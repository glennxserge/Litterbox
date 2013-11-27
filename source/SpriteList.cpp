#include "SpriteList.h"
#include <stdio.h>

// File SpriteList.cpp
// Author J Mills
// Date 9/15/2013 

SpriteList::SpriteList() {
	root = new node;
	root->prev = 0;
	root->next = 0;
	root->pSp = 0;
}

SpriteList::~SpriteList() {
	conductor = root;
	if(conductor != 0) {
		while(conductor->next != 0) {
			conductor = conductor->next;
			delete conductor->prev;
		}
		delete conductor;
	}
}

void SpriteList::Append(Sprite *_pSp) {
	conductor = root;
	if(conductor != 0) {
		while(conductor->next != 0) {
			conductor = conductor->next;
		}
	}
	conductor->next = new node;
	conductor->next->prev = conductor;
	conductor->next->next = 0;
	conductor = conductor->next;
	conductor->pSp = _pSp;
}

void SpriteList::Delete(Sprite *_pSp) {
	conductor = root;
	
	if(conductor != 0) {
		while(conductor->next != 0) {
			conductor = conductor->next;
			//Found node to delete
			if(conductor->pSp == _pSp) {
				if(conductor->prev != 0) {
					conductor->prev->next = conductor->next;
				}	
				if(conductor->next != 0) {
					conductor->next->prev = conductor->prev;
				}
				delete conductor;
				return;
			}
		}
	}
}

int SpriteList::IsPaletteLoaded(Sprite *_pSp) {
	conductor = root;
	if(conductor != 0) {
		while(conductor->next != 0) {
			conductor = conductor->next;
			//Check if they use the same gfx
			if( conductor->pSp->gfx_t->paletteEntries == _pSp->gfx_t->paletteEntries ) return conductor->pSp->palette_num;
		}
	}
	return -1;
}

int SpriteList::PaletteInstances(Sprite *_pSp) {
	int count = 0;
	conductor = root;
	if(conductor != 0) {
		while(conductor->next != 0) {
			conductor = conductor->next;
			//Is it the same palette?
			if( conductor->pSp->palette_num == _pSp->palette_num ) count++;
		}
	}
	return count;
}

bool SpriteList::IsSpriteInList(Sprite *_pSp) {
	conductor = root;
	if(conductor != 0) {
		while(conductor->next != 0) {
			conductor = conductor->next;
			//Is it the same palette?
			if( conductor->pSp == _pSp ) return true;
		}
	}
	return false;
}

void SpriteList::PutSpriteList() {
	conductor = root;
	if(conductor != 0) {
		while(conductor->next != 0) {
			conductor = conductor->next;
			conductor->pSp->PutSpriteOam();
		}
	}
}

void SpriteList::AnimateList() {
	conductor = root;
	if(conductor != 0) {
		while(conductor->next != 0) {
			conductor = conductor->next;
			conductor->pSp->Animate();
		}
	}
}

void SpriteList::SortByY() {
	node* bubbleEnd;
	bubbleEnd->prev = 0;
	bubbleEnd->next = 0;
	bubbleEnd->pSp = 0;
	
	node* current = root->next;
	
	
	int i = 0;
	consoleClear();
	while( root->next->next != bubbleEnd )
	{		
		//If node A.y is greater than B.y, swap them so that the draw order makes sense
		if( current->pSp->y > current->next->pSp->y ) {
			SwapNodes(current, current->next);
		}		
		
		current = current->next;
		
		// When we hit either the end of the list or the bubbleEnd, reassign bubbleEnd 
		if( current->next == 0 || current->next == bubbleEnd ) {
			bubbleEnd = current;
			current->pSp->sprite_oam_index = i++;
			current = root->next;
		}
	}
	root->next->pSp->sprite_oam_index = i;
}

void SpriteList::SwapNodes(node* A, node* B) {
	Sprite *tmpA = A->pSp;
	A->pSp = B->pSp;
	B->pSp = tmpA;
}