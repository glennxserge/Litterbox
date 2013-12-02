#ifndef INPUTCONTEXT_H
#define INPUTCONTEXT_H

//! \file InputContext.h
//! \author J Mills
//! \date 12/1/2013 

#include "Event.h"
#include "Defines.h"

//! \addtogroup grpInputManager

/*!	\defgroup grpInputContext InputContext
 *	\brief	Class containing events for each button state on the DS, is mappable
 *	\ingroup grpInputManager
 */
//\{

//! \enum BUTTON_STATE enumeration
enum BUTTON_STATE {
	BUTTON_PRESSED,		//!< Button pressed state, 	0
	BUTTON_HELD,		//!< Button held state, 	1
	BUTTON_RELEASED		//!< Button released state, 2
};

//! \enum BUTTON_IDS enumeration
enum BUTTON_IDS {
  BUTTON_A,			//!< A, 			0
  BUTTON_B,			//!< B, 			1
  BUTTON_SELECT,	//!< Select, 		2
  BUTTON_START,		//!< Start, 		3
  BUTTON_RIGHT,		//!< D-Pad Right, 	4
  BUTTON_LEFT,		//!< D-Pad Left, 	5
  BUTTON_UP,		//!< D-Pad Up, 		6
  BUTTON_DOWN,		//!< D-Pad Down, 	7
  BUTTON_R,			//!< R Shoulder, 	8
  BUTTON_L,			//!< L Shoulder, 	9
  BUTTON_X,			//!< X, 			10
  BUTTON_Y,			//!< Y, 			11
  BUTTON_TOUCH,		//!< Touch Pad, 	12
  BUTTON_LID,		//!< Lid Open/Close,13
};

/*! \class InputContext
 *  Maps each button and state to a cooresponding execution function
 */
class InputContext {
private:

	Event ButtonEvents[MAX_BUTTON_STATES];		//!< Array containing the event function pointers for button responses, mappable via SetButtonEvent

public:
	//! Constructor points all button events to an empty function
	InputContext();												
	//! Maps a function to a button state response
	//! \param state Button state involved, see BUTTON_STATE enum definition
	//! \param button The button which triggers the event, see BUTTON_IDS enum definition
	//! \param *pt2Func A pointer to the function to dispatch on input
	void SetButtonEvent(int state, int button, void (*pt2Func)(void));
	//! Executes the function associated with the given state and button
	//! \param state The state involved
	//! \param button The button involved
	void ExecuteEvent(int state, int button);
};


//! Non member function that does nothing 
void do_nothing();

//\}
#endif //INPUTCONTEXT_H