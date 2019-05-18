#ifndef ForceKeyServerControl_h
#define ForceKeyServerControl_h

#include <ForceKey.h>
#include <WiFiControl.h>
#include <ESP8266WebServer.h>
#include <LedRgbControl.h>

class ForceKeyServerControl : public WiFiControl
{
public:
    ForceKeyServerControl(const String & name, const String &url, ForceKey *forceKey, ESP8266WebServer *server, LedRgbControl *ledRgb);
    void setup();

private:
    ForceKey *forceKey;
    LedRgbControl *ledRgb;

private:
    void serverhandleInfo();
    void serverHandleRelayOn();
    void serverHandleRelayOff();
    void serverHandleRelayToggle();
    void serverHandleRelayStatus();
    void serverHandleRelayRatio();
    String getStatus();
    inline bool isEnabled() const { return forceKey->isHigh(); }
    inline void relayEnable() { forceKey->setHigh(); }
    inline void relayDisable() { forceKey->setLow(); }
    inline void relayToggle() { forceKey->toggle(); }
};

#endif

