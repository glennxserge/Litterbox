// Author J Mills
// Date 12/1/2013

#include "InputContext.h"
#include <stdio.h>

InputContext::InputContext() {
	//Set all button events to do nothing
	int i;
	for(i = 0; i < MAX_BUTTON_STATES; i++) {
		ButtonEvents[i].function_pointer = do_nothing;
	}
}

void InputContext::SetButtonEvent(int state, int button, void (*pt2Func)(void)) {
	ButtonEvents[MAX_BUTTONS*state+button].function_pointer = pt2Func;
}

void InputContext::ExecuteEvent(int state, int button) {
	ButtonEvents[MAX_BUTTONS*state+button].function_pointer();
}

// ----------------------------------------- //
//				Nonmember Functions			 //
// ----------------------------------------- //
void do_nothing()
{
	//function pointer will be set to this on initialization to prevent crashing
	return;
}