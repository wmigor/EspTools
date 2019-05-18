#include <LedRgbControl.h>

LedRgbControl::LedRgbControl(const String &name, const String &url, int redPin, int greenPin, int bluePin, int value, int maxValue, int delta, ESP8266WebServer *server):
    WiFiControl(name, url, "LedRgb", server),
    redKey(redPin, value, maxValue, delta),
    greenKey(greenPin, value, maxValue, delta),
    blueKey(bluePin, value, maxValue, delta),
    color(1, 1, 1)
{
}

void LedRgbControl::setup()
{
    redKey.setup();
    greenKey.setup();
    blueKey.setup();

    getServer()->on(getUrl(), std::bind(&LedRgbControl::serverHandleInfo, this));
    getServer()->on(getUrl() + "/color", std::bind(&LedRgbControl::serverHandleColor, this));
}

void LedRgbControl::update()
{
    redKey.update();
    greenKey.update();
    blueKey.update();
}

void LedRgbControl::setEnabled(bool enabled)
{
    if (enabled)
    {
        redKey.setRatio(color.getRed());
        greenKey.setRatio(color.getGreen());
        blueKey.setRatio(color.getBlue());
    }
    else
    {
        redKey.setRatio(0);
        greenKey.setRatio(0);
        blueKey.setRatio(0);
    }
}

bool LedRgbControl::isEnabled() const
{
    return !redKey.isLow() || !greenKey.isLow() || !blueKey.isLow();
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
        Color realColor(redKey.getRatio(), greenKey.getRatio(), blueKey.getRatio());
        getServer()->send(200, "text/plain", realColor.getHex());
        return;
    }
    color = Color(hex);
    redKey.setRatio(color.getRed());
    greenKey.setRatio(color.getGreen());
    blueKey.setRatio(color.getBlue());
    redKey.update();
    greenKey.update();
    blueKey.update();
    getServer()->send(200, "text/plain", "OK");
}
