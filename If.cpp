#include "If.h"

If::If(Action *next, IInput *input, IOValue *conditions, int conditionSize) : Action(next), mInput(input), conditions(conditions), conditionSize(conditionSize)
{
  
}

If::~If() 
{
	delete conditions;
}

bool If::IsDone() {
  return result;
}

void If::Run() 
{
  result = true;
  for (int i=0;i<conditionSize;i++)
  {
    result *= (mInput->ReadInput(conditions[i].channel) == conditions[i].result);
  }
}

