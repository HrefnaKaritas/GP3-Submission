#include "GameState.h"

GameState::GameState() // Default constructor
{
	GameState::mState=INTRO; 
}

GameState::GameState(eState theState) // Constructor
{
	GameState::mState=theState;
}

eState GameState::getState() // Get current game state
{
	return GameState::mState;
}

void GameState::setState(eState theState) // Set game state
{
	GameState::mState = theState;
}

