#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <Adafruit_MCP23017.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Hardware.h"
#include "SequenceManager.h"
#include "SequenceFactory.h"
#include "Clock.h"



  Hardware hw;
  SequenceManager sequenceManager(hw);
	SequenceFactory sequenceFactory(hw);
enum Mode {
	NORMAL,
	TEST,
	PROG
};
  
Mode mode = NORMAL;
Adafruit_MCP23017 mcp;
Clock clock(3600);

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
	Serial.println("AGENCE LESS IS MORE SAS - 2018 Tous droits réservés.");
	delay(1000);
	Serial.println("ESPCTRT 1.1");
	
	hw.Init();
	hw.Buzz(440);
	hw.LcdMessage("HOLD B1 TO TEST MODE\nHOLD B2 TO PROG MODE");
	
	for (int i=0;i<10;i++) {
		if (hw.DigitalRead(8)) {
			hw.LcdMessage("-- TEST MODE --\n\nLoading...");
			mode = TEST;
			break;
		}
		else if (hw.DigitalRead(9)) {
			hw.LcdMessage("-- PROG MODE --\n\nPlease see instruction in Serial");
			mode = PROG;
			break;

		}
		delay(500);
	}
	


	if (mode == PROG) {
		
		/**
		Programmation : PROG puis entrée, saisir le JSON puis entrée, puis ;END; puis entrée
		*/
		//String jsontest = "{\"time\":60,\"enigme\":[{\"type\":\"output\",\"arg1\":[4,5,7],\"result\":[true,true,true]},{\"type\":\"if\",\"arg1\":[2,8,11],\"result\":[true,false,false]},{\"type\":\"if\",\"arg1\":[2],\"result\":[false]},{\"type\":\"wait\",\"arg1\":[2],\"result\":[false]},{\"type\":\"output\",\"arg1\":[4],\"result\":[false]},{\"type\":\"buzzer\",\"arg1\":[440],\"result\":[false]},{\"type\":\"output\",\"arg1\":[1000],\"result\":[true]},{\"type\":\"if\",\"arg1\":[18],\"result\":[false]},{\"type\":\"output\",\"arg1\":[1000],\"result\":[false]},{\"type\":\"lcd\",\"msg\":{\"fr\":\"Etape 1 : OK\nRebrancher cables\",\"en\":\"Step 1 : Done\nReconnect wires\"}},{\"type\":\"if\",\"arg1\":[8,11],\"result\":[true,true]}]}";
		//Serial.println(jsontest);
		Serial.println("Enter \"PROG\" then Enter, put your JSON then Enter, end with \";END;\" ");
		bool valid = false;
		// Verif chaine
		while (!valid)
		{
			String data = Serial.readString();
			if (data == "PROG") {
				valid = true;
			}
			delay(10);

		}
		String currentChar = "";
		String json = "";
		Serial.println("JSON?");

		while (currentChar != ";END;") {
			currentChar = Serial.readString();
			if (currentChar != ";END;")
				json += currentChar;
			delay(10);
		}
		Serial.println("Saving...");
		Serial.println(json);
		hw.LcdMessage("PROGRAMMING...");

		sequenceFactory.SaveInEeprom(json);
		hw.LcdMessage("DONE\n\nPLEASE RESTART");
		while (true)
		{
			delay(1000);
		}

	}
	if (mode == NORMAL) {
		hw.LcdMessage("LOADING PROGRAM...");
		if (!sequenceFactory.LoadFromEeprom()) {
			Serial.println("Unable to load from EEPROM");
			hw.LcdMessage("ERROR : UNABLE TO LOAD EEPROM\n\nNO PROGRAM");
			while (true) {
				delay(100);
			}
		}

		Init();
	}
}

void Init() {
	hw.LcdMessage("STARTING PROGRAM...");
	sequenceManager.Init(sequenceFactory.GetActions());
	hw.LcdMessage("READY\n\nA1 to ON to start");
	while (!hw.DigitalRead(22)) {
		delay(100);
	}
	hw.LcdMessage("STARTING IN \n\n3");
	delay(1000);		hw.LcdMessage("STARTING IN \n\n2");
	delay(1000);		hw.LcdMessage("STARTING IN \n\n1");
	delay(1000);		hw.LcdMessage("\n##### GO #####");
	hw.Start();
	clock.Init();
}

void loop()
{
	delay(50);	
	if (mode == TEST) {
		// Test solenoide

		while (!hw.DigitalRead(9)) {
			hw.home();
			hw.print("PUSH LBlue to exit : HIGH");
			hw.DigitalWrite(1000, HIGH);
			hw.DigitalWrite(1001, HIGH);
			hw.DigitalWrite(1002, HIGH);
			hw.home();
			delay(1000);

			hw.print("PUSH LBLUe to exit : LOW");
			hw.DigitalWrite(1000, LOW);
			hw.DigitalWrite(1001, LOW);
			hw.DigitalWrite(1002, LOW);
			delay(1000);

		}

		for (int i=0;i<14;i++) {
			hw.home();
			String index(i);
			hw.print("Testing led... ");
			hw.print(index);
			if (i != 0) {
				hw.DigitalWrite(i-1, LOW);
			}
			hw.DigitalWrite(i, HIGH);
			delay(500);
		}
		
		
		for (int i=0;i<14;i++) {
			if (i == 15) continue;
			if (i== 5) continue;

			hw.LcdMessage("");
			String index(i);
			Serial.print("Testing J");
			Serial.println(i);
			if (hw.DigitalRead(i)) {
				hw.print("ERROR B1 to continue");
				hw.print(index);
				while (!hw.DigitalRead(8)) {
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
		hw.LcdMessage("TEST DONE");
	}
	else if (mode == NORMAL) 
	{
		hw.SetClock(clock.GetCountDownString());
		// si fin du jeu (time ou manuel)
		if (clock.IsEnded() || !hw.DigitalRead(22)) {
			hw.LcdMessage("TORPILLE READY...\n");
			delay(2000);
			String progress = "IGNITION...\n";
			for (int i=0;i<15;i++) {
				progress = progress + "#";
				hw.LcdMessage(progress);
				delay(100);
			}

			hw.LcdMessage("GAME OVER\nPLEASE SET A1 OFF TO RESTART");
			while (hw.DigitalRead(22)) {
				delay(100);
			}
			Init();
			return;
		}
		sequenceManager.Run();

	}
	// Manage bypass
	hw.ManageBypass();

}



