################################
Thư viện kết nối WiFi cho ESP8266
################################

:Info: Github <https://github.com/thiminhnhut/WiFiSupportESP8266>
:Author: Thi Minh Nhựt <thiminhnhut@gmail.com>
:Date: $Date: 19/04/2019 $
:Revision: $Revision: 1.1.0 $
:Description: Thư viện kết nối WiFi cho ESP8266

===============================================================

.. sectnum::

.. contents:: Nội dung

===============================================================

Nội dung thực hiện
******************

Thư viện WiFiSupportESP8266
=============================

* Thư mục source: `src <https://github.com/thiminhnhut/WiFiSupportESP8266/blob/master/src>`_.

  * Struct ``NetWork`` gồm các field sau:

  .. code::

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

  * File `WiFiSupportESP8266.h <https://github.com/thiminhnhut/WiFiSupportESP8266/blob/master/src/WiFiSupportESP8266.h>`_:

  .. code::

    WiFiSupportESP8266();

    WiFiSupportESP8266(int8_t pin, uint8_t state);

    WiFiSupportESP8266(Print *print, int8_t pin, uint8_t state);

    bool isConnected(const char* ssid, const char* password, unsigned int timeout);

    bool isSmartConfig();

    bool isSmartConfig(unsigned int timeout);

    bool isConnected();

    bool disConnected();

    NetWork getNetwork();

  * File `WiFiSupportESP8266.cpp <https://github.com/thiminhnhut/WiFiSupportESP8266/blob/master/src/WiFiSupportESP8266.cpp>`_.

* Ví dụ:

  * Kết nối WiFi cho ESP8266 `ConnectWiFi.ino <https://github.com/thiminhnhut/WiFiSupportESP8266/blob/master/examples/ConnectWiFi/ConnectWiFi.ino>`_

  * Kết nối WiFi cho ESP8266 với giao thức SmartConfig `SmartConfig.ino <https://github.com/thiminhnhut/WiFiSupportESP8266/blob/master/examples/SmartConfig/SmartConfig.ino>`_

Chức năng của thư viện WiFiSupportESP8266
===========================================

* Kết nối WiFi cho ESP8266 với ``SSID`` và ``Password``.

* Kết nối WiFi cho ESP8266 với giao thức SmartConfig và tự động vào mạng WiFi đã kết nối cho các lần sau.

* Lấy thông tin của mạng WiFi đang kết nối (``struct NetWork``).

Revision
========

* `Version 1.0.0 <https://github.com/thiminhnhut/WiFiSupportESP8266/releases/tag/1.0.0>`_

* `Version 1.1.0 <https://github.com/thiminhnhut/WiFiSupportESP8266/releases/tag/1.1.0>`_
