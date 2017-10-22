#include "Finish.h"

Finish::Finish(IFinish *finish, Action *next) : Action(next), mFinish(finish)
{
  
}

bool Finish::IsDone() {
  return false;
}

void Finish::Run() 
{
  mFinish->Finish();
}

