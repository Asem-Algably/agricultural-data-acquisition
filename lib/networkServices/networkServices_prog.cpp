#include "networkServices_config.h"
#include "networkServices_init.h"
#include "networkServices_priv.h"
#include <Arduino.h>
#include "../esp_now/esp_now_init.h"
#include "../esp_now/esp_now_config.h"
#include "../../include/reefPlusFirmware_config.h"
#include "../app/app_init.h"
#include "../../include/includes.h"
#include "../../include/types.h"

extern const board_t board_systemBoards[];

int networkServices_init(void){
    // Initialization code for network services module
    if(communication_mode == espNow_mode){
        esp_now_start();
    }
    return 0;
}

int networkServices_upstreamPacket(packet_t packet){
    // Code to handle upstream packet ✅
    if(communication_mode == espNow_mode){
        esp_err_t result = esp_now_send(upstreamDevice_MAC_h, (uint8_t *) &packet, sizeof(packet));
        if(serial_output == 1){
            if (result == ESP_OK) {
                Serial.println("packet upstreaming succeeded");
                Serial.print(" at board ");
                Serial.println(boardID);
            }
            else {
                Serial.println("Error upstreaming packet");
                Serial.print(" at board ");
                Serial.println(boardID);
            }
        }
    }

    return 0; // Return 0 on success
}

int networkServices_downstreamPacket(packet_t packet){
    // Code to handle upstream packet ✅
    if(communication_mode == espNow_mode){
        esp_err_t result = esp_now_send(downstreamDevice_MAC_h, (uint8_t *) &packet, sizeof(packet));
        if(serial_output == 1){
            if (result == ESP_OK) {
                Serial.println("packet downstreaming succeeded");
                Serial.print(" at board ");
                Serial.println(boardID);
            }
            else {
                Serial.println("Error downstreaming packet");
                Serial.print(" at board ");
                Serial.println(boardID);
            }
        }
    }

    return 0; // Return 0 on success
}

void networkServices_onDataRecv(packet_t packet){
    app_onDataReceived(packet);
}