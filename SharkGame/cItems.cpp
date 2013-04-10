#include "cItems.h"

//Default constructor
cItems::cItems(): cSprite()
{
	mDirection = RIGHT;
	mType = static_cast<eType>(rand() % 5);
	cItems::setImage();
	cItems::setScore();
	cItems::setActive(true);
}

// Constructor
cItems::cItems(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename): cSprite(sPosition,pd3dDevice,theFilename)
{
	mDirection = RIGHT;
	mType = static_cast<eType>(rand() % 5);
	cItems::setImage();
	cItems::setScore();
	cItems::setActive(true);
}

// Update position
void cItems::update()
{
	D3DXVECTOR2 tempV2;
	D3DXVECTOR3 tempV3;
	tempV2 = cItems::getSpritePos2D() + cItems::getTranslation();
	tempV3 = D3DXVECTOR3(tempV2.x,tempV2.y,0.0f);
	cItems::setSpritePos(tempV3);
	cSprite::update();
}

void cItems::setItem(eType theType) // Set the item type used
{
	cItems::mType = theType;
}

eType cItems::getItem() // Get the item type used
{
	return cItems::mType;
}

void cItems::setScore()
{
	if (cItems::getItem() == SMALL)  //Score for small fish
	{
		mScore = 5;
	}
	else if (cItems::getItem() == MED) //Score for medium fish
	{
		mScore = 2;
	}
	else if (cItems::getItem() == LARGE) //Score for large fish
	{
		mScore = 1;
	}
	else if (cItems::getItem() == JELLY) //Score for jelly fish (negative)
	{
		mScore = (-2);
	}
	else if (cItems::getItem() == DEBRIS) //Score for debris, no score
	{
		mScore = (0);
	}
}

int cItems::getScore()
{
	return mScore;
}

void cItems::setImage()
{
	if (mType == SMALL)
	{
		image = "Images\\SmallFish.png";
	}
	else if (mType == MED)
	{
		image = "Images\\MediumFish.png";
	}
	else if (mType == LARGE)
	{
		image = "Images\\LargeFish.png";
	}
	else if (mType == JELLY)
	{
		image = "Images\\Jellyfish.png";
	}
	else if (mType == DEBRIS)
	{
		image = "Images\\Debris.png";
	}
}

LPCSTR cItems::getImage()
{
	return image;
}

void cItems::setActive(bool b_Active)
{
	cItems::bActive = b_Active;
}

bool cItems::getActive() 
{
	return cItems::bActive;
}