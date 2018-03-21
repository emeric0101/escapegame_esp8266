#ifndef IFRAZ_H
#define  IFRAZ_H
#include "Action.h"
#include "IInput.h"
#include "IOValue.h"
#include <ESP8266WiFi.h>



class Ifraz : public Action
{
    public:
    Ifraz(Action *next, IInput *input);
	~Ifraz();
    void Run();
    bool IsDone();
  private:
    IInput *mInput;
    bool result = false;
};

#endif
