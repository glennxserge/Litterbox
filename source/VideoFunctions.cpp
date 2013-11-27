#include <nds.h>
#include "VideoFunctions.h"

// Author J. Mills
// 9/15/2013

void VideoInitialize() {
// Main Screen setup
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankE(VRAM_E_BG_EXT_PALETTE);
	vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
  // Sub Screen setup
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);
	vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);
  // Mode Setup
	videoSetMode(MODE_0_2D | DISPLAY_BG_EXT_PALETTE);
	videoSetModeSub(MODE_0_2D | DISPLAY_BG_EXT_PALETTE);
}