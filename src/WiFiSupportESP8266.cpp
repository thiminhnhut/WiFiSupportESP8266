#include "WiFiSupportESP8266.h"

WiFiSupportESP8266::WiFiSupportESP8266() {

}

WiFiSupportESP8266::WiFiSupportESP8266(int8_t pin, uint8_t state) {
    _pin = pin;
    _state = state;
    pinMode(pin, OUTPUT);
}

WiFiSupportESP8266::WiFiSupportESP8266(Print *print, int8_t pin, uint8_t state) {
    _debug = true;
    this->_print = print;
    _pin = pin;
    _state = state;
    pinMode(pin, OUTPUT);
}

bool WiFiSupportESP8266::isConnected(const char *ssid, const char *password, unsigned int timeout) {
    _on();

    WiFi.begin(ssid, password);

    unsigned long _start = millis();
    while (millis() - _start <= timeout) {
        if (isConnected()) {
            _network = _getNetwork();

            _exportInfoNetwork();

            _off();

            _debug_connect_wifi_success();

            return true;
        }

        _debug_wait_connect();
    }

    _blink();

    _debug_connect_wifi_fail();

    return false;
}

bool WiFiSupportESP8266::isSmartConfig() {
    _on();

    _debug_start_smart_config();

    WiFi.mode(WIFI_STA);
    delay(5000);

    unsigned long _start = millis();
    unsigned int cnt = 0;
    while (!isConnected()) {
        delay(500);
        _debug_wait_connect();
        if (cnt++ >= 10) {
            WiFi.beginSmartConfig();
            while (true) {
                delay(1000);
                if (WiFi.smartConfigDone()) {
                    break;
                }
                _debug_wait_connect();
            }
        }
    }

    while (true) {
        if (isConnected()) {
            _network = _getNetwork();

            _off();

            _exportInfoNetwork();

            _debug_smart_config_success();

            return true;
        }
        delay(500);
    }

    return false;
}

bool WiFiSupportESP8266::isSmartConfig(unsigned int timeout) {
    _on();

    _debug_start_smart_config();

    WiFi.mode(WIFI_STA);
    delay(5000);

    unsigned long _start = millis();
    unsigned int cnt = 0;
    while (!isConnected() && millis() - _start <= timeout) {
        delay(500);
        _debug_wait_connect();
        if (cnt++ >= 10) {
            WiFi.beginSmartConfig();
            while (millis() - _start <= timeout) {
                delay(1000);
                if (WiFi.smartConfigDone()) {
                    break;
                }
                _debug_wait_connect();
            }
        }
    }

    while (millis() - _start <= timeout) {
        if (isConnected()) {
            _network = _getNetwork();

            _off();

            _exportInfoNetwork();

            _debug_smart_config_success();

            return true;
        }

        _debug_wait_connect();
    }

    _blink();

    _debug_smart_config_fail();

    return false;
}

bool WiFiSupportESP8266::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void WiFiSupportESP8266::disConnected() {
    WiFi.disconnect();
}
void WiFiSupportESP8266::_exportInfoNetwork() {
    if (_debug) {
        if (isConnected()) {
            _print->println(F("\nExport Info Network"));
            _print->print(F("SSID:")); _print->println(_network.ssid);
            _print->print(F("Password:")); _print->println(_network.password);
            _print->print(F("IP:")); _print->println(_network.ip);
            _print->print(F("Getway:")); _print->println(_network.getway);
            _print->print(F("Netmask:")); _print->println(_network.netmask);
            _print->print(F("DNS:")); _print->println(_network.dns);
            _print->print(F("RSSI:")); _print->println(_network.rssi);
            _print->print(F("Mode:")); _print->println(_network.modeString);
            _print->print(F("Channel:")); _print->println(_network.channel);
            _print->print(F("BSSID:")); _print->println(_network.bssid);
            _print->print(F("Hostname:")); _print->println(_network.hostname);
        } else {
            _print->println("Connect wifi fail");
        }
    }
}

NetWork WiFiSupportESP8266::getNetwork() {
    return _network;
}

NetWork WiFiSupportESP8266::_getNetwork() {
    NetWork network;

    network.ssid = _getSSID();
    network.password = _getPassword();
    network.ip = _getIP();
    network.getway = _getGetWay();
    network.netmask = _getNetMask();
    network.dns = _getDNS();
    network.rssi = _getRSSI();
    network.mode = _getMode();
    network.modeString = _getModeString();
    network.channel = _getChannel();
    network.bssid = _getBSSID();
    network.hostname = _getHostName();

    return network;
}

