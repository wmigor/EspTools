#ifndef WiFiControl_h
#define WiFiControl_h

#include <ARduino.h>
#include <ESP8266WebServer.h>

class WiFiControl
{
public:
    WiFiControl(const String &name, const String &url, const String &type, ESP8266WebServer *server);
    virtual ~WiFiControl();

    virtual void setup() = 0;

    inline String getName() const { return name; }
    inline String getUrl() const { return url; }
    inline String getType() const { return type; }
    inline ESP8266WebServer *getServer() const { return server; }

private:
    String name;
    String url;
    String type;
    ESP8266WebServer *server;
};

#endif
