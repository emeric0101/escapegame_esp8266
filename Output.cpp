#include "Output.h"

Output::Output(Action *next, IOutput *output, IOValue *v, int valueSize) : Action(next), mOutput(output), values(v), valueSize(valueSize)
{
  values = v;
}

void Output::Run() {
  if (values == NULL) {return;}
  for (int i = 0; i<valueSize;i++) {
    mOutput->DigitalWrite(values[i].channel, values[i].result);
  }
}
bool Output::IsDone() {
  return true;
}
Output::~Output() 
{
	delete values;
}
