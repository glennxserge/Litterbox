#ifndef DEFINES_H
#define DEFINES_H

//! \file Defines.h
//! \author J Mills
//! \date 9/15/2013 

//! \name BG macros
//\{
#define REG_BGCNT 				((volatile u16*)(0x04000000+0x0008))	//!< Indexes the BG Control Register for assignment (Main screen)
#define REG_BGCNT_SUB 			((volatile u16*)(0x04000000+0x1008))	//!< Indexes the BG Control Register for assignment (Sub screen)

#define DISPLAY_BG_ACTIVE(n) 	(1 << (8+n)) 							//!< Returns bits for setting BG specified as active, still has to be stored in proper register.\n DISPLAY_BG_ACTIVE(0) is equivalent to DISPLAY_BG0_ACTIVE
#define BLEND_SRC_BG(n)			(1 << (n))								//!< Returns bits for setting Blending on BGs, still has to be captured in REG_BLDCNT
//\}

//! \name BG Scrolling macros
//\{
#define REG_BG_HOFS(n) (*(volatile u16*)(0x4000010+(n*4)))				//!< Main BG Horizontal scrolling address, where 'n' is the BG number
#define REG_BG_VOFS(n) (*(volatile u16*)(0x4000012+(n*4)))				//!< Main BG Vertical scrolling address, where 'n' is the BG number

#define SUB_REG_BG_HOFS(n) (*(volatile u16*)(0x4001010+(n*4)))			//!< Sub BG Horizontal scrolling address, where 'n' is the BG number
#define SUB_REG_BG_VOFS(n) (*(volatile u16*)(0x4001012+(n*4)))			//!< Sub BG Vertical scrolling address, where 'n' is the BG number
//\}

//! \name Window macros
//\{
#define WIN0_BG0 BIT(0) 
#define WIN0_BG1 BIT(1) 
#define WIN0_BG2 BIT(2) 
#define WIN0_BG3 BIT(3) 
#define WIN0_OBJ BIT(4) 
#define WIN0_GFX BIT(5) 
#define WIN0_ALL 0x3F 

#define WIN1_BG0 BIT(8) 
#define WIN1_BG1 BIT(9) 
#define WIN1_BG2 BIT(10) 
#define WIN1_BG3 BIT(11) 
#define WIN1_OBJ BIT(12) 
#define WIN1_GFX BIT(13) 
#define WIN1_ALL (0x3F << 8)
//\}

//! \name Input macros
//\{
#define BUTTON_STATES 		3		//!< Total number of states: held, pressed, and released
#define MAX_BUTTONS 		14		//!< Total number of DS input buttons (including lid state and touch pad)
//\}

/*! \enum ScreenEnum
 * Enumeration for identifying screen
 */
enum ScreenEnum {
	MAIN,		//!< 0, Main screen
	SUB			//!< 1, Sub(touch) screen
};

//! \name Math
//\{
#define ABS(n)	(((n) < 0) ? -(n) : (n))
//\}

#endif //DEFINES_H