String WiFiSupportESP8266::_getSSID() {
    return WiFi.SSID();
}

String WiFiSupportESP8266::_getPassword() {
    return WiFi.psk();
}

IPAddress WiFiSupportESP8266::_getIP() {
    return WiFi.localIP();
}

IPAddress WiFiSupportESP8266::_getGetWay() {
    return WiFi.gatewayIP();
}

IPAddress WiFiSupportESP8266::_getNetMask() {
    return WiFi.subnetMask();
}

IPAddress WiFiSupportESP8266::_getDNS() {
    return WiFi.dnsIP();
}

int8_t WiFiSupportESP8266::_getRSSI() {
    return WiFi.RSSI();
}

WiFiMode_t WiFiSupportESP8266::_getMode() {
    return WiFi.getMode();
}

String WiFiSupportESP8266::_getModeString() {
    switch (_getMode()) {
        case WIFI_STA:
            return "STA";
        case WIFI_AP:
            return "AP";
        case WIFI_AP_STA:
            return "AP+STA";
        default: // WIFI_MODE_NULL
            return "NULL";
    }
}

uint32_t WiFiSupportESP8266::_getChannel() {
    return WiFi.channel();
}

String WiFiSupportESP8266::_getBSSID() {
    return WiFi.BSSIDstr();
}

String WiFiSupportESP8266::_getHostName() {
    return WiFi.hostname();
}

void WiFiSupportESP8266::_on() {
    if (_pin != -1) {
        digitalWrite(_pin, _state);
    }
}

void WiFiSupportESP8266::_off() {
    if (_pin != -1) {
        digitalWrite(_pin, !_state);
    }
}

void WiFiSupportESP8266::_blink() {
    for (unsigned char i = 0; i < 20; i++) {
        _on();
        delay(500);
        _off();
        delay(500);
    }
}

void WiFiSupportESP8266::_debug_ssid_password() {
    if (_debug) {
        _print->print(F("Reading SSID and Password (NVR):\t"));

        _print->print(F("SSID:"));
        if (_network.ssid.length() > 0) {
            _print->print(_network.ssid);
            _print->print(F("(len:")); _print->print(_network.ssid.length()); _print->print(F(")"));
        } else {
            _print->print(F("None"));
        }

        _print->print(F("\tPassword:"));
        if (_network.password.length() > 0) {
            _print->print(_network.password);
            _print->print(F("(len:")); _print->print(_network.password.length()); _print->println(F(")"));
        } else {
            _print->println(F("None"));
        }
    }
}

void WiFiSupportESP8266::_debug_connect_wifi() {
    if (_debug) {
        _print->print(F("Connecting WiFi:\tSSID:")); _print->print(_network.ssid);
        _print->print(F("\tPassword:")); _print->println(_network.password);
    }
}

void WiFiSupportESP8266::_debug_wait_connect() {
    if (_debug) {
        _print->print(F("."));
        delay(100);
    } else {
        delay(0);
    }
}

void WiFiSupportESP8266::_debug_connect_wifi_success() {
    if (_debug) {
        _print->println(F("\nConnecting WiFi Success!"));
    }
}

void WiFiSupportESP8266::_debug_connect_wifi_fail() {
    if (_debug) {
        _print->println(F("\nConnecting WiFi Failed!"));
    }
}

void WiFiSupportESP8266::_debug_start_smart_config() {
    if (_debug) {
        _print->println(F("Start SmartConfig"));
    }
}

void WiFiSupportESP8266::_debug_no_received_smart_config() {
    if (_debug) {
        _print->println(F("\nSmartConfig Received Failed, Timeout Error!"));
    }
}

void WiFiSupportESP8266::_debug_received_smart_config() {
    if (_debug) {
        _print->println(F("\nSmartConfig received, Waiting for WiFi..."));
    }
}

void WiFiSupportESP8266::_debug_smart_config_success() {
    if (_debug) {
        _print->println(F("\nSmartConfig Success!"));
    }
}

void WiFiSupportESP8266::_debug_smart_config_fail() {
    if (_debug) {
        _print->println(F("\nSmartConfig Fail, Timeout error!"));
    }
}
