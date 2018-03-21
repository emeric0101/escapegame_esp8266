#include "Finish.h"

Finish::Finish( Action *next, IFinish *finish) : Action(next), mFinish(finish)
{
  
}

bool Finish::IsDone() {
  return false;
}

void Finish::Run() 
{
  mFinish->Finish();
}

