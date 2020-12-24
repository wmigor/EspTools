#ifndef LedRgbControl_h
#define LedRgbControl_h

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <WiFiControl.h>
#include <ForceKey.h>
#include <Color.h>
#include <Mode.h>
#include <vector>

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
	std::vector<Mode> modes;
	int modeIndex;
	Mode defaultMode;

    void serverHandleInfo();
    void serverHandleColor();
	void serverHandleNextMode();
	void setModeIndex(int index);
	Mode createMode(const std::vector<Color> &colors, unsigned long time, bool instant, int delta);
};

#endif
