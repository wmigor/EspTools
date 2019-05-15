#ifndef Settings_h
#define Settings_h

#include <Arduino.h>

class Settings
{
public:
    Settings(const String &fileName);
    bool load();
    bool save();
    inline int getLedColor() const { return ledColor; }
private:
    String fileName;
    int ledColor;
};

#endif
