#include "textSystem.h"

// File TextSystem.cpp
// Author J Mills
// Date 9/15/2013

void TextSystem::Initialize( int screen, int bgNum, int tileRamNum, int mapRamNum ) {
	_x = 0;
	_y = 0;
	_dx = 0;
	_dy = 0;
	
	_margin = 231;		// 25 pixels from the screen right edge 
	_lineSpace = 10;	// space between vetical lines
	_screen = screen; 	// MAIN, SUB
	
	REG_BLDY = 0;
	REG_BLDY_SUB = 0;
	_bgNum = bgNum;
	
	EnableWindows();
	// Do engine/screen specific setups
	if(_screen == MAIN) {
		REG_BGCNT[_bgNum] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(mapRamNum) | BG_TILE_BASE(tileRamNum) | BG_PRIORITY(0);
		_tileRam = BG_TILE_RAM(tileRamNum);
		_mapRam = (u16*)BG_MAP_RAM(mapRamNum);
		// We have to load the extended palette in lcd mode because vram doesn't 
		// have an address in ext_palette mode
		vramSetBankE(VRAM_E_LCD);
		// set palette address
		_palRam = VRAM_E_EXT_PALETTE[_bgNum][0];	// Set bg number and first slot palette
		REG_DISPCNT |= DISPLAY_BG_ACTIVE(bgNum);
	}
	if(_screen == SUB) {
		REG_BGCNT_SUB[_bgNum] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(mapRamNum) | BG_TILE_BASE(tileRamNum) | BG_PRIORITY(0);
		_tileRam = BG_TILE_RAM_SUB(tileRamNum);
		_mapRam = (u16*)BG_MAP_RAM_SUB(mapRamNum);
		// We have to load the extended palette in lcd mode because vram doesn't 
		// have an address in ext_palette mode
		vramSetBankH(VRAM_H_LCD);
		// set palette address
		_palRam = VRAM_H_EXT_PALETTE[_bgNum][0];	// Set bg number and first slot palette	
		REG_DISPCNT_SUB |= DISPLAY_BG_ACTIVE(bgNum);
	}
	
	//set palette, the order (if not obvious by name) is lighter -> darker shades
	_palRam[0] = RGB15(0,   0,  0);		// Clear color
	//WHITE - BLACK
	_palRam[1] = RGB15(31, 31, 31);		// White
	_palRam[2] = RGB15(25, 25, 25);		// 80% Gray
	_palRam[3] = RGB15(20, 20, 20);		// 66% Gray
	_palRam[4] = RGB15(15, 15, 15);		// 50% Gray
	_palRam[5] = RGB15(10, 10, 10);		// 33% Gray
	_palRam[6] = RGB15(5,   5,  5);		// 16% Gray
	_palRam[7] = RGB15(0,   0,  0);		// Black
	//REDS
	_palRam[8] = RGB15(31, 22, 23);		// Light Pink
	_palRam[9] = RGB15(26,  2,  7);		// Crimson Red
	_palRam[10] = RGB15(18, 1,  3);		// Indian Red
	//ORANGES
	_palRam[11] = RGB15(31, 26, 22);	// Peachpuff
	_palRam[12] = RGB15(28, 17,  4);	// Carrot
	_palRam[13] = RGB15(16,  8,  2);	// Saddlebrown
	//YELLOWS
	_palRam[14] = RGB15(31, 29, 17);	// Khaki 1
	_palRam[15] = RGB15(28, 28,  0);	// Yellow 2
	_palRam[16] = RGB15(15, 15,  0);	// Olive
	//GREENS
	_palRam[17] = RGB15(22, 31, 24);	// Mint Green
	_palRam[18] = RGB15(2,  24, 10);	// Emerald
	_palRam[19] = RGB15(7,  17,  7);	// Cobalt Green
	//BLUES
	_palRam[20] = RGB15(16, 25, 31);	// Lightsky Blue
	_palRam[21] = RGB15(6,  19, 24);	// Peacock
	_palRam[22] = RGB15(5,  12, 16);	// Steelblue 4
	//PURPLES
	_palRam[23] = RGB15(31, 22, 31);	// Plum 1
	_palRam[24] = RGB15(28, 15, 28);	// Yellow 2
	_palRam[25] = RGB15(15,  0, 15);	// Purple
	
	// Borders, dialog box, I'm placing the palette a safe distance from the text
	// colors just in case we need the padding for later
	
	//_palRam[71] = RGB15(0, 0, 0);
	//_palRam[72] = RGB15(26, 26, 11);
	//_palRam[73] = RGB15(15, 24, 28);
	//_palRam[74] = RGB15(29, 30, 23);
	//_palRam[75] = RGB15(21, 22, 5);
	
	_palRam[71] = RGB15(15, 15, 28);
	_palRam[72] = RGB15(30, 30, 26);
	_palRam[73] = RGB15(20, 20, 20);
	_palRam[74] = RGB15(31, 31, 31);
	_palRam[75] = RGB15(21, 22, 5);
	
	// Swap back to ext palette mode once we've copied our colors into memory
	if(_screen == MAIN) vramSetBankE(VRAM_E_BG_EXT_PALETTE);
	if(_screen == SUB) vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
	
	_font = (u8 *)font;
	_border = (u8 *)dbox;
	_color = TS_WHITE;
	
	int i;
	//Populate lookup table with ASCII offset so that indexing char ' ' returns tile 0
	for( i = 0; i < 96; i++ ) {
		_chars[i+32] = i;
	}
	
	// set bg map to screen index, this is so we can write directly to tile ram 
	// and have non grid aligned text
	for( i = 0; i < 32*32; i++ ) {
		_mapRam[i] = i;
	}
	
	ClearScreen();
}

