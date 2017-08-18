#include "Buzzer.h"

Buzzer::Buzzer(Action *next, IBuzzer *buz, int frequency) : Action(next), mBuzzer(buz) , frequency(frequency)
{
  
}

bool Buzzer::IsDone() {
  return true;
}

void Buzzer::Run() 
{
  mBuzzer->Buzz(frequency);
}

