#include "../../include/includes.h"
#include "../../include/types.h"
#include "app_init.h"
#include "app_config.h"
#include "app_priv.h"

void app_init(void){
    Serial.println("DEBUG: Starting app_init");
    int wifiChannel = 11;

    if(boardID == 1){
        Serial.println("DEBUG: Before postServices_init");
        wifiChannel = postServices_init();
        Serial.println("DEBUG: After postServices_init");
    }

    Serial.println("DEBUG: Before soilHumid_init");
    soilHumid_init();
    Serial.println("DEBUG: After soilHumid_init");
    Serial.println("DEBUG: Before dht11_init");
    dht11_init();
    Serial.println("DEBUG: After dht11_init");
    Serial.println("DEBUG: Before networkServices_init");
    networkServices_init(wifiChannel);
    Serial.println("DEBUG: After networkServices_init");
    Serial.println("app_init finished");
    Serial.println("-----------------------------");
}

void app_masterTask(void){
    // 1) Request data from other boards FIRST (avoid HTTP blocking during radio traffic)
    for(int i = 2; i <= boardsChainLength; i++){
        Serial.printf("handling board %d data \n\n", i);
        if(serial_output == 1U){
            Serial.println("Master board is requesting data from other boards ");
            Serial.print("Requesting data from board ");
            Serial.println(i);
        }

        packet_t packet;
        packet.packetType = upPacketType;
        packet.boardNum = i;

        networkServices_upstreamPacket(packet);

        if(serial_output == 1U){
            Serial.print("Master board requested data from board ");
            Serial.println(i);
        }

        // Wait for response window (tune for your chain)
        delay(2000);
        yield();
        Serial.printf("\n\nMaster board finished handling data from board %d\n-------------------------------------\n", i);
    }

    // 2) Post master board's own data AFTER ESP-NOW exchange
    Serial.println("Master board is handling its own data");
    sensorsData_t data = app_collectSensorData();
    if(serial_output == 1U){
        Serial.println("Master board collected its own data will posted it");
    }
    postServices_postData(data, boardID);
    if(serial_output == 1U){
        Serial.println("Master board posted its own data");
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
    // show received data
    if(serial_output == 1U){
        Serial.printf("Board %d received packet going to board %d with with packet type %d,", 
            boardID, packet.boardNum, packet.packetType);
    }
    (serial_output == 1U) ? Serial.printf("Board %d is processing the received packet\n", boardID) : 1;
    if(boardID == 1){
        // Master board processing
        (serial_output == 1U) ? Serial.printf("Master board received data from other and will post it %d\n", packet.boardNum) : 1; 
        postServices_postData((sensorsData_t){packet.airHumidity, packet.airTemperature, packet.soilHumidity}, packet.boardNum);
        (serial_output == 1U) ? Serial.printf("Master board posted data from other board %d\n", packet.boardNum) : 1;
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