void TextSystem::PutChar( int x, int y, char c, int col) {
	int tile, px, py, row;
	
	// src == font tile, dst == vram tiles
	u16 *dst = _tileRam;
	u8 *src = _font + _chars[int(c)]*64;
	
	tile = (y/8)*32 + x/8;
	px = x%8;
	py = y%8;
	// character offset and width (variable width font) + px
	u8 cw = vwid[_chars[int(c)]] + px;
	
	dst += (tile*64 + py*8)/2; // divide by 2 to account for u16 vs u8
	
	int i, xoff, yoff = 0;
	
	// vram tiles are 8x8 pixels, and made of u16 data which contains 2 pixels per unit 
	// so to do single pixel blits we have to grab 2 pixels (1 u16) from vram and mask the pixel
	// we want to keep and then OR it with the new value to create a new 2 pixel value
	for( row = py; row < py+8; row++ ) {
		// check if we have descended into a neighboring tile and set y offset appropriately
		if(row < 8) yoff = 0;
		else 	    yoff = 992;
		
		for( i = px; i < cw; i++ ) {
			// We only blit non zero values, don't want to overwrite stuff, this will be handy for shadowing/dialog box effects
			if(src[i-px]) {
				// check if we have crossed into a neighboring tile and set x offset appropriately
				if(i < 8) xoff = 0;
				else	  xoff = 28;
				
				// Is the pixel even or odd, this determines how we mask the destination value we are keeping
				if( !(i&1) ) { 	//x even
					dst[i/2+xoff+yoff] = ( (dst[i/2+xoff+yoff]&0xFF00) | col );
				} else {	//x odd
					dst[i/2+xoff+yoff] = ( (dst[i/2+xoff+yoff]&0x00FF) | col<<8 );
				}
			}
		}
		//Adjust our read and write pointers by a row (8 bytes == 1 row of pixels)
		dst+=4; // 2 bytes * 4 = 8 bytes
		src+=8;	// 1 byte * 8 = 8 bytes
	}
}

// Places a dialog border piece.  These are fixed to tile grids, and x, y are in tile units (not pixels)
void TextSystem::PutBorderPiece( int x, int y, int id) {
	swiCopy(_border+(id*64), _tileRam+(x+(y*32))*32, 32);
}

