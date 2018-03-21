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
	/*  Serial.print(" | ");
	  Serial.print(conditions[i].channel);
	  Serial.print(" ");
	  Serial.print((mInput->DigitalRead(conditions[i].channel) == conditions[i].result));*/
    result *= (mInput->DigitalRead(conditions[i].channel) == conditions[i].result);
  }
  //.println();
}

