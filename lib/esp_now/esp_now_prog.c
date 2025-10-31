#include "esp_now_init.h"
#include "esp_now_config.h"
#include "esp_now_priv.h"

esp_now_peer_info_t upStreamDevice;
esp_now_peer_info_t downStreamDevice;

uint8_t upstreamDevice_MAC[6] = upstreamDevice_MAC;
uint8_t downstreamDevice_MAC[6] = downstreamDevice_MAC;

int esp_now_initPeers(esp_now_peer_info_t *upstreamPeer, esp_now_peer_info_t *downstreamPeer){
    if (esp_now_add_peer(upstreamPeer) != ESP_OK){
        #if serial_output == 1U
            Serial.println("Failed to add upstream device");
        #endif
    }else {
        #if serial_output == 1U
            Serial.println("Upstream device added successfully");
        #endif
    }
    if (esp_now_add_peer(downstreamPeer) != ESP_OK){
        #if serial_output == 1U
            Serial.println("Failed to add downstream device");
        #endif
    }else {
        #if serial_output == 1U
            Serial.println("Downstream device added successfully");
        #endif
    }
}

int esp_now_start(){
    memcpy(upStreamDevice.peer_addr, upstreamDevice_MAC, 6);
    upStreamDevice.channel = 0;
    upStreamDevice.encrypt = false;

    memcpy(downStreamDevice.peer_addr, downstreamDevice_MAC, 6);
    downStreamDevice.channel = 0;
    downStreamDevice.encrypt = false;

    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        #if serial_output == 1U
            Serial.print("Error initializing ESP-NOW in device with boardID: ");
            Serial.print(boardID);
        #endif
        return -1;
    }

    int esp_now_initPeers(&upStreamDevice, &downStreamDevice);

    return 0;
}


void esp_now_OnDataSent(const esp_now_send_info_t *info, esp_now_send_status_t status) {
    // Do nothing for now
}
void esp_now_onDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
    // Do nothing for now
}
