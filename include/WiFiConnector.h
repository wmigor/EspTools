#ifndef WiFiConnector_h
#define WiFiConnector_h

#include <Arduino.h>

class WiFiConnector
{
public:
    WiFiConnector(const String &ssid, const String &password);
    bool connect();
private:
    String ssid;
    String password;
};

#endif