// Places a full dialog box with with params describing position and width
void TextSystem::PutBorderBox( int x1, int x2, int y1, int y2, int fade ) {
	int xx, yy;
	// Place corners first
	PutBorderPiece( x1, y1, TS_BorderTL );
	PutBorderPiece( x2, y1, TS_BorderTR );
	PutBorderPiece( x2, y2, TS_BorderBR );
	PutBorderPiece( x1, y2, TS_BorderBL );
	
	// Place repeating horizontal pieces
	for(xx = x1+1; xx < x2; xx++) {
		PutBorderPiece( xx, y1, TS_BorderT );
		PutBorderPiece( xx, y2, TS_BorderB );
	}
	// Place repeating vertical pieces
	for(yy = y1+1; yy < y2; yy++) {
		PutBorderPiece( x1, yy, TS_BorderL );
		PutBorderPiece( x2, yy, TS_BorderR );
	}
	
	// Set window coordinates for transparency effect
	if(_screen == MAIN)	{
		REG_BLDY = fade;
		WIN1_X0 = x1*8 + 3;
		WIN1_X1 = x2*8 + 5;
		WIN1_Y0 = y1*8 + 3;
		WIN1_Y1 = y2*8 + 5;
	}
	if(_screen == SUB) {
		REG_BLDY_SUB = fade;
		SUB_WIN1_X0 = x1*8 + 3;
		SUB_WIN1_X1 = x2*8 + 5;
		SUB_WIN1_Y0 = y1*8 + 3;
		SUB_WIN1_Y1 = y2*8 + 5;
	}
}

void TextSystem::ClearBorderBox( int x1, int x2, int y1, int y2 ) {
	int xx, yy;
	
	// Place corners first
	swiCopy(&font, _tileRam+x1+y1*32, 32);
	swiCopy(&font, _tileRam+x2+y1*32, 32);
	swiCopy(&font, _tileRam+x2+y2*32, 32);
	swiCopy(&font, _tileRam+x1+y2*32, 32);
	
	// Place repeating horizontal pieces
	for(xx = x1+1; xx < x2; xx++) {
		PutBorderPiece( xx, y1, TS_BorderT );
		PutBorderPiece( xx, y2, TS_BorderB );
	}
	// Place repeating vertical pieces
	for(yy = y1+1; yy < y2; yy++) {
		PutBorderPiece( x1, yy, TS_BorderL );
		PutBorderPiece( x2, yy, TS_BorderR );
	}
}

// reads char array until it finds a non number, then converts to integer value
// returns value, however does not return offset of text to pointer
int TextSystem::GetValue(const char *text) {
	char cnum[3];
	int pos = 0;
	// while the character is 0-9
	while( 47 < text[pos] && text[pos] < 58 ) {
		cnum[pos] = text[pos];
		ASSERT(pos < 3); // We only allow values to 3 placeholders
		pos++;
	}
	return atoi(cnum);
}

int TextSystem::NumDigits(int v) {
	int numDigits = 0;
	int tmp = 1;
	
	// zero still represents a single digit (char)
	if( v == 0 ) return 1;
	// if it's a negative num
	if( v < 0 ) {
		v = -v; // we deal with abs
		numDigits++;
	}
	
	while( v >= tmp ) {
		numDigits++;
		tmp*=10;
	}
	return numDigits;
}

// Handles script tags for adjusting TS_Print behavior
const char* TextSystem::ExecTags(const char *text) {
	//will hold values from tags
	int val;
	
	while( *text != '}') {
		//Check for specific tags, no I don't care that I'm using a switch
		switch(*text) {
			
			case 'X':
				if( text[1] == ':') {
					val = GetValue(&text[2]);
					_dx = val;
					_x = val;
					text += NumDigits(val);
				} else {
					_dx = _x;
				}
				break;
			
			case 'Y':
				if( text[1] == ':') {
					val = GetValue(&text[2]);
					_dy = val;
					_y = val;
					text += NumDigits(val);
				} else {
					_dy = _y;
				}
				break;
			
			case 'x':
				if( text[1] == ':') {
					val = GetValue(&text[2]);
					_dx+= val;
					text += NumDigits(val);
				} 
				else {
					_dx = _x;
				}
				break;
			
			case 'y':
				//if there is a ':' we check for a value
				if( text[1] == ':') {
					val = GetValue(&text[2]);
					_dy+= val;
					text += NumDigits(val);
				} 
				//otherwise we reset dx to 0
				else {
					_dy = _y;
				}
				break;
			
			case 'C':
				if( text[1] == ':' ) {
					val = GetValue(&text[2]);
					_color = val;
					text += NumDigits(val);
				}
				else {
					_color = 1; //white
				}
				break; 
			// If we the character doesn't represent a known tag, we ignore it
			default:
				break;
		}
		text++;
	}
	return text;
}

