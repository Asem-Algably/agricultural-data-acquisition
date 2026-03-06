#include "postServices_priv.h"
#include "postServices_config.h"
#include "postServices_init.h"
#include "includes.h"
#include <WiFiClientSecure.h>

// WiFi credentials
const char* ssid = ssid_priv;
const char* password = password_priv;


void postServices_init(){

    WiFi.begin(ssid, password);
    (serial_output == 1U) ? Serial.printf("Connecting to wifi %s", ssid) : 1;
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
    delay(500);
    return;
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
        Serial.printf("Posting data of board %d to server...\n", boardNum);
    }

    WiFi.setSleep(false);
    if(WiFi.status() != WL_CONNECTED){
        WiFi.reconnect();
        unsigned long t = millis();
        while(WiFi.status() != WL_CONNECTED && millis() - t < 4000) delay(100);
        if(WiFi.status() != WL_CONNECTED) return false;
    }

    String base = String("https://webhook.site/21e17a97-1064-4502-a041-17746a889a10");

    String airHumidURL  = base + "/api/v1/sensors/" + board_systemBoards[boardNum-1].airHumiditySensorId    + "/data";
    String airTempURL   = base + "/api/v1/sensors/" + board_systemBoards[boardNum-1].airTemperatureSensorId + "/data";
    String soilHumidURL = base + "/api/v1/sensors/" + board_systemBoards[boardNum-1].soilMoistureSensorId   + "/data";

    httppost(airHumidURL,  "{\"value\":\""+String(data.airHumidity)+"\",\"unit\":\"%\",\"recordedAt\":\"2022-01-01T00:00:00Z\"}");
    httppost(airTempURL,   "{\"value\":\""+String(data.airTemperature)+"\",\"unit\":\"C\",\"recordedAt\":\"2022-01-01T00:00:00Z\"}");
    httppost(soilHumidURL, "{\"value\":\""+String(data.soilHumidity)+"\",\"unit\":\"%\",\"recordedAt\":\"2022-01-01T00:00:00Z\"}");

    return true;
}

void postServices_deinit(){
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    if(serial_output == 1U){
        Serial.println("Post Services Deinitialized");
    }
}

void httppost(String url, String jsonpayload){
    
    HTTPClient http;
    http.begin(url.c_str()); // endpoint to post all data together
    
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(jsonpayload);
    if(serial_output == 1U){
        Serial.print("POST to ");
        Serial.print(url);
        Serial.print(" with payload: ");
        Serial.print(jsonpayload);
        Serial.print(" - Response code: ");
        Serial.println(httpResponseCode);
    }
    http.end(); 
}