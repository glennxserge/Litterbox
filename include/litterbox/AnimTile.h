#ifndef ANIMTILE_H
#define ANIMTILE_H

//! \file AnimTile.h
//! \author J Mills
//! \date 9/15/2013 

#include <nds.h>
#include "GraphicT.h"

//! \addtogroup grpTileManager

/*!	\defgroup grpAnimTile	AnimTile
 *	\brief	Struct for keeping track of tile animation info. 
 *	\note	Generally the tile manager will get an array of AnimTiles that describe which tiles should have animation in a tileset.
 *	\ingroup grpTileManager
 */
//\{

//! \enum AnimLoop enumeration
enum AnimLoop {
	AN_ONCE,	//!< The animated tile cycles once and stops
	AN_LOOP,	//!< The animated tile loops continously
	AN_BOUNCE	//!< The animated tile ping pongs continously
};

/*! \struct AnimTile
 * Contains tile animation data for tracking frame IDs
 */
struct AnimTile {
	const u8 	len;	//!< The array size for ID and freq
	const u16*	ID;		//!< Array of tile ID's in animation, ordered sequencially
	const u8*	freq;	//!< Array of tile frequency in animation, units in 60ths of a second
	u8 			loop;	//!< Looping type for animation, AnimLoop enumeration
};

//! Checks tile frame animation, and copies appropriate data to
//! hardware 
/*!
	\param a		Pointer to AnimTile object to update
	\param t		Pointer to a timer for the anim tile
	\param f		Pointer to current frame for the anim tile
	\param gptr		Pointer to graphic_t object containing tiles
	\param tmem		Pointer to hardware tile destination
*/
void AnimUpdateTile(AnimTile *a, int *t, int *f, graphic_t *gptr, u8 *tmem);

//\}
#endif //ANIMTILE_H