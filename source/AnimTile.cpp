#include "AnimTile.h"

// AnimTile.cpp
// Author J. Mills
// 9/15/2013

void AnimUpdateTile(AnimTile *a, int *t, int *f, graphic_t *gptr, u8 *tmem)
{
	(*t)++;
	if( (*t) > a->freq[(*f)])
	{
		(*t) = 0;
		if( (*f) < a->len - 1)
		{
			(*f)++;
		}
		else
		{
			(*f) = 0;
		}
		swiCopy(gptr->tileEntries+(a->ID[(*f)]*4)*64, tmem + a->ID[0]*4*64, 32);
		swiCopy(gptr->tileEntries+(a->ID[(*f)]*4+1)*64, tmem + (a->ID[0]*4+1)*64, 32);
		swiCopy(gptr->tileEntries+(a->ID[(*f)]*4+2)*64, tmem + (a->ID[0]*4+2)*64, 32);
		swiCopy(gptr->tileEntries+(a->ID[(*f)]*4+3)*64, tmem + (a->ID[0]*4+3)*64, 32);	
	}
}