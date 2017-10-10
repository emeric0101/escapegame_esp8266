#include "Hardware.h"

Hardware::Hardware() 
{
  
}

Hardware::~Hardware() 
{
  delete lcd;
}
 

void Hardware::Init()
{
	// Check i2c connection for IO
	while (!checkHardware()) {
		delay(1000);
	}
	// Initialise l'ecran LCD
	lcd = new LiquidCrystal_I2C(SCREEN_ADDRESS,20,4);
	lcd->init();
	

	
	mcp1.begin(); // Utilise l'adresse par défaut qui est 0
	mcp2.begin(4);
	mcp3.begin(6);
	

 
	
	lcd->home();
	lcd->print("AGENCE LESS IS MORE - Starting...");
	lcd->backlight();
	
	// Init Out Carte LED
	for (int i=0; i<10;i++) {
		mcp2.pinMode(i, OUTPUT); 
	}
	// Init 3 led out Carte Led
	mcp2.pinMode(14, OUTPUT);
	mcp2.pinMode(13, OUTPUT);
	mcp2.pinMode(12, OUTPUT);
	// Init Buzzer Carte Led
	mcp2.pinMode(15, OUTPUT); 
	// Init langue, bypass
	mcp2.pinMode(10, INPUT);  // 17
	mcp2.pullUp(10, HIGH);
	mcp2.pinMode(11, INPUT); // 18
	mcp2.pullUp(11, HIGH);
	// Capteurs charge
	mcp3.pinMode(8, INPUT);
	mcp3.pinMode(9, INPUT);
	mcp3.pinMode(10, INPUT);
	mcp3.pullUp(8, HIGH);
	mcp3.pullUp(9, HIGH);
	mcp3.pullUp(10, HIGH);
	
	
	
	
	// Capteurs charges
	/*pinMode(12, INPUT_PULLUP);
	pinMode(13, INPUT_PULLUP);
	pinMode(15, INPUT); // no pullup on this input...
	
	pinMode(14, OUTPUT); // Sortie vers enigme suivante
	*/
	for (int i=0; i<16;i++) {
		mcp1.pinMode(i, INPUT); 
		mcp1.pullUp(i, HIGH); // turn on a 100K pullup internally
	}
	
	// Actionneurs charges
	mcp3.pinMode(2, OUTPUT); // charge 1
	mcp3.pinMode(3, OUTPUT); // charge 2
	mcp3.pinMode(4, OUTPUT); // charge 3
	
	// Séquence de test
	mcp2.digitalWrite(0, HIGH);
	mcp2.digitalWrite(2, HIGH);
	mcp2.digitalWrite(12, HIGH);
	delay(500);
	mcp2.digitalWrite(0, LOW);
	mcp2.digitalWrite(2, LOW);
	mcp2.digitalWrite(12, LOW);


	delay(500);
}

void Hardware::delayMs(uint32_t us){
  uint32_t start = micros();
  while(micros() - start < us){
	 yield();//give the system a chance to execute
  }
}

void Hardware::Buzz(int frequency) 
{
	int delay = ((1/frequency) * 1000000);
	for (int i=0;i<800;i++) {
		delayMs(delay);
		mcp2.digitalWrite(15, HIGH);
		delayMs(delay);
		mcp2.digitalWrite(15, LOW);
	}
}

void Hardware::print(String msg) {
	lcd->print(msg);
}

void Hardware::home() {
	lcd->home();
}

void Hardware::LcdMessage(String msg) 
{
	Serial.println(msg);
    lcd->clear();
	lcd->home();
	lcd->print(msg);
}
Adafruit_MCP23017 *Hardware::GetMcp1() {
	return &mcp1;
}

bool Hardware::DigitalRead(int channel)
{
  if (channel < 16)  {
	  return mcp1.digitalRead(channel) == LOW;
  }
  if (channel == 16) 
	  return mcp2.digitalRead(10) == LOW; // Key language

  if (channel == 17) 
	  return mcp2.digitalRead(11) == LOW; // Key BYPASS
  
  if (channel == 18)
	return mcp3.digitalRead(8) == LOW;  
  if (channel == 19)
	return mcp3.digitalRead(9) == LOW;  
  if (channel == 20)
	return mcp3.digitalRead(10) == LOW;
  
	Serial.println("DigitalRead : out of range :");
	Serial.println(channel);
  
}

int deviceAdress[] = {0x20, 0x24, 0x3f};

bool Hardware::checkHardware() {
	Wire.begin();
	byte error, address;
	for (address = 0; address < 3; address++ )  
	{
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(deviceAdress[address]);
		error = Wire.endTransmission();
		if (error != 0) {
			Serial.print("A I2C DEVICE IS NOT FOUND");
			Serial.println(deviceAdress[address]);

			return false;
		}
	}

	return true;
}

void Hardware::DigitalWrite(int channel, bool value)
{
	uint8_t v = HIGH;
	if (!value) {
		v = LOW;
	}
	if (channel < 10) { 

		mcp2.digitalWrite(channel, v);
	}
	if (channel == 11)
		mcp2.digitalWrite(12, v); // LED A
	if (channel == 12)
		mcp2.digitalWrite(13, v); // LED B
	if (channel == 13)
		mcp2.digitalWrite(14, v); // LED C
	
	if (channel == 14) // Sortie vers enigme suivante
		mcp3.digitalWrite(1, value);
		
	// Solenoides
	if (channel == 1000) 
		mcp3.digitalWrite(2, v);
	if (channel == 1001) 
		mcp3.digitalWrite(3, v);
	if (channel == 1002) 
		mcp3.digitalWrite(4, v);
	

}

