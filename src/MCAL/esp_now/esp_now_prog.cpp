#include "esp_now_init.h"
#include "esp_now_config.h"
#include "esp_now_priv.h"
#include "includes.h"
#include "esp_wifi.h"

extern const board_t board_systemBoards[];

esp_now_peer_info_t upStreamDevice;
esp_now_peer_info_t downStreamDevice;

uint8_t upstreamDevice_MAC[6];
uint8_t downstreamDevice_MAC[6];

int esp_now_start(int wifiChannel){
    memcpy(upstreamDevice_MAC,   upstreamDevice_MAC_h,   6);
    memcpy(downstreamDevice_MAC, downstreamDevice_MAC_h, 6);

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false);               // keep radio awake

    uint8_t ch = (wifiChannel > 0) ? (uint8_t)wifiChannel : 11;
    // For the master (board 1), don’t force channel; for others, set it
    if(boardID != 1U){
        esp_wifi_set_channel(ch, WIFI_SECOND_CHAN_NONE);
    }

    memset(&upStreamDevice, 0, sizeof(upStreamDevice));
    memset(&downStreamDevice, 0, sizeof(downStreamDevice));

    if (esp_now_init() != ESP_OK) return 0;

    memcpy(upStreamDevice.peer_addr, upstreamDevice_MAC, 6);
    upStreamDevice.channel = ch;
    upStreamDevice.encrypt = false;
    upStreamDevice.ifidx = WIFI_IF_STA;

    memcpy(downStreamDevice.peer_addr, downstreamDevice_MAC, 6);
    downStreamDevice.channel = ch;
    downStreamDevice.encrypt = false;
    downStreamDevice.ifidx = WIFI_IF_STA;

    esp_now_initPeers(&upStreamDevice, &downStreamDevice);
    esp_now_register_send_cb(esp_now_send_cb_t(esp_now_OnDataSent));
    esp_now_register_recv_cb(esp_now_recv_cb_t(esp_now_onDataRecv));

    return 0;
}
int esp_now_initPeers(esp_now_peer_info_t* upstreamPeer, esp_now_peer_info_t* downstreamPeer){
    // Add upstream peer
    esp_err_t result = esp_now_add_peer(&upStreamDevice);
    if (result != ESP_OK){
        if(serial_output == 1U){
            Serial.print("Failed to add upstream peer. Error: ");
            Serial.println(result);  // Print error code
        }
        return 0;
    }else {
        if(serial_output == 1U){Serial.println("Upstream peer added successfully");}
    }
    
    // Add downstream peer
    result = esp_now_add_peer(&downStreamDevice);
    if (result != ESP_OK){
        if(serial_output == 1U){
            Serial.print("Failed to add downstream peer. Error: ");
            Serial.println(result);  // Print error code
        }
        return 0;
    }else {
        if(serial_output == 1U){Serial.println("Downstream peer added successfully");}
    }

    return 0;
}



void esp_now_OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    if(serial_output == 1U){
        Serial.print("Board ");
        Serial.print(boardID);
        Serial.print(" sent to MAC: ");
        for(int i = 0; i < 6; i++) {
            Serial.print(mac_addr[i], HEX);
            if(i < 5) Serial.print(":");
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
        Serial.print(" received data from MAC: ");
        for(int i = 0; i < 6; i++) {
            Serial.print(mac[i], HEX);
            if(i < 5) Serial.print(":");
        }
        Serial.print(" - Data length: ");
        Serial.println(len);
    }
    networkServices_onDataRecv(*(packet_t*)incomingData);
}
