/*
cItems.h
- Header file for catchable items
*/

#ifndef _CITEMS_H
#define _CITEMS_H
#include "cSprite.h"
#include "GameConstants.h"

class cItems : public cSprite
{
private:
	int mScore;
	eDirection mDirection;
	eType mType;
	LPCSTR image;
	bool bActive;

public:
	cItems();
	cItems(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename); // Constructor
	void update(); // Update item position based on the translation
	void setItem(eType theType); //Decide which item is being used
	eType getItem(); //Get item type
	void setScore(); //Set score, varies between items
	int getScore(); //Get score
	void setImage();
	void setActive(bool b_Active);
	bool getActive();
	LPCSTR getImage();
}; 

#endif