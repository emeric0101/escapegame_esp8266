#ifndef SEQUENCE_FACTORY_H
#define  SEQUENCE_FACTORY_H
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>


#include "Hardware.h"
#include "Action.h"
#include "Buzzer.h"
#include "If.h"
#include "LCD.h"
#include "Output.h"
#include "Wait.h"



class SequenceFactory
{
  public:
	SequenceFactory(Hardware &hw);
	void Load(String scenario);
  private:
	Hardware &hw;
};

#endif
