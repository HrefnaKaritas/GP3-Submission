/*
GameState.h
Header file for possible game states
*/

#ifndef _GAMESTATE_H
#define _GAMESTATE_H
#include "GameConstants.h"

class GameState 
{
private:
	eState mState;

public:
	GameState();
	GameState(eState); // Constructor
	eState getState(); // Returns the current game state
	void setState(eState theState); // Set the current state for the game

};
#endif