#ifndef LIBLITTERBOX_H
#define LIBLITTERBOX_H

//! \file litterbox.h
//! \author J Mills
//! \date 9/15/2013 

#include <litterbox/Assert.h>
#include <litterbox/Defines.h>
#include <litterbox/GraphicT.h>
#include <litterbox/VideoFunctions.h>
#include <litterbox/TileManager.h>
#include <litterbox/SpriteManager.h>
#include <litterbox/TextSystem.h>
#include <litterbox/Coroutine.h>

/*! \defgroup grpTileManager TileManager
 *  \brief TileManager organizes tile data and simplifies loading
 *  \note The TileManager is in charge of setting up the number of BG layers to use,
 *  copying the palette and tile data to the hardware, querying updates on animated tiles,
 *  and handle edge case loading for scrolling backgrounds
 */

 /*! \defgroup grpTextSystem TextSystem
 *  \brief Blits text to the tile memory 
 *  \note The TextSystem is responsible for parsing strings and blitting them to the
 *  appropriate tile memory.  It can read a proprietary tag notation which allows text to be
 *  embedded with commands for adjusting the position, color, speed, and margins.
 *  It has, optionally, dialogue box method with layer transparency.
 */
 
/*! \defgroup grpCoroutine Coroutine
 *  \brief Coroutine hack that allows for persistent data between function calls
 *  \note Coroutines are made up from a bunch of macros that define which function params to keep, 
 *  where to yield, and where to end the coroutine.  It is based on Duff's Device.
 */
 
 /*! \defgroup grpSpriteManager SpriteManager
 *  \brief Manages all the sprites allocation and display details
 *  \note Adjusts sprite draw priority by sorting height, allocates OAM index, attaches tile and palette data,
 *  and copies data to hardware.
 */
 
/*! \mainpage	Litterbox 1.0
	<p>
	Litterbox is a NDS library that simplifies management of typical
	game objects in relation to the DS hardware.  In other words it deals 
	with all the tedious crap that's required to make a game.  Specific modules include:\n
	- \ref grpTileManager \n
	- \ref grpSpriteManager \n
	- InputManager \n
	- \ref grpCoroutine \n
	- \ref grpTextSystem \n
	</p>
*/

#endif //LIBLITTERBOX_H