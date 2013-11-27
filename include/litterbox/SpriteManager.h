#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

//! \file SpriteManager.h
//! \author J Mills
//! \date 9/15/2013 

#include "Sprite.h"
#include "SpriteList.h"

#include <stdio.h>

//! \addtogroup grpSpriteManager
//\{

/*! \class SpriteManager
 * Manages and updates all sprites.  Governs loading and recycling graphics, 
 * sorts sprites by Y position, and adds and deletes sprites as needed
 */
class SpriteManager {
private:
	
	u16* PalettePtr;			//!< Pointer to the palette hardware address
	SpriteList SpList;			//!< Contains a list of all sprites that are active
	OamState *Oam;				//!< Contains a pointer to either oamMain or oamSub
	
public:
	int OamCount;				//!< Keeps track of next OAM ID
	bool OamSlotState[128];		//!< Sets which OAM slots are occupied
	bool PaletteSlotState[16];	//!< Sets which palette slots are occupied
	int PaletteCount;			//!< Keeps track of next palette to fill
	
	//! Constructor initializes manager 
	/*! \param *_Oam Assigns Oam pointer to either oamMain or oamSub
	 *  \param SMap How the sprite is aligned, generally this is just SpriteMapping_1D_128
	 */
	SpriteManager(OamState *_Oam, SpriteMapping SMap);
	//! Destructor, currently unnecessary
	~SpriteManager();
	//! Adds a sprite to SpList and copies graphics data to hardware if needed
	//! \param *_pSp Sprite to add
	void AddSprite(Sprite *_pSp);
	//! Deletes a sprite from the SpList and frees up oam slot and palette data (if not shared by other sprites)
	//! \param *_pSp Sprite to add
	void DeleteSprite(Sprite *_pSp);
	//! Copies all sprites to OAM memory
	void PutSprites();
	//! Updates all sprite animations
	void UpdateSpriteOam();
	//! Returns the next free slot in oam
	int GetNextFreeOam();
	//! Returns the next free slot in palette
	int GetNextFreePalette();
	//! Free up a palette slot at ID
	//! \param ID The palette slot ID to free
	void FreePaletteSlot(int ID);
	//! Free up a oam slot at ID
	//! \param ID The osm slot ID to free
	void FreeOamSlot(int ID);
	//! Sorts all sprites along the Y axis to ensure that their draw order makes sense
	void SortSpritesByYAxis();
};

//\}

#endif //SPRITEMANAGER_H