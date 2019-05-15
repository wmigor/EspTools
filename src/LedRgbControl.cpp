#include <LedRgbControl.h>
#include <Color.h>

LedRgbControl::LedRgbControl(const String &name, const String &url, int redPin, int greenPin, int bluePin, int value, int maxValue, int delta, ESP8266WebServer *server):
    WiFiControl(name, url, "LedRgb", server),
    redKey(redPin, value, maxValue, delta),
    greenKey(redPin, value, maxValue, delta),
    blueKey(redPin, value, maxValue, delta)
{
}

void LedRgbControl::setup()
{
    getServer()->on(getUrl(), std::bind(&LedRgbControl::serverHandleInfo, this));
    getServer()->on(getUrl() + "/color", std::bind(&LedRgbControl::serverHandleColor, this));
}

void LedRgbControl::serverHandleInfo()
{
    String message = getName();
    message += "<br><a href=\"" + getUrl() + "/color\">color</a>";
    message += "<br>Red: " + String(redKey.getRatio());
    message += "<br>Green: " + String(greenKey.getRatio());
    message += "<br>Blue: " + String(blueKey.getRatio());
    getServer()->send(200, "text/html", message);
}

void LedRgbControl::serverHandleColor()
{
    String hex = getServer()->arg("color");
    if (hex == "")
    {
        Color color(redKey.getRatio(), greenKey.getRatio(), blueKey.getRatio());
        getServer()->send(200, "text/plain", color.getHex());
        return;
    }
    Color color(hex);
    redKey.setRatio(color.getRed());
    greenKey.setRatio(color.getGreen());
    blueKey.setRatio(color.getBlue());
    redKey.update();
    greenKey.update();
    blueKey.update();
    getServer()->send(200, "text/plain", "OK");
}
