#include <Settings.h>
#include <FS.h>

Settings::Settings(const String &fileName)
{
    this->fileName = fileName;
}

bool Settings::load()
{
    if (!SPIFFS.exists(fileName))
    {
        return false;
    }

    File file = SPIFFS.open(fileName, "r");

    if (!file)
    {
        return false;
    }

    ledColor = file.parseInt();

    file.close();
    return true;
}

bool Settings::save()
{
    if (SPIFFS.exists(fileName))
    {
        if (!SPIFFS.remove(fileName))
            return false;
    }

    File file = SPIFFS.open(fileName, "w");

    if (!file)
    {
        return false;
    }

    file.printf("%i", ledColor);

    file.close();
    return true;
}