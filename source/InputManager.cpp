// Author J Mills
// Date 12/1/2013

#include "InputManager.h"

//Constructor
InputManager::InputManager(){

}

//Destructor
InputManager::~InputManager()
{
	//Clean up goes here
}

//Polls the inputs and executes events
bool InputManager::HandleInput(){
	scanKeys();
	_pressed = keysDown();
	_released = keysUp();
	_held = keysHeld();
	touchRead(&_touch);
	
	if(_pressed & KEY_A) IC->ExecuteEvent(BUTTON_PRESSED, BUTTON_A);
	if(_pressed & KEY_B) IC->ExecuteEvent(BUTTON_PRESSED, BUTTON_B);
	if(_pressed & KEY_X) IC->ExecuteEvent(BUTTON_PRESSED, BUTTON_X);
	if(_pressed & KEY_Y) IC->ExecuteEvent(BUTTON_PRESSED, BUTTON_Y);
	if(_pressed & KEY_UP) IC->ExecuteEvent(BUTTON_PRESSED, BUTTON_UP);
	if(_pressed & KEY_DOWN) IC->ExecuteEvent(BUTTON_PRESSED, BUTTON_DOWN);
	if(_pressed & KEY_LEFT) IC->ExecuteEvent(BUTTON_PRESSED, BUTTON_LEFT);
	if(_pressed & KEY_RIGHT) IC->ExecuteEvent(BUTTON_PRESSED, BUTTON_RIGHT);
	if(_pressed & KEY_L) IC->ExecuteEvent(BUTTON_PRESSED, BUTTON_L);
	if(_pressed & KEY_R) IC->ExecuteEvent(BUTTON_PRESSED, BUTTON_R);
	if(_pressed & KEY_TOUCH) IC->ExecuteEvent(BUTTON_PRESSED, BUTTON_TOUCH);
	if(_pressed & KEY_START) IC->ExecuteEvent(BUTTON_PRESSED, BUTTON_START);
	if(_pressed & KEY_SELECT) IC->ExecuteEvent(BUTTON_PRESSED, BUTTON_SELECT);
	
	if(_held & KEY_A) IC->ExecuteEvent(BUTTON_HELD, BUTTON_A);
	if(_held & KEY_B) IC->ExecuteEvent(BUTTON_HELD, BUTTON_B);
	if(_held & KEY_X) IC->ExecuteEvent(BUTTON_HELD, BUTTON_X);
	if(_held & KEY_Y) IC->ExecuteEvent(BUTTON_HELD, BUTTON_Y);
	if(_held & KEY_UP) IC->ExecuteEvent(BUTTON_HELD, BUTTON_UP);
	if(_held & KEY_DOWN) IC->ExecuteEvent(BUTTON_HELD, BUTTON_DOWN);
	if(_held & KEY_LEFT) IC->ExecuteEvent(BUTTON_HELD, BUTTON_LEFT);
	if(_held & KEY_RIGHT) IC->ExecuteEvent(BUTTON_HELD, BUTTON_RIGHT);
	if(_held & KEY_L) IC->ExecuteEvent(BUTTON_HELD, BUTTON_L);
	if(_held & KEY_R) IC->ExecuteEvent(BUTTON_HELD, BUTTON_R);
	if(_held & KEY_TOUCH) IC->ExecuteEvent(BUTTON_HELD, BUTTON_TOUCH);
	if(_held & KEY_START) IC->ExecuteEvent(BUTTON_HELD, BUTTON_START);
	if(_held & KEY_SELECT) IC->ExecuteEvent(BUTTON_HELD, BUTTON_SELECT);
	
	if(_released & KEY_A) IC->ExecuteEvent(BUTTON_RELEASED, BUTTON_A);
	if(_released & KEY_B) IC->ExecuteEvent(BUTTON_RELEASED, BUTTON_B);
	if(_released & KEY_X) IC->ExecuteEvent(BUTTON_RELEASED, BUTTON_X);
	if(_released & KEY_Y) IC->ExecuteEvent(BUTTON_RELEASED, BUTTON_Y);
	if(_released & KEY_UP) IC->ExecuteEvent(BUTTON_RELEASED, BUTTON_UP);
	if(_released & KEY_DOWN) IC->ExecuteEvent(BUTTON_RELEASED, BUTTON_DOWN);
	if(_released & KEY_LEFT) IC->ExecuteEvent(BUTTON_RELEASED, BUTTON_LEFT);
	if(_released & KEY_RIGHT) IC->ExecuteEvent(BUTTON_RELEASED, BUTTON_RIGHT);
	if(_released & KEY_L) IC->ExecuteEvent(BUTTON_RELEASED, BUTTON_L);
	if(_released & KEY_R) IC->ExecuteEvent(BUTTON_RELEASED, BUTTON_R);
	if(_released & KEY_TOUCH) IC->ExecuteEvent(BUTTON_RELEASED, BUTTON_TOUCH);
	if(_released & KEY_START) IC->ExecuteEvent(BUTTON_RELEASED, BUTTON_START);
	if(_released & KEY_SELECT) IC->ExecuteEvent(BUTTON_RELEASED, BUTTON_SELECT);
	
	return 1;
}

void InputManager::SetContext(InputContext *ic) {
	IC = ic;
}
