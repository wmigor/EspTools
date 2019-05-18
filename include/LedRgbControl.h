#ifndef LedRgbControl_h
#define LedRgbControl_h

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <WiFiControl.h>
#include <ForceKey.h>
#include <Color.h>

class LedRgbControl : public WiFiControl
{
public:
    LedRgbControl(const String &name, const String &url, int redPin, int greenPin, int bluePin, int value, int maxValue, int delta, ESP8266WebServer *server);
    void setup();
    void update();
    void setEnabled(bool enabled);
    bool isEnabled() const;
private:
    ForceKey redKey;
    ForceKey greenKey;
    ForceKey blueKey;
    Color color;

private:
    void serverHandleInfo();
    void serverHandleColor();
};

#endif
