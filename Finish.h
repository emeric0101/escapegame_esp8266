#ifndef BUZZER_H
#define  BUZZER_H

#include "Action.h"
#include "IFinish.h"


class Finish : public Action 
{
  public:
    Finish(IFinish *finish, Action *next);
    void Run();
    bool IsDone();
  private:
    IFinish *mFinish;
};

#endif
