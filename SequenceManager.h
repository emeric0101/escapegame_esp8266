#ifndef SEQUENCE_MANAGER_H
#define  SEQUENCE_MANAGER_H

#include "Hardware.h"
#include "Action.h"

#include "Buzzer.h"
#include "If.h"
#include "LCD.h"
#include "Output.h"
#include "Wait.h"

class SequenceManager 
{
  public:
    SequenceManager(Hardware &hw);
    ~SequenceManager();
    void Run();
	void Init(Action* firstAction);
  private:
    Hardware *hw;
    Action *firstAction = NULL;
    Action *current = NULL;
};

#endif
