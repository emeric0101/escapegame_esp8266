#ifndef BUZZER_H
#define  BUZZER_H

#include "Action.h"
#include "IBuzzer.h"


class Buzzer : public Action 
{
  public:
    Buzzer(Action *next, IBuzzer *buz, int frequency);
    void Run();
    bool IsDone();
  private:
    IBuzzer *mBuzzer;
    int frequency;
};

#endif
