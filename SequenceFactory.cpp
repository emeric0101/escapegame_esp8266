#include "SequenceFactory.h"
#include <EEPROM.h>
SequenceFactory::SequenceFactory(Hardware &hw) : hw(hw) 
{
}
int SequenceFactory::GetDuration() {
	return duration;
}
Action* SequenceFactory::GetActions() {
	return firstAction;
}

void SequenceFactory::SaveInEeprom(String json) {
	int jsonSize = json.length()+1;
	EEPROM.begin(10000);
	Serial.println(jsonSize);
	EEPROM.write(0, highByte(jsonSize)); //write the first half
	EEPROM.write(1, lowByte(jsonSize)); //write the second half
	for (int i = 0; i < json.length(); ++i)
	{
	  EEPROM.write(2+ i, json[i]);
	}
	EEPROM.commit();
}

bool SequenceFactory::LoadFromEeprom()
{
	EEPROM.begin(10000);
	Serial.println("Reading EEPROM...");
	byte high = EEPROM.read(0); //read the first half
	byte low = EEPROM.read(1); //read the second half

	int size = (high << 8) + low; //reconstruct the integerS
	Serial.print("EEPROM size");
	Serial.println(size);
	if (size < 10) {
		Serial.println("EEPROM EMPTY");
		return false;
	}
	  
	String json;
	for (int i = 2; i < size+1; ++i)
	{
	  json += char(EEPROM.read(i));
	}
	Serial.println(size);
	Serial.print("JSON: ");
	Serial.println(json);	
	return Load(json);
}

bool SequenceFactory::Load(String scenario) 
{		
	Serial.println("Loading scenario...");
	const size_t bufferSize = 10*42*JSON_ARRAY_SIZE(1) + 6*JSON_ARRAY_SIZE(2) + 12*JSON_ARRAY_SIZE(3) + JSON_ARRAY_SIZE(33) + 7*JSON_OBJECT_SIZE(2) + 30*JSON_OBJECT_SIZE(3) + 1450;
	DynamicJsonBuffer jsonBuffer(bufferSize);

	JsonObject& root = jsonBuffer.parseObject(scenario);
	duration = root["time"]; // 60

	JsonArray& enigme = root["enigme"];
	if (root["enigme"].size() == 0) {
		Serial.println("NOT VALID JSON");
		return false;
	}
	for (int i=0;i<root["enigme"].size();i++) {
		Action* currentAction;
		JsonObject& currentActionJson = enigme[i];
		String type = currentActionJson["type"];
		// Args
		JsonArray& argsJson = currentActionJson["arg1"];
		JsonArray& resultJson = currentActionJson["result"];
		IOValue *args = new IOValue[argsJson.size()];
		Serial.println(type);
		for (int a=0;a<argsJson.size(); a++) {
			args[a].channel = argsJson[a];
			args[a].result = resultJson[a];
		}
		
		if (type == "output") {
			currentAction = new Output(NULL, &hw, args, static_cast<int>(argsJson.size()));
		}
		if (type == "if") {
			currentAction = new If(NULL, &hw, args, static_cast<int>(argsJson.size()));
		}
		if (type == "buzzer") {
			currentAction = new Buzzer(NULL, &hw, args[0].channel);
		}
		if (type == "lcd") {
			currentAction = new LCD(NULL, &hw, currentActionJson["msg"]["fr"], currentActionJson["msg"]["en"]);
		}
		if (type == "wait") {
			currentAction = new Wait(NULL, args[0].channel);
		}
		
		if (firstAction == NULL)
			firstAction = currentAction;
		else
			firstAction->Add(currentAction);
		
	}
	return true;
}