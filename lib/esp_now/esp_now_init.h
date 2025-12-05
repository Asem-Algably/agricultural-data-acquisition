#ifndef ESP_NOW_INIT_H
#define ESP_NOW_INIT_H

int esp_now_start(void);
void esp_now_OnDataSent(const esp_now_send_info_t *info, esp_now_send_status_t status);
void esp_now_onDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len);
#endif // ESP_NOW_INIT_H