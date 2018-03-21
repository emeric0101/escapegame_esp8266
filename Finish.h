#ifndef FINISH_H
#define  FINISH_H

#include "Action.h"
#include "IFinish.h"


class Finish : public Action 
{
  public:
    Finish( Action *next, IFinish *finish);
    void Run();
    bool IsDone();
  private:
    IFinish *mFinish;
};

#endif
