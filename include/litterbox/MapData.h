#ifndef MAP_DATA_H
#define MAP_DATA_H

//! \file MapData.h
//! \author J Mills
//! \date 9/15/2013 

#include <nds.h>

//! \addtogroup grpTileManager 
//\{
/*! \struct MapData_t
 * Contains map details for displaying up to 3 layers of BG tile maps
 * as well as a collision map.
 */
struct MapData_t {
	const int width;			//!< Width of map
	const int height;			//!< Height of map
	const u16 *tile_map_1;		//!< Layer 1 (bottom), contains tile IDs
	const u16 *tile_map_2;		//!< Layer 2 (middle), contains tile IDs
	const u16 *tile_map_3;		//!< Layer 3 (top), contains tile IDs
	const u8 *walkable_map;		//!< Collision layer, 0 or 1
};
//\}

#endif //MAP_DATA_H