#ifndef WiFiConnector_h
#define WiFiConnector_h

#include <Arduino.h>
#include <ESP8266WiFi.h>

class WiFiConnector
{
public:
    WiFiConnector(const String &ssid, const String &password);
    bool connect();
	inline bool isConnected() const { return WiFi.status() == WL_CONNECTED; }
private:
    String ssid;
    String password;
};

#endif

