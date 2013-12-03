// Author J Mills
// Date 12/1/2013

#include "InputContext.h"
#include <stdio.h>

InputContext::InputContext() {
	//Set all button events to do nothing
	int i, j;
	for(i = 0; i < BUTTON_STATES; i++) {
		for(j = 0; j < MAX_BUTTONS; j++) {
			ButtonEvents[i][j].function_pointer = do_nothing;
		}
	}
}

void InputContext::SetButtonEvent(int state, int button, void (*pt2Func)(void)) {
	ButtonEvents[state][button].function_pointer = pt2Func;
}

void InputContext::ExecuteEvent(int state, int button) {
	ButtonEvents[state][button].function_pointer();
}

// ----------------------------------------- //
//				Nonmember Functions			 //
// ----------------------------------------- //
void do_nothing()
{
	//function pointer will be set to this on initialization to prevent crashing
	return;
}