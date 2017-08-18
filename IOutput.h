#ifndef IOUTPUT_H
#define  IOUTPUT_H

class IOutput
{
  public:
    virtual void DigitalWrite(int channel, bool value) = 0;
};

#endif
