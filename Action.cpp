#include "Action.h"

Action::Action(Action *next) : nextAction(next)
{
  
}

Action* Action::GetNextAction() {
  return nextAction;
}

