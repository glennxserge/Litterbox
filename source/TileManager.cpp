#include "TileManager.h"
#include <stdio.h>

// TileManager.cpp
// Author J. Mills
// 9/15/2013

void TileManager::Initialize(int screen, int numBGs, int tileRamNum, int mapRamNum)
{
	// Fail if the screen isn't defined or the number of bgs isn't between 1-4
	ASSERT(screen == MAIN || screen == SUB);
	ASSERT(numBGs < 5 && numBGs > 0);
	// Otherwise we have reasonable params, we can continue ...
	_screen = screen;
	_numBGs = numBGs;
	_offsetX = _offsetY = 0;
	_animLen = 0;
	
	int i, j;
	
	if(_screen == MAIN) {
		_tileHardwarePtr = (u8*)BG_TILE_RAM(tileRamNum);
		for(i = 0; i < _numBGs; i++) {
			REG_BGCNT[i] = BG_64x32 | BG_COLOR_256 | BG_MAP_BASE(mapRamNum+(i*2)) | BG_TILE_BASE(tileRamNum) | BG_PRIORITY(3-i);
			_mapHardwarePtr[i] = (u16*)BG_MAP_RAM(mapRamNum+(i*2));
		}
		
		for(i = 0; i < 4; i++) {
			//Turn on BGs and disable leftover BGs
			if(i < _numBGs) REG_DISPCNT |= DISPLAY_BG_ACTIVE(i);
			else REG_DISPCNT &= ~DISPLAY_BG_ACTIVE(i);
		}
		// We have to load extended palettes in lcd mode because vram doesn't 
		// have an address in ext_palette mode, once we are done we can go back to extended mode
		vramSetBankE(VRAM_E_LCD);
		_paletteHardwarePtr = VRAM_E_EXT_PALETTE[0][0];	// Get palette address at BG 0 and slot 0
		vramSetBankE(VRAM_E_BG_EXT_PALETTE);
	}
	else if(_screen == SUB) {
		_tileHardwarePtr = (u8*)BG_TILE_RAM_SUB(tileRamNum);
		
		for(i = 0; i < _numBGs; i++) {
			REG_BGCNT_SUB[i] = BG_64x32 | BG_COLOR_256 | BG_MAP_BASE(mapRamNum+(i*2)) | BG_TILE_BASE(tileRamNum) | BG_PRIORITY(3-i);
			_mapHardwarePtr[i] = (u16*)BG_MAP_RAM_SUB(mapRamNum+(i*2));
		}
		
		for(i = 0; i < 4; i++) {
			//Turn on BGs and disable leftover BGs
			if(i < _numBGs) REG_DISPCNT_SUB |= DISPLAY_BG_ACTIVE(i);
			else REG_DISPCNT_SUB &= ~DISPLAY_BG_ACTIVE(i);
		}
		// We have to load extended palettes in lcd mode because vram doesn't 
		// have an address in ext_palette mode, once we are done we can go back to extended mode
		vramSetBankH(VRAM_H_LCD);
		_paletteHardwarePtr = VRAM_H_EXT_PALETTE[0][0];	// Get palette address at BG 0 and slot 0
		vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
	}
	
	//clear maps
	for(i = 0; i < 64*32; i++)
	{
		for(j = 0; j < _numBGs; j++)
		{
			(_mapHardwarePtr[j])[i] = 0;
		}
	}
}

TileManager::~TileManager()
{
	//Nothing to do here
}

void TileManager::SetGraphics(graphic_t *gfx)
{
	_gfx = gfx;
	CopyPaletteToHardware();
	CopyTilesToHardware();
}

void TileManager::SetMapData(MapData_t *map) {
	_map = map;
	CopyMapToHardware();
}

void TileManager::CopyMapToHardware() {
	int x, y;
	int index, subindex;
	
	//Setup Main Maps
	for(y = 0; y < 12; y++)
	{
		for(x = 0; x < 16; x++)
		{	
			index = _map->width*y + x;
			subindex = y * 16 * 4 + x * 2;
			
			if(_numBGs > 0) {
				_mapHardwarePtr[0][subindex] = _map->tile_map_1[index]<<2;
				_mapHardwarePtr[0][subindex+1] = ( _map->tile_map_1[index]<<2 ) + 1;
				_mapHardwarePtr[0][subindex+32] = ( _map->tile_map_1[index]<<2 ) + 2;
				_mapHardwarePtr[0][subindex+33] = ( _map->tile_map_1[index]<<2 ) + 3;
			}
			if(_numBGs > 1) {
				_mapHardwarePtr[1][subindex] = _map->tile_map_2[index]<<2;
				_mapHardwarePtr[1][subindex+1] = ( _map->tile_map_2[index]<<2 ) + 1;
				_mapHardwarePtr[1][subindex+32] = ( _map->tile_map_2[index]<<2 ) + 2;
				_mapHardwarePtr[1][subindex+33] = ( _map->tile_map_2[index]<<2 ) + 3;
			}
			if(_numBGs > 2 ) {
				_mapHardwarePtr[2][subindex] = _map->tile_map_3[index]<<2;
				_mapHardwarePtr[2][subindex+1] = ( _map->tile_map_3[index]<<2 ) + 1;
				_mapHardwarePtr[2][subindex+32] = ( _map->tile_map_3[index]<<2 ) + 2;
				_mapHardwarePtr[2][subindex+33] = ( _map->tile_map_3[index]<<2 ) + 3;
			}
			if(_numBGs > 3 ) {
				_mapHardwarePtr[3][subindex] = 0;
				_mapHardwarePtr[3][subindex+1] = 0;
				_mapHardwarePtr[3][subindex+32] = 0;
				_mapHardwarePtr[3][subindex+33] = 0;
			}
		}
	}
}

