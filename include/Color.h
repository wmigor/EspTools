#ifndef Color_h
#define Color_h

#include <Arduino.h>

class Color
{
public:
    Color(const String &hex);
    Color(float red, float green, float blue);
    inline int getValue() const { return value; }
    String getHex() const;
    float getRed() const;
    float getGreen() const;
    float getBlue() const;

private:
    int value;
};

#endif
