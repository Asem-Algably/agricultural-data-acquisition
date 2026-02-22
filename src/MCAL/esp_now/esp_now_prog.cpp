#include "esp_now_init.h"
#include "esp_now_config.h"
#include "esp_now_priv.h"
#include "includes.h"
#include "esp_wifi.h"

esp_now_peer_info_t upStreamDevice;
esp_now_peer_info_t downStreamDevice;

uint8_t upstreamDevice_MAC[6];
uint8_t downstreamDevice_MAC[6];

bool esp_now_start(){

    WiFi.mode(WIFI_STA);

    esp_wifi_set_channel(5, WIFI_SECOND_CHAN_NONE); // set radio channel

    if (esp_now_init() != ESP_OK){
        if(serial_output == 1U){
            Serial.print("Error initializing ESP-NOW with error code ");
            Serial.println(esp_err_to_name(esp_now_init()));
        }
        return 0;
    }else {
        if(serial_output == 1U){
            Serial.println("ESP-NOW initialized successfully");
        }
    }
    
    esp_now_register_send_cb(esp_now_send_cb_t(esp_now_OnDataSent));

    memcpy(upstreamDevice_MAC,   upstreamDevice_MAC_h,   6);
    memcpy(downstreamDevice_MAC, downstreamDevice_MAC_h, 6);

    memcpy(upStreamDevice.peer_addr, upstreamDevice_MAC, 6);
    upStreamDevice.channel = 5;            // follow current (home) channel
    upStreamDevice.encrypt = false;

    memcpy(downStreamDevice.peer_addr, downstreamDevice_MAC, 6);
    downStreamDevice.channel = 5;          // follow current (home) channel
    downStreamDevice.encrypt = false;

    esp_now_initPeers(&upStreamDevice, &downStreamDevice);


    esp_now_register_recv_cb(esp_now_recv_cb_t(esp_now_onDataRecv));
    return true;
}
int esp_now_initPeers(esp_now_peer_info_t* upstreamPeer, esp_now_peer_info_t* downstreamPeer){
    // Add upstream peer
    if(boardID < boardsChainLength){
        int result = esp_now_add_peer(&upStreamDevice);
        if (result != ESP_OK){
            if(serial_output == 1U){
                Serial.print("Failed to add upstream peer. Error: ");
                Serial.println(result);  // Print error code
            }
            return 0;
        }else {
            if(serial_output == 1U){Serial.println("Upstream peer added successfully");}
        }
    }
    
    // Add downstream peer
    if(boardID > 1U){
        int result = esp_now_add_peer(&downStreamDevice);
        if (result != ESP_OK){
            if(serial_output == 1U){
                Serial.print("Failed to add downstream peer. Error: ");
                Serial.println(result);  // Print error code
            }
            return 0;
        }else {
            if(serial_output == 1U){Serial.println("Downstream peer added successfully");}
        }
    }


    return 0;
}



void esp_now_OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    if(serial_output == 1U){
        Serial.print("Board ");
        Serial.print(boardID);
        Serial.print(" sent to board: ");
        for(int i = 0; i < boardsChainLength; i++) {
            if (board_systemBoards[i].macAddress[0] == mac_addr[0] &&
                board_systemBoards[i].macAddress[1] == mac_addr[1] &&
                board_systemBoards[i].macAddress[2] == mac_addr[2] &&
                board_systemBoards[i].macAddress[3] == mac_addr[3] &&
                board_systemBoards[i].macAddress[4] == mac_addr[4] &&
                board_systemBoards[i].macAddress[5] == mac_addr[5]) {
                    Serial.print(board_systemBoards[i].boardId);
                    break;
            }           
        }
        Serial.print(" - Status: ");
        Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Failed");
    }
}
void esp_now_onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    // submit received data
    if(serial_output == 1U){
        Serial.print("Board ");
        Serial.print(boardID);
        Serial.print(" received data from board: ");
        for(int i = 0; i < boardsChainLength; i++) {
            if (board_systemBoards[i].macAddress[0] == mac[0] &&
                board_systemBoards[i].macAddress[1] == mac[1] &&
                board_systemBoards[i].macAddress[2] == mac[2] &&
                board_systemBoards[i].macAddress[3] == mac[3] &&
                board_systemBoards[i].macAddress[4] == mac[4] &&
                board_systemBoards[i].macAddress[5] == mac[5]) {
                    Serial.print(board_systemBoards[i].boardId);
                    break;
            }           
        }
        Serial.print(" - Data length: ");
        Serial.println(len);
    }
    networkServices_onDataRecv(*(packet_t*)incomingData);
}
