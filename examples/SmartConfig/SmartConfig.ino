#include <Arduino.h>
#include <WiFiSupportESP8266.h>

#define __TIMEOUT__ 60000
#define __LED_STATUS__ 2
#define __LED_STATE__ LOW

#define __SERIAL_MONITOR__ Serial
#define __BAUD_RATE__ 115200

WiFiSupportESP8266 wifiSupport(&__SERIAL_MONITOR__, __LED_STATUS__, __LED_STATE__);

void setup() {
    __SERIAL_MONITOR__.begin(__BAUD_RATE__);

    bool isConnected = wifiSupport.isSmartConfig(__TIMEOUT__);
    if (!isConnected) {
        ESP.restart();
    }

    // bool isConnected = wifiSupport.isSmartConfig();

    __SERIAL_MONITOR__.println("Finish!");
}

void loop() {

}
