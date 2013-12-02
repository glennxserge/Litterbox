#ifndef INPUTMANAGER
#define INPUTMANAGER

//! \file InputManager.h
//! \author J Mills
//! \date 12/1/2013 

#include <nds.h>
#include "InputContext.h"

//! \addtogroup grpInputManager
//\{

/*! \class InputManager
 *	Handles querying input and dispatching appropriate events via mapped InputContexts
 */
class InputManager
{
public:
	//! Constructor, currently here for posterity, doesn't do anything
	InputManager();
	//! Destructor, currently here for posterity, currently there isn't any clean up needed
	~InputManager();
	//! Polls for input and executes functions
	bool HandleInput();
	//! Assigns an InputContext
	//! \param *ic A pointer to an InputContext
	void SetContext(InputContext *ic);
	
private:
	int _pressed;			//!< _pressed The state of all buttons that have just been pressed
	int _released;			//!< _released The state of all buttons that have just been released
	int _held;				//!< _held The state of all buttons that are currently held
	touchPosition _touch;	//!< _touch The coordinates of the touched position
	InputContext *IC;		//!< *IC A pointer to the InputContext used for mapped button functions
};

//\}
#endif //INPUTMANAGER