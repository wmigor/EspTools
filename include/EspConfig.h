#ifndef EspConfig_h
#define EspConfig_h

#include <Arduino.h>

class EspConfig
{
public:
  EspConfig(const String &fileName);
  bool read();
  bool write();

  int value;
private:
  String fileName;
};

#endif
