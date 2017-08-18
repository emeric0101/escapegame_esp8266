#ifndef WAIT_H
#define  WAIT_H
#include "Action.h"
#include <ESP8266WiFi.h>

class Wait
  : public Action 
{
  public:
    Wait(Action *next, int seconds);
    void Run();
    bool IsDone();
  private:
    int seconds;
};

#endif
