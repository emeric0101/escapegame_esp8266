#include "SequenceManager.h"

SequenceManager::SequenceManager(Hardware &hw) : hw(&hw)
{
  Serial.println("Init");
}

void SequenceManager::Init(Action* firstAction) {
	  
  // Valeurs par defaut:
  	// led 3
	hw->DigitalWrite(11, true);
	hw->DigitalWrite(12, true);
	hw->DigitalWrite(13, true);
	// 10 leds blanche à eéro
	for (int i=0;i<10;i++) 
	{
		hw->DigitalWrite(i, false);
	}
	// solenoide coupés
	hw->DigitalWrite(1000, false);
	hw->DigitalWrite(1001, false);
	hw->DigitalWrite(1002, false);
	this->firstAction = firstAction;
	this->current = NULL;
  
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

