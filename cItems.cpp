#include "cItems.h"

//Default constructor
cItems::cItems(): cSprite()
{
	mDirection = RIGHT;
	//cSprite::setTranslation(D3DXVECTOR2 (-5.0f,0.0f));
	mType = static_cast<eType>(rand() % 5);
	cItems::setImage();
	cItems::setScore();
}

// Constructor
cItems::cItems(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename): cSprite(sPosition,pd3dDevice,theFilename)
{
	mDirection = RIGHT;
	//cSprite::setTranslation(D3DXVECTOR2 (-5.0f,0.0f));
	mType = static_cast<eType>(rand() % 5);
	cItems::setImage();
	cItems::setScore();
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

void cItems::setItem(eType theType)
{
	cItems::mType = theType;
}

eType cItems::getItem() //Get the item type used
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
	else if (cItems::getItem() == DEBRIS) //Score for debris (irrelivant)
	{
		mScore = 0;
	}
	//cItems::mScore = theScore;
}

int cItems::getScore()
{
	return mScore;
}

void cItems::setImage()
{
	if (mType == SMALL)
	{
		image = "Images\\smallFish.png";
	}
	else if (mType == MED)
	{
		image = "Images\\mediumFish.png";
	}
	else if (mType == LARGE)
	{
		image = "Image\\largeFish.png";
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

bool cItems::getActive() //Get the item type used
{
	return cItems::bActive;
}