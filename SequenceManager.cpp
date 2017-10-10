#include "SequenceManager.h"

SequenceManager::SequenceManager(Hardware &hw) : hw(&hw)
{
  Serial.println("Init");
  IOValue *values = new IOValue[1];
  values[0].channel = 0;
  values[0].result = true;
  
    IOValue *values2 = new IOValue[1];
  values2[0].channel = 0;
  values2[0].result = false;


  IOValue *conditions = new IOValue[1];
  conditions[0].channel = 0;
  conditions[0].result = false;
  LCD *lcd2 = new LCD(NULL, &hw, "Ca va ?");
  Output *output2 = new Output(lcd2, &hw, values2, 1);
  Buzzer *buzzer = new Buzzer(output2, &hw, 440);
  If *out = new If(buzzer, &hw, conditions, 1);
  LCD *lcd = new LCD(out, &hw, "Coucou");
  Wait *wait = new Wait(lcd, 2);
  firstAction = new Output(wait, &hw, values, 1);
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
  delay(1000);
  
  if (current->IsDone()) {
    current = current->GetNextAction();
  }
}

