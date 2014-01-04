#include "Sprite.h"
#include "Assert.h"
#include <stdio.h>

// Author J Mills
// Date 9/15/2013 

Sprite::Sprite()
{
	pos = Vec2d(0,0);
	gfx_t = 0;
	palette_num = 0;
	current_frame = 0;
	sub_frames = 0;
	delay = 0;
	start_frame = 0;
	end_frame = 1;
	priority = 2;
}

Sprite::Sprite(Vec2d _p, int _start_frame, int _end_frame, int* _delay, graphic_t* gfx)
{
	pos = _p;
	gfx_t = gfx;
	palette_num = 0;
	current_frame = _start_frame;
	sub_frames = 0;
	delay = _delay;
	start_frame = _start_frame;
	end_frame = _end_frame;
	priority = 2;
	hidden = false;
}

void Sprite::SetupSprite(Vec2d _p, int _current_frame, int* _delay, int _palette_num)
{
	pos = _p;
	palette_num = _palette_num;
	current_frame = _current_frame;
	sub_frames = 0;
	delay = _delay;
	start_frame = 0;
	end_frame = 1;
}

void Sprite::Animate()
{
	// add to sub_frame and determine whether the animation frame needs to change
	sub_frames++;
	if(sub_frames > delay[current_frame])
	{
		// go to next animation frame and reset the sub_frame
		current_frame++;
		sub_frames = 0;
		
		// if we are at the end of the animation then we cycle back
		if (current_frame > end_frame) current_frame = start_frame;
		
		// specify frame offset in gfx 
		const u8* gfx_offset = gfx_t->tileEntries + current_frame * 16 * 16;
		dmaCopy(gfx_offset, sprite_gfx_mem, 16*16);
	}
}

void Sprite::SetFrame(int frame)
{
	current_frame = frame;
	const u8* gfx_offset = gfx_t->tileEntries + current_frame * 16 * 16;
	dmaCopy(gfx_offset, sprite_gfx_mem, 16*16);
}

void Sprite::PutSpriteOam()
{
	oamSet(_oam, sprite_oam_index, pos.x, pos.y, priority, palette_num, SpriteSize_16x16, SpriteColorFormat_256Color, 
		sprite_gfx_mem, -1, false, hidden, false, false, false);
}

void Sprite::InitializeOam(OamState *oam, int oam_index)
{
	_oam = oam;
	sprite_oam_index = oam_index;
	sprite_gfx_mem = oamAllocateGfx(_oam, SpriteSize_16x16, SpriteColorFormat_256Color);
	
	//We go ahead and copy the sprite graphics so it is visible initially
	const u8* gfx_offset = gfx_t->tileEntries + current_frame * 16 * 16;
		dmaCopy(gfx_offset, sprite_gfx_mem, 16*16);
}