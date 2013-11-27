#ifndef TEXTSYSTEM_H
#define TEXTSYSTEM_H

//! \file TextSystem.h
//! \author J Mills
//! \date 9/15/2013 

#include <nds.h>
#include <stdio.h>
#include "Assert.h"
#include "Defines.h"
#include "font.h"
#include "dbox.h"

//! \addtogroup grpTextSystem
//\{

//! \enum TS_Colors enumeration
enum TS_Colors {
	TS_CLEAR,		//!< Palette 	0
	TS_WHITE,		//!< Palette  	1
	TS_80GRAY,		//!< Palette  	2
	TS_66GRAY,		//!< Palette  	3
	TS_50GRAY,		//!< Palette  	4
	TS_33GRAY,		//!< Palette  	5
	TS_16GRAY,		//!< Palette  	6
	TS_BLACK,		//!< Palette  	7
	TS_RED1,		//!< Palette  	8
	TS_RED2,		//!< Palette  	9
	TS_RED3,		//!< Palette  	10
	TS_ORANGE1,		//!< Palette  	11
	TS_ORANGE2,		//!< Palette  	12
	TS_ORANGE3,		//!< Palette  	13
	TS_YELLOW1,		//!< Palette  	14
	TS_YELLOW2,		//!< Palette  	15
	TS_YELLOW3,		//!< Palette  	16
	TS_GREEN1,		//!< Palette  	17
	TS_GREEN2,		//!< Palette  	18
	TS_GREEN3,		//!< Palette  	19
	TS_BLUE1,		//!< Palette  	20
	TS_BLUE2,		//!< Palette  	21
	TS_BLUE3,		//!< Palette  	22
	TS_PURPLE1,		//!< Palette  	23
	TS_PURPLE2,		//!< Palette  	24
	TS_PURPLE3,		//!< Palette  	25
};

//! \enum TS_Borders enumeration
enum TS_Borders {
	TS_BorderTL,	//!< Top left
	TS_BorderT, 	//!< Top 
	TS_BorderTR,	//!< Top right
	TS_BorderL, 	//!< Left
	TS_BorderE,		//!< Empty
	TS_BorderR,		//!< Right
	TS_BorderBL,	//!< Bottom left
	TS_BorderB, 	//!< Bottom
	TS_BorderBR 	//!< Bottom right
};

/*! \class TextSystem
 *  TextSystem handles parsing and displaying strings via the hardware tiles and uses a proprietary
 *  tag notation for executing commands inside the strings it is evaluating that can move the cursor,
 *  change the color, change the printing speed, and adjust the margins.
 * 
 *  -Tag Definitions- \n
 *	<em> Tags can be specified inside TS_Print strings to adjust the behaviour of the blitter </em>\n
 *  \line \n
 *	X - set absolute x position -- example @\{X:20\} \n
 *	Y - same as X but for y position \n
 *	x - relative x position -- example @\{x:35\} (moves the cursor forward 35 pixels) \n
 *	y - same as x but for y position \n
 *	C - set ink color -- example @\{C:1\} \n
 *	w - wait number of frames -- example @\{w:60\} waits one second \n
 *
 *  \warning IMPORTANT: in order for the text system to work DISPLAY_BG_EXT_PALETTE must be set in the video mode.
 */
class TextSystem {
public:
	int 	_screen;		//!< Sets the output display to use, Main or Sub
	int		_bgNum;			//!< Sets the BG layer to print to (only prints to one)
	u16 	*_tileRam;		//!< NDS Hardware address for tile memory
	u16		*_mapRam;		//!< NDS Hardware address for map memory
	u16		*_palRam;		//!< NDS Hardware address for palette memory ( VRAM_{E,H}_EXT_PALETTE )
	u8		*_font;			//!< Address of font graphics, these come with the library, but you could potentially use your own
	u8		*_border;		//!< Address of border graphics, these come with the library, but you could potentially use your own
	u8 		_chars[256];	//!< Ascii letters look up table to speed up text parsing 
	int 	_x; 			//!< X beginning coordinate
	int		_y;				//!< Y beginning coordinate
	int 	_dx; 			//!< X current coordinate
	int		_dy;			//!< Y current coordinate
	int 	_margin;		//!< Width in pixels of the screen right margin, default: 247 ( 8 pixels from edge )
	int		_lineSpace;		//!< Vertical space in pixels between lines, default: 10
	u16		_color;			//!< Ink color, by default it's white
	
