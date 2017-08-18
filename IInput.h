#ifndef INPUT_H
#define  INPUT_H

class IInput 
{
  public:
    virtual bool ReadInput(int channel) = 0;
};

#endif
