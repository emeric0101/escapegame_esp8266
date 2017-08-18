#include <ESP8266WiFi.h>
#include "Hardware.h"
#include "SequenceManager.h"

  Hardware hw;
  SequenceManager sequenceManager(hw);

void setup(void){
  delay(1000);
  WiFi.mode(WIFI_OFF);
  Serial.begin(115200);
  Serial.println("Coucou");

  

}
void loop()
{
  sequenceManager.Run();
}
