#include "LCD.h"

LCD::LCD(Action *next, ILCD *lcd, String msg) : Action(next), mLcd(lcd), msg(msg)
{
  
}

bool LCD::IsDone() {
  return true;
}

void LCD::Run() {
  mLcd->LcdMessage(msg);
}

