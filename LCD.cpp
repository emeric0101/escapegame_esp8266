#include "LCD.h"

LCD::LCD(Action *next, ILCD *lcd, String msgFr, String msgEn) : Action(next), mLcd(lcd), msgFr(msgFr), msgEn(msgEn)
{
  
}

bool LCD::IsDone() {
  return true;
}

void LCD::Run() {
	if (mLcd->GetLanguage() == "fr") {
		  mLcd->LcdMessage(msgFr);
	}
	else {
		  mLcd->LcdMessage(msgEn);
	}
}

