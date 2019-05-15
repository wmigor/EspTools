#include <WiFiControl.h>

WiFiControl::WiFiControl(const String &name, const String &url, const String &type, ESP8266WebServer *server)
{
    this->name = name;
    this->url = url;
    this->type = type;
    this->server = server;
}

WiFiControl::~WiFiControl()
{
}
