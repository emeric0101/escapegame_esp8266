#ifndef ILCD_H
#define  ILCD_H

class ILCD 
{
  public:
    virtual void LcdMessage(String msg) = 0;
	virtual String GetLanguage() = 0;
};

#endif
