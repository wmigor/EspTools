#include <EspConfig.h>
#include <FS.h>

EspConfig::EspConfig(const String &fileName)
{
    this->fileName = fileName;
}

bool EspConfig::read()
{
    File file = SPIFFS.open(fileName, "r");
    if (!file)
        return false;
    value = file.parseInt();
    file.close();
    return true;
}

bool EspConfig::write()
{
    if (SPIFFS.exists(fileName))
        SPIFFS.remove(fileName);

    File file = SPIFFS.open(fileName, "w");
    if (!file)
        return false;

    file.printf("%i\n", value);
    file.close();
    return true;
}
