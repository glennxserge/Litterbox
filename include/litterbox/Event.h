#ifndef EVENT_H
#define EVENT_H

//! \file Event.h
//! \author J Mills
//! \date 12/1/2013 

//! \addtogroup grpInputContext

/*!	\defgroup grpEvent	Event
 *	\brief	Struct containing a pointer to a function
 *	\note	Function pointer acts as a mappable response for button input
 *	\ingroup grpInputContext
 */
//\{

/*! \struct Event
 * Keeps an empty function pointer which is used
 * in our InputManager class to attach functions to button inputs
 */
typedef struct {
	void (*function_pointer)();		//!< An empty function pointer for button mapping
} Event;

//\}
#endif //EVENT_H