#ifndef IF_H
#define  IF_H
#include "Action.h"
#include "IInput.h"
#include "IOValue.h"
#include <ESP8266WiFi.h>



class If : public Action
{
    public:
    If(Action *next, IInput *input, IOValue *conditions, int conditionSize);
    void Run();
    bool IsDone();
  private:
    IInput *mInput;
    IOValue *conditions;
    int conditionSize;
    bool result = false;
};

#endif
