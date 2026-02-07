// main component library
#include "includes.h"
#include "./dht11_config.h"
#include "./dht11_init.h"
#include "./dht11_priv.h"
#include <esp_timer.h>

extern const board_t board_systemBoards[];
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
bool dht11_available = false;

void dht11_init(void){
    if(serial_output == 1U){
        Serial.println("DHT11: Starting initialization..."); 
    }
    
    uint64_t start_time = esp_timer_get_time();
    const uint64_t timeout_us = 1500000; // 1.5 second timeout
    
    sensor_t sensor;
    bool sensor_info_retrieved = false;
    bool dht_begin_called = false;
    
    // Try to initialize within timeout
    while ((esp_timer_get_time() - start_time) < timeout_us) {
        // Call dht.begin() only once
        if (!dht_begin_called) {
            dht.begin();
            dht_begin_called = true;
            Serial.println("DHT11: dht.begin() called");
            delay(100);
            yield();
        }
        Serial.println("DHT11: Re-enabling watchdog...");
        
        // Now try to get sensor info
        dht.temperature().getSensor(&sensor);
        
        // Check if we got valid sensor data (sensor_id will be non-zero for valid sensor)
        if (sensor.sensor_id != 0) {
            Serial.println(F("------------------------------------"));
            Serial.println(F("Temperature Sensor"));
            Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
            Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
            Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
            Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
            Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
            Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
            Serial.println(F("------------------------------------"));
            
            dht.humidity().getSensor(&sensor);
            Serial.println(F("Humidity Sensor"));
            Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
            Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
            Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
            Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
            Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
            Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
            Serial.println(F("------------------------------------"));
            
            delayMS = sensor.min_delay / 1000;
            dht11_available = true;
            sensor_info_retrieved = true;
            Serial.println("DHT11: Initialization successful");
            break; // Success - exit loop
        }
        delay(100);
        yield(); // Let other tasks run
    }
    
    if (!sensor_info_retrieved) {
        Serial.println("DHT11: Sensor not responding - continuing without DHT11");
        dht11_available = false;
        delayMS = 2000; // Default delay
    }
}

dht11_object returnDHT11Readings(void){
    dht11_object result;
    result.airTemp = -1.0f;   // Error default
    result.airHumid = -1.0f;  // Error default
    
    if (!dht11_available) {
        if (serial_output == 1U) {
            Serial.println("DHT11: Sensor not available");
        }
        return result;
    }
    
    // Delay between measurements.
    delay(delayMS);
    
    // Get temperature event and print its value.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature) && (serial_output) == 1U) {
        Serial.println(F("Error reading temperature!"));
    }
    else {
        if ((serial_output) == 1U){
            Serial.print(F("Temperature: "));
            Serial.print(event.temperature);
            Serial.println(F("°C"));
        }        
        result.airTemp = event.temperature;
    }
    
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity) && (serial_output) == 1U) {
        Serial.println(F("Error reading humidity!"));
    }
    else {
        if ((serial_output) == 1U){
            Serial.print(F("Humidity: "));
            Serial.print(event.relative_humidity);
            Serial.println(F("%"));
        }
        result.airHumid = event.relative_humidity;
    }

    return result;
}
