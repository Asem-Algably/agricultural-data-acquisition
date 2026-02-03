#include "../../include/includes.h"
#include "../../include/types.h"
#include "app_init.h"
#include "app_config.h"
#include "app_priv.h"

void app_init(void){
    postServices_init();
    soilHumid_init();
    dht11_init();
    networkServices_init();
}

void app_masterTask(void){
    // Code for the master task
    sensorsData_t data = app_collectSensorData();
    postServices_postData(data, boardID);

    for(int i = 2; i <= boardsChainLength; i++){
        packet_t packet;
        packet.packetType = upPacketType;
        packet.boardNum = i;
        networkServices_upstreamPacket(packet);
        delay(20);
    }
    delay(systemDutyCycle);
}

sensorsData_t app_collectSensorData(void){
    sensorsData_t data;
    data.soilHumidity = returnSoilHumid();

    dht11_object dht11Data = returnDHT11Readings();
    data.airHumidity = dht11Data.airHumid;
    data.airTemperature = dht11Data.airTemp;
    return data;
}

void app_onDataReceived(packet_t packet){
    if(boardID == 1){
        // Master board processing
        postServices_postData((sensorsData_t){packet.airHumidity, packet.airTemperature, packet.soilHumidity}, packet.boardNum);
    
    } else if (boardID == boardsChainLength){
        // terminator board processing
        sensorsData_t data = app_collectSensorData();
        networkServices_downstreamPacket((packet_t){
            .packetType = downPacketType,
            .airHumidity = data.airHumidity,
            .airTemperature = data.airTemperature,
            .soilHumidity = data.soilHumidity,
            .boardNum = boardID
        });
    }else{
        // Middle board processing
        if(packet.packetType == upPacketType){
            // Process upstream packet
            if(packet.boardNum == boardID){
                sensorsData_t data = app_collectSensorData();
                networkServices_downstreamPacket((packet_t){
                    .packetType = downPacketType,
                    .airHumidity = data.airHumidity,
                    .airTemperature = data.airTemperature,
                    .soilHumidity = data.soilHumidity,
                    .boardNum = boardID
                });
            }else{
                networkServices_upstreamPacket(packet);
            }
        }else{
            // Process downstream packet
            networkServices_downstreamPacket(packet);
        }
    }
}
