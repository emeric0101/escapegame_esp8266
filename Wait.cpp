#include "Wait.h"

Wait::Wait(Action *next, int seconds) : Action(next), seconds(seconds)
{
  
}

void Wait::Run()
{
  delay(seconds*1000);
}

bool Wait::IsDone() {
  return true;
}

