#include <Color.h>
#include <math.h>

Color::Color(const String &hex)
{
    value = (int) strtol(hex.c_str(), 0, 16);
}

Color::Color(float redf, float greenf, float bluef)
{
    int red = (int) roundf(redf * 255);
    int green = (int) roundf(greenf * 255);
    int blue = (int) roundf(bluef * 255);
    value = (red << 16) | (green << 8) | blue;
}

String Color::getHex() const
{
    return value != 0 ? String(value, HEX) : "000000";
}

float Color::getRed() const
{
    return (float) ((value >> 16) & 0xff) / 255;
}

float Color::getGreen() const
{
    return (float) ((value >> 8) & 0xff) / 255;
}

float Color::getBlue() const
{
    return (float) (value & 0xff) / 255;
}