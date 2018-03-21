#include "Ifraz.h"

Ifraz::Ifraz(Action *next, IInput *input) : Action(next), mInput(input)
{
  
}

Ifraz::~Ifraz() 
{
}

bool Ifraz::IsDone() {
  return result;
}

void Ifraz::Run() 
{
  result = true;
  for (int i=0;i<14;i++)
  {
	  if (i == 5) {continue;}
    result *= (mInput->DigitalRead(i) == false);
  }
  //Serial.print("RAZ : ");
  //Serial.println(result);
  
}

