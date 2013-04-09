#ifndef _GAMECONSTANTS_H
#define _GAMECONSTANTS_H

// Include the Windows header file that�s needed for all Windows applications
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <xaudio2.h>
#include "SDKwavefile.h"

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <ctime>
#include <cstdlib>
#include <strsafe.h>

using namespace std;
// This header file contains all the constants & enumarated types for the game

enum eDirection {LEFT, RIGHT, UP, DOWN};
enum eState {INTRO, GAME, LOST, WON, REPLAY}; //Possible states for the game
enum eType {JELLY, SMALL, MED, LARGE, DEBRIS}; //Possible items to render

#endif