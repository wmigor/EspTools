#include <LedRgbControl.h>

LedRgbControl::LedRgbControl(const String &name, const String &url, int redPin, int greenPin, int bluePin, int value, int maxValue, int delta, ESP8266WebServer *server):
    WiFiControl(name, url, "LedRgb", server),
    redKey(redPin, value, maxValue, delta),
    greenKey(greenPin, value, maxValue, delta),
    blueKey(bluePin, value, maxValue, delta),
    color(1, 1, 1),
	modeIndex(-1),
	defaultMode(&redKey, &greenKey, &blueKey, {Mode::Phase(Color(1, 1, 1), 0xFFFFFFFFul, false, delta)})
{
	std::vector<Color> colors = {
		Color(1, 0, 0),
		Color(0, 1, 0),
		Color(0, 0, 1),
		Color(1, 1, 0),
		Color(1, 0, 1),
		Color(0, 1, 1),
	};
	
	modes.push_back(createMode(colors, 2000ul, false, 10));
	modes.push_back(createMode(colors, 10000ul, false, 50));
	modes.push_back(createMode(colors, 1000ul, true, 1024));
	modes.push_back(createMode(colors, 500ul, true, 1024));
	modes.push_back(createMode(colors, 250ul, true, 1024));
}

void LedRgbControl::setup()
{
    redKey.setup();
    greenKey.setup();
    blueKey.setup();

	defaultMode.onEnter();

    getServer()->on(getUrl(), std::bind(&LedRgbControl::serverHandleInfo, this));
    getServer()->on(getUrl() + "/color", std::bind(&LedRgbControl::serverHandleColor, this));
	getServer()->on(getUrl() + "/next_mode", std::bind(&LedRgbControl::serverHandleNextMode, this));
}

void LedRgbControl::update()
{
    redKey.update();
    greenKey.update();
    blueKey.update();

	if (modeIndex >= 0 && (size_t) modeIndex < modes.size())
		modes[modeIndex].update();
}

void LedRgbControl::setEnabled(bool enabled)
{
	setModeIndex(-1);

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
	message += "<br><a href=\"" + getUrl() + "/next_mode\">next mode</a>";
    message += "<br>Red: " + String(redKey.getRatio());
    message += "<br>Green: " + String(greenKey.getRatio());
    message += "<br>Blue: " + String(blueKey.getRatio());
	message += "<br>Mode; " + String(modeIndex);
    getServer()->send(200, "text/html", message);
}

void LedRgbControl::serverHandleColor()
{
	setModeIndex(-1);

    String hex = getServer()->arg("color");
    if (hex == "")
    {
        Color realColor(redKey.getRatio(), greenKey.getRatio(), blueKey.getRatio());
        getServer()->send(200, "text/plain", realColor.getHex());
        return;
    }
	defaultMode.phases[0].color = color;
    color = Color(hex);
    redKey.setRatio(color.getRed());
    greenKey.setRatio(color.getGreen());
    blueKey.setRatio(color.getBlue());
    redKey.update();
    greenKey.update();
    blueKey.update();
    getServer()->send(200, "text/plain", "OK");
}

void LedRgbControl::serverHandleNextMode()
{
	auto index = modeIndex + 1;
	if ((size_t) index >= modes.size())
		index = -1;
	setModeIndex(index);
	getServer()->send(200, "text/plain", "OK");
}

void LedRgbControl::setModeIndex(int index)
{
	modeIndex = index;
	
	if (modeIndex < 0 || (size_t) modeIndex >= modes.size())
		defaultMode.onEnter();
	else
		modes[index].onEnter();

}

Mode LedRgbControl::createMode(const std::vector<Color> &colors, unsigned long time, bool instant, int delta)
{
	std::vector<Mode::Phase> phases;

	for (auto color : colors)
		phases.push_back(Mode::Phase(color, time, instant, delta));

	return Mode(&redKey, &greenKey, &blueKey, phases);
}
