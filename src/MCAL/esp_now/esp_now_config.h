#ifndef ESP_NOW_CONFIG_H
#define ESP_NOW_CONFIG_H
#include "includes.h"
#include "esp_now_priv.h"

// define relative MAC addresses for target devices
#if boardID == 1U
    #define upstreamDevice_MAC_h board_systemBoards[boardID].macAddress // MAC address of the upstream device for boardID 1
    #define downstreamDevice_MAC_h board_systemBoards[boardID].macAddress // MAC address of the downstream device for boardID 1
#elif boardID == boardsChainLength
    #define upstreamDevice_MAC_h board_systemBoards[boardID -2].macAddress // MAC address of the upstream device for boardID 2
    #define downstreamDevice_MAC_h board_systemBoards[boardID -2].macAddress // MAC address of the downstream device for boardID 2
#else
    #define upstreamDevice_MAC_h board_systemBoards[boardID].macAddress // MAC address of the upstream device for boardID 3
    #define downstreamDevice_MAC_h board_systemBoards[boardID -2].macAddress // MAC address of the downstream device for boardID 3
#endif

#endif // ESP_NOW_CONFIG_H