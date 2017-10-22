#ifndef CLOCK_H
#define  CLOCK_H

#include <ESP8266WiFi.h>



class Clock
{
    public:
		Clock(int duration);
		void Init();
		String GetCountDownString();
		bool IsEnded();
	private:
		unsigned long timeNow = 0;
		unsigned long timeLast = 0;
		int duration;
};

#endif
