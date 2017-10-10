#include "SequenceFactory.h"

SequenceFactory::SequenceFactory(Hardware &hw) : hw(hw) 
{
}
int SequenceFactory::GetDuration() {
	return duration;
}
Action* SequenceFactory::GetActions() {
	return firstAction;
}


void SequenceFactory::Load(String scenario) 
{		
	const size_t bufferSize = 42*JSON_ARRAY_SIZE(1) + 6*JSON_ARRAY_SIZE(2) + 12*JSON_ARRAY_SIZE(3) + JSON_ARRAY_SIZE(33) + 7*JSON_OBJECT_SIZE(2) + 30*JSON_OBJECT_SIZE(3) + 1450;
	DynamicJsonBuffer jsonBuffer(bufferSize);

	const char* json = "{\"time\":60,\"enigme\":[{\"type\":\"output\",\"arg1\":[4,5,7],\"result\":[true,true,true]},{\"type\":\"if\",\"arg1\":[2,8,11],\"result\":[true,false,false]},{\"type\":\"if\",\"arg1\":[2],\"result\":[false]},{\"type\":\"wait\",\"arg1\":[2],\"result\":[false]},{\"type\":\"output\",\"arg1\":[4],\"result\":[false]},{\"type\":\"buzzer\",\"arg1\":[440],\"result\":[false]},{\"type\":\"output\",\"arg1\":[1000],\"result\":[true]},{\"type\":\"if\",\"arg1\":[18],\"result\":[false]},{\"type\":\"output\",\"arg1\":[1000],\"result\":[false]},{\"type\":\"lcd\",\"msg\":{\"fr\":\"Etape 1 : OK\nRebrancher cables\",\"en\":\"Step 1 : Done\nReconnect wires\"}},{\"type\":\"if\",\"arg1\":[8,11],\"result\":[true,true]}]}";
	JsonObject& root = jsonBuffer.parseObject(json);
	duration = root["time"]; // 60

	JsonArray& enigme = root["enigme"];
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
}