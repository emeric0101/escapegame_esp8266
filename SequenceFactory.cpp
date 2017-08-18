#include "SequenceFactory.h"

SequenceFactory::SequenceFactory(Hardware &hw) : hw(hw) 
{
}

class StringList 
{
	public: 
		StringList(String txt, StringList *next) : txt(txt), next(next) {
			
		}
			
		int Count() {
			int i = 1;
			StringList *current = next;
			while (current != NULL) {
				i++;
				current = current->GetNext();
			}
			return i;
		}
		StringList* GetNext() {return next;}
		String GetTxt() {return txt;}
		void SetNext(StringList *v) {next = v;}
		void Add(String txt) 
		{
			if (next == NULL) {
				next = new StringList(txt, NULL);
				return;
			}
			StringList *current = next;
			StringList *later = next;
			while (current != NULL) {
				later = current;
				current = current->GetNext();
			}
			later->SetNext(new StringList(txt, NULL));
		}
	private:
		String txt;
		StringList *next = NULL;
};


StringList* SplitString(String str, char delimiter) 
{
	StringList *lines = NULL;
	String current = "";
	for (int i = 0; i< str.length();i++) 
	{
		if (str[i] == delimiter) 
		{
			if (lines == NULL) {
				lines = new StringList(current, NULL);
			}
			else {
				lines->Add(current);
			}
			current = "";
			continue;
		}
		current += str[i];
	}
	if (lines == NULL) {
		lines = new StringList(current, NULL);
	}
	else {
		lines->Add(current);
	}
	return lines;
}


void SequenceFactory::Load(String scenario) 
{
	scenario = "output:2=true,3=false,4=true;if:1=true,2=true;wait:5";
	Action *firstAction;
	StringList *currentStr = SplitString(scenario, ';');
	while (currentStr != NULL) {
		String content = currentStr->GetTxt();
		// Line by line
		StringList *currentWords = SplitString(content, ':');
		String action = currentWords->GetTxt();
		String args = currentWords->GetNext()->GetTxt();
		
		StringList *currentArgs = SplitString(args, ',');
		int nbArgs = currentArgs->Count();
		IOValue *IOArgs = new IOValue[nbArgs];
		int i = 0;
		while (currentArgs != NULL) {
			StringList *equal = SplitString(currentArgs->GetTxt(), '=');
			int nb = equal->Count();
			IOValue arg;
			arg.channel = atoi(equal->GetTxt().c_str());
			if (nb>1) {
				arg.result = equal->GetNext()->GetTxt() == "true";
			}
			Serial.println(arg.channel);
			Serial.println(arg.result);
			Serial.println(" ");
			IOArgs[i] = arg;
			currentArgs = currentArgs->GetNext();
			i++;

		}
		Action *current;
		if (action == "output") {
			current = new Output(NULL, &hw, IOArgs, nbArgs);
		}

		if (firstAction == NULL) {
			firstAction = current;
		}
		else {
			//firstAction.Add(current); FIXME!!
		}
		currentStr = currentStr->GetNext();
	}

}