	/*! Sets which ouptut to display to, which BG layer to use, and loads the graphics and palette 
	 *  \param screen sets the display output
	 *  \param bgNum is the BG layer to use
	 *  \param tileRamNum BG_TILE_RAM block number to use
	 *  \param mapRamNum BG_MAP_RAM block number to use
	 */
	void Initialize( int screen, int bgNum, int tileRamNum, int mapRamNum );
	
	/*! Draws a character coordinates with specific color 
	 *  \param x horizontal coordinate to draw at
	 *  \param y vertical coordinate to draw at
	 *  \param c ascii character to draw
	 *  \param col ink color
	 */
	void PutChar( int x, int y, char c, int col);
	
	/*! Places a piece of the dialog box
	 *  \param x horizontal coordinate to draw at
	 *  \param y vertical coordinate to draw at
	 *  \param id The border ID to use, specified in the TS_Borders enum
	 */
	void PutBorderPiece( int x, int y, int id);
	
	/*! Places a dialog box and enables windowing for transparency
	 *  \param x1 horizontal tile coordinate start drawing box
	 *  \param y1 vertical tile coordinate start drawing box
	 *  \param x2 horizontal tile coordinate finish drawing box
	 *  \param y2 vertical tile coordinate finish drawing box
	 *  \param fade transparency value: 0 (opaque) - 15 (transparent)
	 */
	void PutBorderBox( int x1, int x2, int y1, int y2, int fade );
	
	/*! Clears a dialog box and disables windowing
	 *  \param x1 horizontal tile coordinate start clearing box
	 *  \param y1 vertical tile coordinate start clearing box
	 *  \param x2 horizontal tile coordinate finish clearing box
	 *  \param y2 vertical tile coordinate finish clearing box
	 */
	void ClearBorderBox( int x1, int x2, int y1, int y2 );
	
	/*! Evaluates beginning of string looking for \@{} tags, after it processes them 
	 *  and applies their methods it advances the pointer to just past the tag
	 *  \param *text Text to evaluate
	 *  \return The remaining string just past the end of the \@{} tag so the text parsing can continue
	 */
	const char* ExecTags(const char *text);
	
	/*! Evaluates the beginning of the string looking for a continuous numerical value
	 *  and returns the integer equivalent.  Only allows up to 3 continuous numbers ( or a maximum value of 999 ).
	 *  \param *text Text to evaluate
	 *  \return The integer value of a numerical string
	 */
	int GetValue(const char *text);
	
	/*! Checks to see how many ascii characters are needed to describe an integer.
	 *  \param v The number to evaluate
	 *  \return The number of digits needed to express an ascii number ( "1240" == 4 digits )
	 */
	int NumDigits(int v);	 
	
	/*! Prints a string to the screen at the coordinates
	 *  \param x The horizontal start for printing
	 *  \param y The vertical start for printing
	 *  \param *text The string to print
	 */
	void Print( int x, int y, const char *text);
	
	/*! Clears entire BG layer text is on
	 */
	void ClearScreen();
	
	/*! Clears a character from screen at the given coordinates
	 *  \param x The horizontal position to clear
	 *  \param y The vertical position to clear
	 */
	void ClearChar( int x, int y );
	
	/*! Turns windowing registers on
	 */
	void EnableWindows();
	
	/*! Turns windowing registers off
	 */
	void DisableWindows();
};

//\}
#endif //TEXTSYSTEM_H