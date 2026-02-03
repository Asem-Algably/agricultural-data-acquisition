#include "postServices_priv.h"
#include "postServices_config.h"
#include "postServices_init.h"
#include "includes.h"

// WiFi credentials
const char* ssid = ssid_priv;
const char* password = password_priv;

int postServices_init(){

    WiFi.begin(ssid, password);
    (serial_output == 1U) ? Serial.println("Connecting") : 1;
    int wifi_channel;

    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        (serial_output == 1U) ? Serial.print(".") : 1;
        wifi_channel = WiFi.channel();
        (serial_output == 1U) ? Serial.print(" Current WiFi Channel: ") : 1;
        (serial_output == 1U) ? Serial.println(wifi_channel) : 1;
    }

    if(serial_output == 1U){
        Serial.println("");
        Serial.print("Connected to WiFi network with IP Address: ");
        Serial.println(WiFi.localIP());
    
        
        Serial.println("Post Services Initialized");
    }
    return wifi_channel;
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