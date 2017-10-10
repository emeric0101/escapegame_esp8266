#ifndef ACTION_H
#define  ACTION_H

class Action 
{
  public:
    Action(Action *next);
    Action* GetNextAction();
    virtual void Run() = 0;
    virtual bool IsDone() = 0;
	void Add(Action *next);

  private:
    Action *nextAction = 0;
};

#endif
