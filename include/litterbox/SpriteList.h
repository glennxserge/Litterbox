#ifndef SPRITELIST_H
#define SPRITELIST_H

//! \file SpriteList.h
//! \author J Mills
//! \date 9/15/2013 

#include "Sprite.h"

//! \addtogroup grpSpriteManager
//\{

/*! \struct node
 * node for sprite list
 */
struct node
{
	Sprite *pSp;	//!< Pointer to a sprite
	node *prev; 	//!< Pointer to the previous sprite node in the list
	node *next; 	//!< Pointer to the next sprite node in the list
};

/*! \class SpriteList
 * Keeps a list of all active sprites and manages their draw priority by Y position
 * can also determine whether a sprite that has been added to the sprite list already shares
 * graphics data with another sprite that is loaded
 */
class SpriteList
{
private:
	node *root;			//!< Pointer to the start of the sprite list
	node *conductor;	//!< Sprite list iterator, travels the sprite list
	
public:
	//! Constructor initializes empty list
	SpriteList();						
	//! Destructor deletes all nodes (does not delete actual sprites)
	~SpriteList();						
	//! Attaches new node to sprite list
	//! \param *_pSp A pointer to the sprite to attach to the pointer list
	void Append(Sprite *_pSp);
	//! Deletes node from sprite list
	//! \param *_pSp A pointer to the sprite to delete from the pointer list
	void Delete(Sprite *_pSp);
	//! Checks if sprite palette is already loaded into memory
	//! \param *_pSp A pointer to the sprite with palette data
	//! \return True or False whether the sprite palette is already loaded
	int IsPaletteLoaded(Sprite *_pSp);
	//! How many instances of the palette are currently loaded in memory
	//! \param *_pSp A pointer to the sprite with palette data to compare to
	//! \return The number of sprites that share this particular sprite palette (not including the given sprite)
	int PaletteInstances(Sprite *_pSp);
	//! Check if sprite is already in the list
	//! \param *_pSp A pointer to the sprite with palette data
	//! \return True or False depending on if the given sprite is already in the SpList
	bool IsSpriteInList(Sprite *_pSp);
	//! Iterate over sprite list and copy them to OAM mem
	void PutSpriteList();
	//! Update sprite animation frames
	void AnimateList();
	//! Sort sprite list by y position
	void SortByY();
	//! Swap two nodes
	/*! \param *A Pointer to first sprite node
	 *  \param *B Pointer to second sprite node
	 */
	void SwapNodes(node *A, node *B);
};

//\}
#endif //SPRITELIST_H