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
#include "Ifraz.h"
#include "Finish.h"



class SequenceFactory
{
  public:
	SequenceFactory(Hardware &hw);
	bool Load(String scenario);
	int GetDuration();
	Action* GetActions();
	void SaveInEeprom(String json);
	bool LoadFromEeprom();
  private:
	Hardware &hw;
	int duration = 0;
	Action *firstAction = NULL;
};

#endif