void TextSystem::Print(int x, int y, const char *text) {
	char c;
	int pos;
	int wordLen;
	_x = x;
	_y = y;
	_dx = x;
	_dy = y;

	while( (c = *text) != 0 ) {
	    // Check length of next word
		pos = 0;
		wordLen = 0;
		
		// Check for carriage returns, and reset x, y on next line
		if(c == '\n' || c == '\r') {
			_dy += _lineSpace;
			_dx = _x;
		}
		// Handle all other characters
		else {
			// loop through characters until the word ends ( space is found )
			while( text[pos] > 33 ) { 
				//Ignore special tag characters when calculating word width in pixels
				if( text[pos] == '@' && text[pos+1] == '{' ) {
					pos+=2;
					while(text[pos] != '}') pos++;
					pos++; // skip '}'
				} else {
					wordLen += vwid[ _chars[ int(text[pos]) ] ];
					pos++;
				}
			}
	    	// Handle tags
	    	if( c == '@' && text[1] == '{' ) {
	    		// TS_ExecTags will apply all applicable tags, and once it's done
	    		// it will skip to the end of the tag scope so that we don't print
	    		// any tag characters, that's why it returns a new pointer to the text
	    		text = ExecTags(&text[1]);
	    	} 
	    	// Blit chars
	    	else {
	    		// If it breaks the margin, put the cursor at the beginning of the next line first
				if( wordLen > _margin - _dx ) {
					_dy += _lineSpace;
					_dx = _x;
				}

				//Blit char to VRAM
				PutChar( _dx, _dy, c, _color);
				//Push offset dx position by character width	    
				_dx += vwid[ _chars[int(c)] ]; // char width
			}
		}
		
		swiWaitForVBlank();
		swiWaitForVBlank();
		text++;
	}
}

void TextSystem::ClearScreen() {
	int i;
	
	for(i =0; i < 768; i++ ) {
		swiCopy(&font, _tileRam+32*i, 32);
	}
}

void TextSystem::ClearChar( int x, int y ) {
	PutChar(x, y, char(127), 0);
}

void TextSystem::EnableWindows() {
	int i;
	
	if(_screen == MAIN) {
		REG_DISPCNT |= DISPLAY_WIN1_ON;
		WIN_IN = WIN1_ALL | WIN1_GFX;
		WIN_OUT = WIN0_ALL ^ WIN0_GFX;
		if( _bgNum > 0 ) {
			for( i = 0; i < _bgNum; i++ ) {
				// Set blend src bgs 
				REG_BLDCNT |= BLEND_FADE_BLACK | BLEND_SRC_BG(i);
			}
			// Set blend src sprites
			REG_BLDCNT |= BLEND_SRC_SPRITE;
		}
		return;
	}
	if(_screen == SUB) {
		REG_DISPCNT_SUB |= DISPLAY_WIN1_ON;
		SUB_WIN_IN = WIN1_ALL | WIN1_GFX;
		SUB_WIN_OUT = WIN0_ALL ^ WIN0_GFX;
		if( _bgNum > 0 ) {
			for( i = 0; i < _bgNum; i++ ) {
				// Set blend src bgs
				REG_BLDCNT_SUB |= BLEND_FADE_BLACK | BLEND_SRC_BG(i);
			}
			REG_BLDCNT_SUB |= BLEND_SRC_SPRITE;
		}
		
		return;
	}
}

void TextSystem::DisableWindows() {
	int i;
	if(_screen == MAIN) {
		REG_DISPCNT &= ~DISPLAY_WIN1_ON;
		if( _bgNum > 0 ) {
			for( i = 0; i < _bgNum; i++ ) {
				REG_BLDCNT &= ~(BLEND_FADE_BLACK | BLEND_SRC_BG(i));
			}
			REG_BLDCNT &= ~BLEND_SRC_SPRITE;
		}
	}
	if(_screen == SUB) {
		REG_DISPCNT_SUB &= ~DISPLAY_WIN1_ON;
		if( _bgNum > 0 ) {
			for( i = 0; i < _bgNum; i++ ) {
				REG_BLDCNT_SUB &= ~(BLEND_FADE_BLACK | BLEND_SRC_BG(i));
			}
			REG_BLDCNT_SUB &= ~BLEND_SRC_SPRITE;
		}
	}
}