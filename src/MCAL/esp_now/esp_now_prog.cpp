#include "esp_now_init.h"
#include "esp_now_config.h"
#include "esp_now_priv.h"
#include "includes.h"

extern const board_t board_systemBoards[];

esp_now_peer_info_t upStreamDevice;
esp_now_peer_info_t downStreamDevice;  

uint8_t upstreamDevice_MAC[6];
uint8_t downstreamDevice_MAC[6];


int esp_now_start(int wifiChannel){
    memcpy(upstreamDevice_MAC, upstreamDevice_MAC_h, 6);
    memcpy(downstreamDevice_MAC, downstreamDevice_MAC_h, 6);
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        if (serial_output == 1U) {
            Serial.print("Error initializing ESP-NOW");
            Serial.print(" at board ");
            Serial.println(boardID);
        }
        return 0;
    }else {
        if (serial_output == 1U) {
            Serial.println("ESP-NOW initialized successfully");
            Serial.print(" at board ");
            Serial.println(boardID);
        }
    }
    
    
    
    memcpy(upStreamDevice.peer_addr, upstreamDevice_MAC, 6);
    upStreamDevice.channel = wifiChannel;
    upStreamDevice.encrypt = false;
    
    memcpy(downStreamDevice.peer_addr, downstreamDevice_MAC, 6);
    downStreamDevice.channel = wifiChannel;
    downStreamDevice.encrypt = false;
    
    esp_now_initPeers(&upStreamDevice, &downStreamDevice);
    
    // Register callbacks ✅
    esp_now_register_send_cb(esp_now_send_cb_t(esp_now_OnDataSent));
    esp_now_register_recv_cb(esp_now_recv_cb_t(esp_now_onDataRecv));
    
    return 0;
}
int esp_now_initPeers(esp_now_peer_info_t* upstreamPeer, esp_now_peer_info_t* downstreamPeer){
    // Add upstream peer
    if (esp_now_add_peer(&upStreamDevice) != ESP_OK){
        if(serial_output == 1U){Serial.println("Failed to add upstream peer");}
        return 0;
    }else {
        if(serial_output == 1U){Serial.println("Upstream peer added successfully");}
    }
    
    // Add downstream peer
    if (esp_now_add_peer(&downStreamDevice) != ESP_OK){
        if(serial_output == 1U){Serial.println("Failed to add downstream peer");}
        return 0;
    }else {
        if(serial_output == 1U){Serial.println("Downstream peer added successfully");}
    }

    return 0;
}



void esp_now_OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    if(serial_output == 1U){
        Serial.print("Packet sent with status: ");
        Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
        Serial.print(" at board ");
        Serial.println(boardID);
    }
}
void esp_now_onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    networkServices_onDataRecv(*(packet_t*)incomingData);
}
