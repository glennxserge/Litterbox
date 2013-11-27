#ifndef _SPRITE_H
#define _SPRITE_H

//! \file Sprite.h
//! \author J Mills
//! \date 9/15/2013 

#include <nds.h>
#include "GraphicT.h"

//! \addtogroup grpSpriteManager
//\{

/*! \class Sprite
 * Contains sprite graphics, position, and animation logic
 */
class Sprite
{
public:
	int x;					//!< X Coordinate
	int y;					//!< Y Coordinate

	graphic_t* gfx_t;		//!< Pointer to graphic data
	
	u16* sprite_gfx_mem;	//!< OAM memory pointer to store graphics
	
	int palette_num;		//!< The palette slot the sprite is loaded in
	int start_frame;		//!< The starting frame for animation
	int end_frame;			//!< The ending frame for animation
	int current_frame;		//!< Current frame in animation sequence
	int sub_frames;			//!< Keeps track of sub frames ( 1/60th of second ) 
	int *delay;				//!< An array containing each frame's delay value
	int sprite_oam_index;	//!< Integer representing a unique ID for OAM
	bool hidden;			//!< Toggles visibility of sprite
	u8 priority;			//!< Priority determines the draw order in reference to other sprites
	OamState* _oam;			//!< Contains a pointer to either oamMain or oamSub
	
	//! Constructor sets the default values for sprites
	Sprite();
	//! Constructor with parameters for setting up sprites
	/*! \param _x The x coordinate for sprite
	 *  \param _y The y coordinate for sprite
	 *	\param _start_frame Sets start_frame 
	 *  \param _end_frame Sets end_frame 
	 *	\param _delay Sets pointer to frame delay values
	 *	\param gfx Sets pointer sprites graphics
	 */
	Sprite(int _x, int _y, int _start_frame, int _end_frame, int* _delay, graphic_t* gfx);
	//! Initialize sprite, essentially the same as the constructor
	/*! \param _x The x coordinate for sprite
	 *  \param _y The y coordinate for sprite
	 *	\param _current_frame Sets current_frame 
	 *	\param _delay Sets pointer to frame delay values
	 *	\param _palette_num Sets palette number
	 */
	void SetupSprite(int _x, int _y, int _current_frame, int* _delay, int _palette_num);
	//! Updates sprite animation frames
	void Animate();
	//! Copies sprite frame graphics to OAM memory
	void PutSpriteOam();
	//! Sets up OAM state and sprite index
	/*! \param *oam A pointer to either oamMain or oamSub
	 *  \param oam_index Unique ID for OAM
	 */
	void InitializeOam(OamState *oam, int oam_index);
	//! Sets the current_frame
	//! \param frame The frame number to set
	void SetFrame(int frame);
};

//\}
#endif //_SPRITE_H