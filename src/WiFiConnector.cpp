#include <WiFiConnector.h>

WiFiConnector::WiFiConnector(const String &ssid, const String &password)
{
    this->ssid = ssid;
    this->password = password;
}

bool WiFiConnector::connect()
{
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
	WiFi.setAutoReconnect(true);

    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    return true;
}