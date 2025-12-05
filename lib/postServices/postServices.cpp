#include "postServices_priv.h"
#include "postServices_config.h"
#include "postServices_init.h"
#include "../../include/types.h"
#include "../../include/includes.h"

void postServices_init(){
    if(serial_output == 1U){
        Serial.println("Post Services Initialized");
    }
}

bool postServices_postData(sensorsData_t data, u8 boardNum){
    if(serial_output == 1U){
        Serial.print("Board ");
        Serial.print(boardNum);
        Serial.print(" - Air Humidity: ");
        Serial.print(data.airHumidity);
        Serial.print(" %, Air Temperature: ");
        Serial.print(data.airTemperature);
        Serial.print(" C, Soil Humidity: ");
        Serial.print(data.soilHumidity);
        Serial.println(" %");
    }
    return true;
}