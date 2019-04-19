#ifndef WiFiSupportESP8266_h
#define WiFiSupportESP8266_h

#include <Arduino.h>
#include <ESP8266WiFi.h>

struct NetWork {
    String ssid;
    String password;
    IPAddress ip;
    IPAddress getway;
    IPAddress netmask;
    IPAddress dns;
    int8_t rssi;
    WiFiMode_t mode;
    String modeString;
    uint32_t channel;
    String bssid;
    String hostname;
};

class WiFiSupportESP8266 {

private:

    int8_t _pin = -1;
    uint8_t _state;

    bool _debug = false;
    Print *_print;

    const char* _keyWiFi = "wifi";
    const char* _keySSID = "ssid";
    const char* _keyPassword = "password";
    String _defaultSSID = "";
    String _defaultPassword = "";

    NetWork _network;
    NetWork _getNetwork();
    String _getSSID();
    String _getPassword();
    IPAddress _getIP();
    IPAddress _getGetWay();
    IPAddress _getNetMask();
    IPAddress _getDNS();
    int8_t _getRSSI();
    WiFiMode_t _getMode();
    String _getModeString();
    uint32_t _getChannel();
    String _getBSSID();
    String _getHostName();

    void _exportInfoNetwork();

    void _on();
    void _off();
    void _blink();

    void _debug_ssid_password();
    void _debug_connect_wifi();
    void _debug_wait_connect();
    void _debug_connect_wifi_success();
    void _debug_connect_wifi_fail();
    void _debug_start_smart_config();
    void _debug_no_received_smart_config();
    void _debug_received_smart_config();
    void _debug_smart_config_success();
    void _debug_smart_config_fail();

    void _delay(unsigned int t);

public:

    WiFiSupportESP8266();

    WiFiSupportESP8266(int8_t pin, uint8_t state);

    WiFiSupportESP8266(Print *print, int8_t pin, uint8_t state);

    bool isConnected(const char* ssid, const char* password, unsigned int timeout);

    bool isSmartConfig();

    bool isSmartConfig(unsigned int timeout);

    bool isConnected();

    void disConnected();

    NetWork getNetwork();

};
#endif
