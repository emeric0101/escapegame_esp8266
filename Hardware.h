#ifndef HARDWARE_H
#define  HARDWARE_H

#include <ESP8266WiFi.h>
#include "IBuzzer.h"
#include "ILCD.h"
#include "IInput.h"
#include "IOutput.h"

class Hardware : 
  public IBuzzer,
  public ILCD,
  public IInput,
  public IOutput
{
  public:
    Hardware();
    void Buzz(int frequency);
    void LcdMessage(String msg);
    bool ReadInput(int channel);
    void DigitalWrite(int channel, bool value);
};

#endif
