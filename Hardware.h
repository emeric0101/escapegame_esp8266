#ifndef HARDWARE_H
#define  HARDWARE_H

#include <ESP8266WiFi.h>
#include <Adafruit_MCP23017.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include "IBuzzer.h"
#include "ILCD.h"
#include "IInput.h"
#include "IOutput.h"

#define SCREEN_ADDRESS 0x3f

class Hardware : 
  public IBuzzer,
  public ILCD,
  public IInput,
  public IOutput
{
  public:
    Hardware();
	~Hardware();
	void Init();
    void Buzz(int frequency);
    void LcdMessage(String msg);
    bool DigitalRead(int channel);
    void DigitalWrite(int channel, bool value);
	void print(String msg);
	String GetLanguage();
	void home();
	Adafruit_MCP23017 *GetMcp1();
			bool checkHardware();

	private:
		LiquidCrystal_I2C *lcd;
		Adafruit_MCP23017 mcp1, mcp2, mcp3;
		void delayMs(uint32_t us);
};

#endif
