#ifndef GRAPHIC_T
#define GRAPHIC_T

//! \file GraphicT.h
//! \author J Mills
//! \date 9/15/2013 

//! \addtogroup grpTileManager
//\{
/*! \struct graphic_t
 * Contains palette and tile data
 */
typedef struct {
	int paletteLen;					//!< Length of palette array in elements
	const u16 *paletteEntries;		//!< Palette entries, u16 values, 5 bits per channel, RGB
	const u16 *paletteEntriesNight; //!< Same as paletteEntries, but containing night time color correction
	int tileLen;					//!< Length of tile array in elements
	const u8 *tileEntries;			//!< Tile entries, u8 value lookups into pallete
} graphic_t;
//\}

#endif //GRAPHIC_T