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
    int wifi_channel = 11;

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

    String base = String("https://webhook.site/");

    String airHumidURL  = base + "/api/v1/sensors/" + board_systemBoards[boardNum-1].airHumiditySensorId    + "/data";
    String airTempURL   = base + "/api/v1/sensors/" + board_systemBoards[boardNum-1].airTemperatureSensorId + "/data";
    String soilHumidURL = base + "/api/v1/sensors/" + board_systemBoards[boardNum-1].soilMoistureSensorId   + "/data";

    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;
    http.setReuse(false);
    http.setTimeout(5000);

    auto postOne = [&](const String& fullUrl, const String& payload){
        IPAddress ip;
        // try DNS up to 2 times
        for(int i=0;i<2;i++){
            if(WiFi.hostByName("webhook.site", ip)) break;
            delay(200);
            if(i==1) { if(serial_output) Serial.println("DNS still failing; skip this POST"); return false; }
        }
        if(!http.begin(client, fullUrl)) return false;
        http.addHeader("Content-Type", "application/json");
        int code = http.POST(payload);
        if(serial_output) Serial.println(code);
        http.end();
        delay(600); // give TLS/socket time between posts
        return code > 0;
    };

    postOne(airHumidURL,  "{\"value\":\""+String(data.airHumidity)+"\",\"unit\":\"%\",\"recordedAt\":\"2022-01-01T00:00:00Z\"}");
    postOne(airTempURL,   "{\"value\":\""+String(data.airTemperature)+"\",\"unit\":\"C\",\"recordedAt\":\"2022-01-01T00:00:00Z\"}");
    postOne(soilHumidURL, "{\"value\":\""+String(data.soilHumidity)+"\",\"unit\":\"%\",\"recordedAt\":\"2022-01-01T00:00:00Z\"}");

    return true;
}