#include "SequenceManager.h"

SequenceManager::SequenceManager(Hardware &hw) : hw(&hw)
{
  Serial.println("Init");
  IOValue *values = new IOValue[2];
  values[0].channel = 1;
  values[0].result = true;
  values[1].channel = 2;
  values[1].result = false;

  IOValue *conditions = new IOValue[1];
  conditions[0].channel = 0;
  conditions[0].result = false;
  Buzzer *buzzer = new Buzzer(NULL, &hw, 440);
  If *out = new If(buzzer, &hw, conditions, 1);
  LCD *lcd = new LCD(out, &hw, "Ceci est un message");
  Wait *wait = new Wait(lcd, 2);
  firstAction = new Output(wait, &hw, values, 2);
}

SequenceManager::~SequenceManager() 
{
  Action *a = firstAction;
  if (a == 0) {return;}
  while (a != 0) {
    Action *b = a;
    a = b->GetNextAction();
    delete b;
  }
}

void SequenceManager::Run()
{
  if (current == NULL) {
    current = firstAction;
    Serial.println("DONE");
    return;
  }
  current->Run();
  
  if (current->IsDone()) {
    current = current->GetNextAction();
  }
}

