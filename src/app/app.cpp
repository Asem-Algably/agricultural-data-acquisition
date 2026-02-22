#include "includes.h"
#include "types.h"
#include "app_init.h"
#include "app_config.h"
#include "app_priv.h"   // must contain board_t/boardData_t definitions

boardData_t boardsData[boardsChainLength];  // defined after the types are known

void app_init(void){
    networkServices_init();
    // if(boardID == 1){postServices_init();}
    soilHumid_init();
    dht11_init();
    Serial.println("app_init finished");
    Serial.println("-----------------------------");
}

void app_masterTask(void){
    clearSysArr(); // reset availability each cycle

    Serial.println("data collection cycle started");
    Serial.println("collecting master board data");
    sensorsData_t data = app_collectSensorData();
    // yield();
    boardsData[0].sensorsData = data;
    boardsData[0].status = availableStatus;
    boardsData[0].boardNum = boardID;
    if(serial_output == 1U){
        Serial.println("Master board data had been submitted to boardsData array");;
    }
    Serial.println("--------------------------------------");
    // 1) Request data from other boards FIRST
    for(int i = 2; i <= boardsChainLength; i++){
        Serial.printf("handling board %d data \n\n", i);
        if(serial_output == 1U){
            Serial.printf("Master board is requesting data from board %d\n", i);
        }

        packet_t packet;
        packet.packetType = upPacketType;
        packet.boardNum = i;

        Serial.printf("before networkservice going to board %d\n", i);
        networkServices_upstreamPacket(packet);
        Serial.printf("after networkservice going to board %d\n", i);

        if(serial_output == 1U){
            Serial.printf("Master board requested data from board %d\n", i);
        }

        // Wait for response window (tune for your chain)
        delay(2000);
        // yield();
        Serial.printf("\nMaster board finished handling data from board %d\n-------------------------------------\n", i);
    }

    // print system array
    app_printBoardsData();

    // 2) Post master board's own data AFTER ESP-NOW exchange
    // postServices_postData(data, boardID);
    // if(serial_output == 1U){
    //     Serial.println("Master board posted its own data");
    // }

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
        Serial.printf("Board %d received coming from board %d with with packet type %d,", 
            boardID, packet.boardNum, packet.packetType);
    }
    if(boardID == 1){
        // Master board processing
        (serial_output == 1U) ? Serial.printf("Master board received data from board %d and will submit it \n", packet.boardNum) : 1; 
        boardsData[packet.boardNum-1].sensorsData = (sensorsData_t){
            .airHumidity = packet.airHumidity,
            .airTemperature = packet.airTemperature,
            .soilHumidity = packet.soilHumidity
        };
        boardsData[packet.boardNum-1].status = availableStatus;
        boardsData[packet.boardNum-1].boardNum = packet.boardNum;
        (serial_output == 1U) ? Serial.printf("Master board submitted data from board %d\n", packet.boardNum) : 1;
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

void clearSysArr(){
    for (int i = 0; i < boardsChainLength; i++){
        boardsData[i].boardNum = i + 1;                 // keep the ID
        boardsData[i].status   = unavailableStatus;
        boardsData[i].sensorsData = (sensorsData_t){-1.0f, -1.0f, -1.0f};
    }
}

void app_printBoardsData(){
    if(serial_output != 1U) return;
    Serial.println("=== boardsData log ===");
    for(int i = 1; i <= boardsChainLength; i++){
        Serial.printf("Board %d | status=%s | airHum=%.2f %% | airTemp=%.2f C | soilHum=%.2f %%\n",
            i,
            (boardsData[i-1].status == availableStatus) ? "available" : "unavailable",
            boardsData[i-1].sensorsData.airHumidity,
            boardsData[i-1].sensorsData.airTemperature,
            boardsData[i-1].sensorsData.soilHumidity
        );
    }
    Serial.println("=======================");
}