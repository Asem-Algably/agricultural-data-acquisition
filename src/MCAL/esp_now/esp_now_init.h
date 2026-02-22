#ifndef ESP_NOW_INIT_H
#define ESP_NOW_INIT_H
#include <esp_now.h>
#include <WiFi.h>

bool esp_now_start();
void esp_now_OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void esp_now_onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
#endif // ESP_NOW_INIT_H