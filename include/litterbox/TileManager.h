#ifndef TILEMANAGER_H
#define TILEMANAGER_H

//! \file TileManager.h
//! \author J Mills
//! \date 9/15/2013 

#include <nds.h>
#include "AnimTile.h"
#include "MapData.h"
#include "Defines.h"
#include "Assert.h"

//! \addtogroup grpTileManager
//\{

/*! \class TileManager
 * This class sets up BG layers for either the Main or Sub screen and handles loading the graphics and maps to tile memory.
 * It also processes tiles that need animation as well as preloading edge tiles for scrolling maps.
 */
class TileManager
{
public:
	graphic_t *_gfx; 							//!< Graphics object which contains tile and palette data to be used
	int _screen;								//!< Screen to load to, Main or Sub as specified in ScreenEnum
	int _numBGs;								//!< Number of BG layers to use, the limit is 4.  Always starts with BG0 and counts up.
	u8 *_tileHardwarePtr;						//!< NDS Hardware address for tile memory
	u16 *_mapHardwarePtr[4];					//!< NDS Hardware address for map memory
	
	int _offsetX;								//!< Map scrolling offset, stored in hardware as REG_BG0HOFS 
	int _offsetY;								//!< Map scrolling offset, stored in hardware as REG_BG0VOFS 
	
	u16 *_paletteHardwarePtr;					//!< NDS Hardware address for palette memory
	u8 _animLen;								//!< Array length for _TileList
	AnimTile *_TileList;						//!< Array containing animation information for tileset
	int _timers[256];							//!< Timers for animated tiles need to be encapsulated in the manager instance, otherwise if more than one manager has access to an AnimTile the timing could get mangled
	int _frames[256];							//!< Current frames for animated tiles need to be encapsulated in the manager instance, otherwise if more than one manager has access to an AnimTile the timing could get mangled
	MapData_t *_map;							//!< Struct that contains 3 layers of tile map arrays, and 1 map containing collision data
	
	/*! Sets up the BGs and hardware pointers as well as the destination screen
	 *  \param screen is a ScreenEnum values representing which screen to use
	 *  \param numBGs dictates how many of the 4 hardware BGs to use
	 *  \param tileRamNum is the tile base offset for BGs, assumes all BGs share the same tile set
	 *  \param mapRamNum is the map base offset for BGs, each takes 2 slots (2x32x32)
	 */
	void Initialize(int screen, int numBGs, int tileRamNum, int mapRamNum);		
	//! Destructor is empty for now since we have no dynamic members
	~TileManager();
	/*! SetAnimTags provides the TileManager with a pointer to AnimTiles of a given size.
	 *  When the TileManager runs its update function to check if any tiles need to be animated 
	 *  it will cycle through each AnimTile.  If SetAnimTags is never run, tiles will still function, but
	 *  be kinda lame.
	 *  \param *anim contains the address of an AnimTile array
	 *  \param animLen indicates the number of elements in *anim
	 */
	void SetAnimTags(AnimTile *anim, int animLen);
	/*! Specifies which graphic object to use when displaying tiles
	 *  \param *gfx is a pointer to a graphics obect containing tile and palette data
	 */
	void SetGraphics(graphic_t *gfx);
	/*! Specifies which maps to use when displaying tiles
	 *  \param *map is a pointer to a MapData obect containing tile map data
	 */
	void SetMapData(MapData_t *map);
	/*! 
	 * Copies contents of _gfx->paletteEntries to the NDS BG_PALETTE address 
	 */
	void CopyPaletteToHardware();
	/*! 
	 * Copies contents of _gfx->tileEntries to the NDS BG_TILE_RAM address 
	 */
	void CopyTilesToHardware();
	/*! 
	 * Copies contents of _map to the NDS BG_MAP_RAM address 
	 */
	void CopyMapToHardware();
	/*!
	 *  Runs AnimUpdateTile on each AnimTile in the _TileList array, which adjusts animation when needed.
	 */
	void UpdateTiles();
	/*! Scrolls BG maps horizontally and preloads edges before they come into view
	 *  \param x gets added to the REG_BG_HOFS register
	 */
	void OffsetMapH(int x);
	/*! Scrolls BG maps vertically and preloads edges before they come into view
	 *  \param y gets added to the REG_BG_VOFS register
	 */
	void OffsetMapV(int y);
	/*! Loads single map id into memory at coordinates
	 *  \param xi is the x tile unit coordinate (not in pixels)
	 *  \param yi is the y tile unit coordinate (not in pixels)
	 */
	void SetMapTile(int xi, int yi);
	/*! Returns a pointer to an individual BG map location for external use
	 *	\param n is the BG number to use for finding a map address
		\return returns a pointer to a BG map address
	 */
	u16* GetMapPtr(int n);
};

//\}
#endif //TILEMANAGER_H