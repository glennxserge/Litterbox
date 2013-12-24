#include "SpriteManager.h"
#include "Assert.h"

SpriteManager::SpriteManager(OamState *_Oam, SpriteMapping SMap) {
	Oam = _Oam;
	oamInit(Oam, SMap, true);
	PaletteCount = 0;
	
	if( Oam == &oamMain ) {
		REG_DISPCNT |= DISPLAY_SPR_EXT_PALETTE;
		
		vramSetBankF(VRAM_F_LCD);
		PalettePtr = VRAM_F_EXT_SPR_PALETTE[0];
		vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
	}
	if( Oam == &oamSub ) {
		REG_DISPCNT_SUB |= DISPLAY_SPR_EXT_PALETTE;
		
		vramSetBankI(VRAM_I_LCD);
		PalettePtr = VRAM_I_EXT_SPR_PALETTE[0];
		vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);
	}
	OamCount = 0;
	
	int i;
	for( i = 0; i < 128; i++ ) {
		OamSlotState[i] = false; //False means unoccupied
	}
	for( i = 0; i < 16; i++ ) {
		PaletteSlotState[i] = false;
	}
}

SpriteManager::~SpriteManager() {
	// currently no members allocated dynamically
}

void SpriteManager::AddSprite(Sprite *_pSp) {
	// There is a maximum of 128 sprites available
	ASSERT(OamCount < 128);
	// Is this exact sprite object already loaded?  Bail
	if( SpList.IsSpriteInList(_pSp) ) return;
	
	// IsSpriteGfxLoaded returns -1 if no loaded sprites use the same palette as the sprite being loaded
	// Otherwise, it returns an index for the already loaded palette 
	int palette = SpList.IsPaletteLoaded(_pSp);
	
	if(palette >= 0) {  // Palette is loaded via another sprite
		_pSp->palette_num = palette;
	} else {			// New palette, we need to copy it to the hardware
		ASSERT(PaletteCount < 16); // Only room for 16 palettes total, bail if we try to load more
		palette = GetNextFreePalette();
		
		if( Oam == &oamMain ) {
			vramSetBankF(VRAM_F_LCD);
			dmaCopy(_pSp->gfx_t->paletteEntries, (u16 *)(PalettePtr+256*palette), _pSp->gfx_t->paletteLen*2);
			vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
		}
		if( Oam == &oamSub ) {
			vramSetBankI(VRAM_I_LCD);
			dmaCopy(_pSp->gfx_t->paletteEntries, (u16 *)(PalettePtr+256*palette), _pSp->gfx_t->paletteLen*2);
			vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);
		}
		//dmaCopy(_pSp->gfx_t->paletteEntries, &PalettePtr[256*palette], _pSp->gfx_t->paletteLen*2);
		_pSp->palette_num = palette;
		PaletteCount++;
	}
	
	int FreeOamSlot;
	FreeOamSlot = GetNextFreeOam();
	_pSp->InitializeOam(Oam, FreeOamSlot); 
	OamCount++;					//Increment Unique Oam ID
	SpList.Append(_pSp);
	_pSp->hidden = false;
}

void SpriteManager::DeleteSprite(Sprite *_pSp) {
	// Free up a palette slot if no other sprites use it
	if( SpList.PaletteInstances(_pSp) == 1 ) {
		FreePaletteSlot(_pSp->palette_num);
		PaletteCount--;
		OamCount--;
	}
	if( SpList.IsSpriteInList(_pSp) ) {
		FreeOamSlot(_pSp->sprite_oam_index);
		SpList.Delete(_pSp);
		_pSp->hidden = true;
		_pSp->PutSpriteOam();
		OamCount--;
	}
	
}

void SpriteManager::PutSprites() {
	SpList.PutSpriteList();
}

void SpriteManager::UpdateSpriteOam() {
	SpList.AnimateList();
	oamUpdate(Oam);
}

int SpriteManager::GetNextFreeOam() {
	int i;
	for( i = 0; i < 128; i++ ) {
		if( OamSlotState[i] == false ) {
			OamSlotState[i] = true;
			return i;
		}
	}
	return -1;  // All Oam Spots are full
}

int SpriteManager::GetNextFreePalette() {
	int i;
	for( i = 0; i < 16; i++ ) {
		// If false, then slot is unassigned, set it true and return index
		if( PaletteSlotState[i] == false ) {
			PaletteSlotState[i] = true;
			return i;
		}
	}
	return -1; //No more unassigned palettes
}

void SpriteManager::FreePaletteSlot(int ID) {
	ASSERT(ID < 16 && ID >= 0); // Given ID must be between 0-16
	PaletteSlotState[ID] = false; 
}

void SpriteManager::FreeOamSlot(int ID) {
	ASSERT(ID < 128 && ID >= 0); // Given ID must be between 0-128
	OamSlotState[ID] = false; 
}

void SpriteManager::SortSpritesByYAxis() {
	SpList.SortByY();
}