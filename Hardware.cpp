#include "Hardware.h"

Hardware::Hardware() 
{
  
}

void Hardware::Buzz(int frequency) 
{
  Serial.println("Buzz !");
}

void Hardware::LcdMessage(String msg) 
{
    Serial.println("Message lcd : " + msg);
}


bool Hardware::ReadInput(int channel)
{
  return false;
}

void Hardware::DigitalWrite(int channel, bool value)
{
  Serial.println("Digitalwrite : " + channel);
}

