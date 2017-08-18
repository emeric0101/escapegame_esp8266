#ifndef OUTPUT_H
#define  OUTPUT_H
#include <ESP8266WiFi.h>

#include "Action.h"
#include "IOutput.h"
#include "IOValue.h"

class Output :
  public Action
{
  public:
    Output(Action *next, IOutput *output, IOValue *v, int valueSize);
    void Run();
    bool IsDone();
  private:
    IOutput *mOutput;
    IOValue *values;
    int valueSize;
};

#endif
