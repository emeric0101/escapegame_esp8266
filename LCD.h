#ifndef LCD_H
#define  LCD_H
#include <ESP8266WiFi.h>

#include "Action.h"
#include "ILCD.h"

class LCD :
  public Action
{
  public:
    LCD(Action *next, ILCD *lcd, String msgFr, String msgEn);
    void Run();
    bool IsDone();
  private:
    ILCD *mLcd;
    String msgEn;
	String msgFr;
};

#endif
