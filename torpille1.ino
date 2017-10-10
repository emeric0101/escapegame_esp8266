#include <ESP8266WiFi.h>

#include <Adafruit_MCP23017.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Hardware.h"
#include "SequenceManager.h"
#include "SequenceFactory.h"

  Hardware hw;
  SequenceManager sequenceManager(hw);

bool testMode = false;
Adafruit_MCP23017 mcp;

void i2c() {
	Wire.begin();
	byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(500);           // 
}

void setup(void){

WiFi.mode(WIFI_OFF);
	
	Serial.begin(115600);
	delay(1000);
	
	Serial.println();

	i2c();

	
	Serial.println();
	Serial.println("AGENCE LESS IS MORE SAS - 2017 Tous droits réservés.");
	delay(1000);
	Serial.println("ESPCTRT 1.0");
	
	hw.Init();
	//hw.Buzz(440);
	hw.LcdMessage("HOLD J2 TO TEST MODE");
	
	for (int i=0;i<10;i++) {
		hw.print(".");
		if (hw.DigitalRead(1)) {
			Serial.println("Test mode");
			hw.LcdMessage("TEST MODE");
			testMode = true;
			break;
		}
		delay(500);
	}
	if (!testMode) {
		hw.LcdMessage("Starting torpille...");
		SequenceFactory sequenceFactory(hw);
		sequenceFactory.Load("");
		
		sequenceManager.Init(sequenceFactory.GetDuration(), sequenceFactory.GetActions());

	}





}
void loop()
{
	delay(50);	

	if (testMode) {
		// Test solenoide

		while (!hw.DigitalRead(2)) {
			hw.home();
			hw.print("PUSH J3 HIGH");
			hw.DigitalWrite(1000, HIGH);
			hw.DigitalWrite(1001, HIGH);
			hw.DigitalWrite(1002, HIGH);
			hw.home();
			delay(1000);

			hw.print("PUSH J3 LOW");
			hw.DigitalWrite(1000, LOW);
			hw.DigitalWrite(1001, LOW);
			hw.DigitalWrite(1002, LOW);
			delay(1000);

		}

		for (int i=0;i<14;i++) {
			if (i != 0) {
				hw.DigitalWrite(i-1, LOW);
			}
			hw.DigitalWrite(i, HIGH);
			delay(500);
		}
		
		
		for (int i=17;i<21;i++) {
			hw.LcdMessage("");
			String index(i);
			if (hw.DigitalRead(i)) {
				hw.print("ERROR J ");
				hw.print(index);
				while (!hw.DigitalRead(1)) {
					delay(100);
				}
			}
			hw.home();
			hw.print("PUSH J ");
			hw.print(index);
			while (!hw.DigitalRead(i)) {
				delay(100);
			}
			hw.print(" OK");
		}
		testMode = false;
		hw.LcdMessage("TEST DONE");
	}
	

	sequenceManager.Run();

}



