#include "Clock.h"

Clock::Clock(int duration) : duration(duration)
{
	
}

void Clock::Init()
{
	timeNow = millis()/1000;
	timeLast = timeNow;
}

String Clock::GetCountDownString()
{
	// Si pas démarré
	if (timeNow == 0) {
		return "";
	}
	timeNow = millis()/1000;
	int totalSeconds = duration - (timeNow - timeLast);
	int minutes = totalSeconds/60;
	String txt = "";
	
	if (minutes < 10) 
		txt = txt + "0" + String(minutes) + ":";
	else
		txt = txt  + String(minutes) + ":";
	
	int seconds = totalSeconds%60;
		
	if (seconds < 10)
		txt = txt + "0" + String(seconds);
	else
		txt = txt + String(seconds);
		
	return txt;
}

bool Clock::IsEnded(){
	int totalSeconds = duration - (timeNow - timeLast);
	if (totalSeconds < 1) {
		return true;
	}
	else 
		return false;
}