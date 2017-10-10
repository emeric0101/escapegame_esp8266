#include "Action.h"
#include <ESP8266WiFi.h>

Action::Action(Action *next) : nextAction(next)
{
  
}

Action* Action::GetNextAction() {
  return nextAction;
}

void Action::Add(Action *next) {
	if (nextAction != NULL) {
		nextAction->Add(next);
	}
	else {
		nextAction = next;
	}
}