void TileManager::UpdateTiles()
{
	int i;
	for(i = 0; i < _animLen; i++)
	{
		AnimUpdateTile(&_TileList[i], &_timers[i], &_frames[i], _gfx, _tileHardwarePtr);
	}
}

void TileManager::SetAnimTags(AnimTile *anim, int animLen) {
	_animLen = animLen;
	_TileList = anim;
	int i;
	for(i = 0; i < 256; i++) {
		_timers[i] = 0;
		_frames[i] = 0;
	}
}

void TileManager::CopyPaletteToHardware() {
	int i;
	//Switch to LCD mode since ext_palette has no address
	if(_screen == MAIN) vramSetBankE(VRAM_E_LCD);
	if(_screen == SUB) vramSetBankH(VRAM_H_LCD);
	
	//Extended palettes assign each BG with a unique palette slot.  Unfortunately this means
	//we have to copy our palette data into each BG that's used instead of just 1.
	for( i = 0; i < _numBGs; i++) {
		dmaCopy(_gfx->paletteEntries, (_paletteHardwarePtr+(i*4096)), 256);
	}
	
	//Switch back to ext_palette
	if(_screen == MAIN) vramSetBankE(VRAM_E_BG_EXT_PALETTE);
	if(_screen == SUB) vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
}

void TileManager::CopyTilesToHardware() {
	int i, len;
	len = _gfx->tileLen>>6;
	for( i = 0; i < len; i++ ) {
		swiCopy(_gfx->tileEntries+i*64, _tileHardwarePtr + i*64, 32);
	}
}

void TileManager::SetMapTile(int xi, int yi) {
	int index, subindex;
	int newX, newY, blockOffset;
	index = yi*_map->width + xi;
	newX = xi%16 * 2;
	newY = (yi%16) * 16 * 4;
	blockOffset = ( (xi/16)%2 ) * (32*32);
	subindex = newY + newX + blockOffset;
	
	//Don't try to preload edges if they are past the minimum/maximum map area 
	if(xi < 0 || yi < 0) return; 
	if(xi > _map->width || yi > _map->height) return;
	
	if(_numBGs > 0) {
		(_mapHardwarePtr[0])[subindex] = _map->tile_map_1[index]<<2;
		(_mapHardwarePtr[0])[subindex+1] = (_map->tile_map_1[index]<<2) + 1;
		(_mapHardwarePtr[0])[subindex+32] = (_map->tile_map_1[index]<<2) + 2;
		(_mapHardwarePtr[0])[subindex+33] = (_map->tile_map_1[index]<<2) + 3;
	}
	if(_numBGs > 1) {
		(_mapHardwarePtr[1])[subindex] = _map->tile_map_2[index]<<2;
		(_mapHardwarePtr[1])[subindex+1] = (_map->tile_map_2[index]<<2) + 1;
		(_mapHardwarePtr[1])[subindex+32] = (_map->tile_map_2[index]<<2) + 2;
		(_mapHardwarePtr[1])[subindex+33] = (_map->tile_map_2[index]<<2) + 3;
	}
	if(_numBGs > 2) {
		(_mapHardwarePtr[2])[subindex] = _map->tile_map_3[index]<<2;
		(_mapHardwarePtr[2])[subindex+1] = (_map->tile_map_3[index]<<2) + 1;
		(_mapHardwarePtr[2])[subindex+32] = (_map->tile_map_3[index]<<2) + 2;
		(_mapHardwarePtr[2])[subindex+33] = (_map->tile_map_3[index]<<2) + 3;
	}
}

void TileManager::OffsetMapH(int x) {
	int i;
	int xindex;
	
	_offsetX += x;
	
	if(_offsetX < 0) _offsetX = 0;
	if(_offsetX > (_map->width-16)*16) _offsetX = (_map->width-16)*16;
	
	//scroll left
	if(x < 0) {
		xindex = _offsetX/16 - 1;
		for(i = _offsetY/16 - 1; i < _offsetY/16+13; i++) {
			SetMapTile(xindex, i);
		} 
	}
	//scroll right
	if(x > 0) {
		xindex = _offsetX/16 + 16;
		for(i = _offsetY/16 - 1; i < _offsetY/16+13; i++) {
			SetMapTile(xindex, i);
		}
		
	}
	// set bg horizontal _offset register 
	for(i = 0; i < _numBGs; i++) {
		if(_screen == MAIN) REG_BG_HOFS(i) = _offsetX;
		if(_screen == SUB) 	SUB_REG_BG_HOFS(i) = _offsetX;
	}
}

void TileManager::OffsetMapV(int y) {
	int i;
	int yindex;
	
	_offsetY += y;
	
	if(_offsetY < 0) _offsetY = 0;
	if(_offsetY > (_map->height-12)*16) _offsetY = (_map->height-12)*16;
	
	//scroll up
	if(y < 0) {
		yindex = _offsetY/16 - 1;
		for(i = _offsetX/16 - 1; i < _offsetX/16+17; i++) {
			SetMapTile(i, yindex);
		} 
	}
	//scroll down
	if(y > 0) {
		yindex = _offsetY/16 + 12;
		for(i = _offsetX/16 - 1; i < _offsetX/16+17; i++) {
			SetMapTile(i, yindex);
		}
		
	}
	// set bg vertical offset register 
	for(i = 0; i < _numBGs; i++) {
		if(_screen == MAIN) REG_BG_VOFS(i) = _offsetY;
		if(_screen == SUB) 	SUB_REG_BG_VOFS(i) = _offsetY;
	}
	
}

u16* TileManager::GetMapPtr(int n) {
	return _mapHardwarePtr[n];
}