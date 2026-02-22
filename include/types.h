#ifndef TYPES_H
#define TYPES_H
#include <Arduino.h>

// standard types
typedef      unsigned char            u8   ;
typedef      signed char              s8   ;
typedef      unsigned short           u16  ;
typedef      signed short             s16  ;
typedef      unsigned long            u32  ;
typedef      signed long              s32  ;
typedef      unsigned long long       u64  ;
typedef      signed long long         s64  ;

// application specific types
typedef struct {
    char boardId[32];                 // Board ID string
    char airHumiditySensorId[32];     // Air humidity sensor ID
    char airTemperatureSensorId[32];  // Air temperature sensor ID
    char soilMoistureSensorId[32];    // Soil moisture sensor ID
    u8 dht11DataPin;                  // DHT11 sensor data pin
    u8 soilHumiditySensorPin;         // Soil humidity sensor analog pin
    uint8_t macAddress[6];
} board_t;

typedef struct {
    float airHumidity;                // Air humidity value
    float airTemperature;             // Air temperature value
    float soilHumidity;               // Soil humidity value
} sensorsData_t;

typedef struct {
    u8 packetType;
    float airHumidity;
    float airTemperature;
    float soilHumidity;
    u8 boardNum;
} packet_t;

#define downPacketType 0x01
#define upPacketType   0x02

typedef struct {
    u8 boardNum;
    sensorsData_t sensorsData;
    u8 status;
} boardData_t;

#define availableStatus 0x01
#define unavailableStatus 0x02

#endif // TYPES_H