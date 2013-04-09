/*
=================
main.cpp
Main entry point for the Card application
=================
*/

#include "GameConstants.h"
#include "GameResources.h"
#include "cD3DManager.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXTexture.h"
#include "cSprite.h"
#include "cXAudio.h"
#include "GameState.h"
#include "cD3DXFont.h"
#include "cItems.h"

using namespace std;

HINSTANCE hInst; // global handle to hold the application instance
HWND wndHandle; // global variable to hold the window handle

// Get a reference to the DirectX Manager
static cD3DManager* d3dMgr = cD3DManager::getInstance();

// Get a reference to the DirectX Sprite renderer Manager 
static cD3DXSpriteMgr* d3dxSRMgr = cD3DXSpriteMgr::getInstance();

// Vectors for the shark and catchable items
D3DXVECTOR2 Shark = D3DXVECTOR2(300,300);
D3DXVECTOR2 itemTrans = D3DXVECTOR2(300,300);

// Catchable items
vector<cItems*> aItem;
vector<cItems*>::const_iterator iterRO;
vector<cItems*>::iterator iter;
vector<cItems*>::iterator index;

RECT clientBounds;

GameState gameState;

int gScore = 0; // Keep track of score
char gScoreStr[50];

int gLives = 3; // Keep track of lives
char gLivesStr[50];

cXAudio gThemeMusic;

/*
==================================================================
* LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
* LPARAM lParam)
* The window procedure
==================================================================
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Check any available messages from the queue

	if (gameState.getState() == INTRO)
	{
		switch (message)
		{
		case WM_KEYDOWN: // To get into the game state
			{	
				if (wParam == VK_SPACE)
				{
				gameState.setState(GAME);
				return 0;
				}
			}
		case WM_CLOSE:
			{
			// Exit the Game
				PostQuitMessage(0);
					return 0;
			}

			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
		}

	}

	else if (gameState.getState() == GAME)
	{
		switch (message)
		{
				case WM_KEYDOWN:
					{
						if (wParam == VK_LEFT)
						{
							Shark.x -= 10.0f;
							return 0;
						}
						if (wParam == VK_RIGHT)
						{
							Shark.x += 10.0f;
							return 0;
						}
						if (wParam == VK_UP)
						{
							Shark.y -= 10.0f;
							return 0;
						}
						if (wParam == VK_DOWN)
						{
							Shark.y += 10.0f;
							return 0;
						}
						return 0;
						
					}
			case WM_CLOSE:
				{
				// Exit the Game
					PostQuitMessage(0);
					 return 0;
				}

			case WM_DESTROY:
				{
					PostQuitMessage(0);
					return 0;
				}
			
		}
	}
	// Always return the message to the default window
	// procedure for further processing
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/*
==================================================================
* bool initWindow( HINSTANCE hInstance )
* initWindow registers the window class for the application, creates the window
==================================================================
*/
bool initWindow( HINSTANCE hInstance )
{
	WNDCLASSEX wcex;
	// Fill in the WNDCLASSEX structure. This describes how the window
	// will look to the system
	wcex.cbSize = sizeof(WNDCLASSEX); // the size of the structure
	wcex.style = CS_HREDRAW | CS_VREDRAW; // the class style
	wcex.lpfnWndProc = (WNDPROC)WndProc; // the window procedure callback
	wcex.cbClsExtra = 0; // extra bytes to allocate for this class
	wcex.cbWndExtra = 0; // extra bytes to allocate for this instance
	wcex.hInstance = hInstance; // handle to the application instance
	wcex.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_MyWindowIcon)); // icon to associate with the application
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);// the default cursor
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // the background color
	wcex.lpszMenuName = NULL; // the resource name for the menu
	wcex.lpszClassName = "SharkGame"; // the class name being created
	wcex.hIconSm = LoadIcon(hInstance,"Balloon.ico"); // the handle to the small icon

	RegisterClassEx(&wcex);
	// Create the window
	wndHandle = CreateWindow("SharkGame",			// the window class to use
							 "Shark Game",			// the title bar text
							WS_OVERLAPPEDWINDOW,	// the window style
							CW_USEDEFAULT, // the starting x coordinate
							CW_USEDEFAULT, // the starting y coordinate
							800, // the pixel width of the window
							600, // the pixel height of the window
							NULL, // the parent window; NULL for desktop
							NULL, // the menu for the application; NULL for none
							hInstance, // the handle to the application instance
							NULL); // no values passed to the window
	// Make sure that the window handle that is created is valid
	if (!wndHandle)
		return false;
	// Display the window on the screen
	ShowWindow(wndHandle, SW_SHOW);
	UpdateWindow(wndHandle);
	return true;
}

/*
==================================================================
// This is winmain, the main entry point for Windows applications
==================================================================
*/
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	// Initialize the window
	if ( !initWindow( hInstance ) )
		return false;
	// called after creating the window
	if ( !d3dMgr->initD3DManager(wndHandle) )
		return false;
	if ( !d3dxSRMgr->initD3DXSpriteMgr(d3dMgr->getTheD3DDevice()))
		return false;

	GetClientRect(wndHandle,&clientBounds);

	D3DXVECTOR3 itemPos; 
	int numItems = 10;

	for(int loop = 0; loop < numItems; loop++)
	{
		itemPos = D3DXVECTOR3((float)clientBounds.right/(loop+2),(float)clientBounds.bottom/(loop+2),0);
		aItem.push_back(new cItems());
		aItem[loop]->setSpritePos(itemPos);
		aItem[loop]->setTexture(d3dMgr->getTheD3DDevice(),aItem[loop]->getImage());
		aItem[loop]->setTranslation(D3DXVECTOR2(-5.0f,0.0f));
	}

	sprintf_s( gScoreStr, 50, "Score : %d", gScore);
	sprintf_s( gLivesStr, 50, "Lives left: %d", gLives);

	// Grab the frequency of the high def timer
	__int64 freq = 0;				// measured in counts per second;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	float sPC = 1.0f / (float)freq;			// number of seconds per count

	__int64 currentTime = 0;				// current time measured in counts per second;
	__int64 previousTime = 0;				// previous time measured in counts per second;

	float numFrames   = 0.0f;				// Used to hold the number of frames
	float timeElapsed = 0.0f;				// cumulative elapsed time

	GetClientRect(wndHandle,&clientBounds);

	float fpsRate = 1.0f/25.0f;

	LPDIRECT3DSURFACE9 introSurface;			//The intro surface
	LPDIRECT3DSURFACE9 aSurface;				// the Direct3D surface
	LPDIRECT3DSURFACE9 theBackbuffer = NULL;	// This will hold the back buffer
	
	D3DXVECTOR3 sharkPos = D3DXVECTOR3(-300,300,0);		// Set shark starting position
	cSprite theShark(sharkPos,d3dMgr->getTheD3DDevice(),"Images\\Shark.png");  // Get shark image

	D3DXVECTOR3 aItemPos;	// Declare the item position variable

	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	introSurface = d3dMgr->getD3DSurfaceFromFile("Images\\IntroScreen.png"); // Create the info screen surface
	aSurface = d3dMgr->getD3DSurfaceFromFile("Images\\background.png");	// Create the game background surface
	
	cD3DXFont* MirischFont = new cD3DXFont(d3dMgr->getTheD3DDevice(),hInstance, "MIRISCH");	// load custom font

	//Score text
	RECT textPos;
	SetRect(&textPos, 50, 10, 400, 100);

	//Lives left text 
	RECT textPos2;
	SetRect(&textPos2, 500, 10, 750, 100);

	while( msg.message!=WM_QUIT )
	{
		// Check the message queue
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			// Game code goes here

			if (gameState.getState() == INTRO)
			{
				d3dMgr->beginRender();
				theBackbuffer = d3dMgr->getTheBackBuffer();
				d3dMgr->updateTheSurface(introSurface, theBackbuffer);
				d3dMgr->releaseTheBackbuffer(theBackbuffer);
				d3dMgr->endRender();
			}
			else if (gameState.getState() == GAME)
			{
				QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
				float dt = (currentTime - previousTime)*sPC;

				//gThemeMusic.playSound(L"Sounds\\theme.wav",false);
				sharkPos = D3DXVECTOR3(Shark.x,Shark.y,0);
				theShark.setSpritePos(sharkPos);
				theShark.update();
				itemPos = D3DXVECTOR3(itemTrans.x,itemTrans.y,0);

				timeElapsed += dt;

				if(timeElapsed > fpsRate)
				{
					for(iter = aItem.begin(); iter != aItem.end(); ++iter)
					{
						(*iter)->update();
						aItemPos = (*iter)->getSpritePos();
					}

					d3dMgr->beginRender();
					theBackbuffer = d3dMgr->getTheBackBuffer();
					d3dMgr->updateTheSurface(aSurface, theBackbuffer);
					d3dMgr->releaseTheBackbuffer(theBackbuffer);
				
					d3dxSRMgr->beginDraw();
					d3dxSRMgr ->setTheTransform(theShark.getSpriteTransformMatrix());
					d3dxSRMgr ->drawSprite(theShark.getTexture(),NULL,NULL,NULL,0xFFFFFFFF);    //&theShark.getSpritePos()
					for(iter = aItem.begin(); iter != aItem.end(); ++iter)
					{
						d3dxSRMgr->setTheTransform((*iter)->getSpriteTransformMatrix());  
						d3dxSRMgr->drawSprite((*iter)->getTexture(),NULL,NULL,NULL,0xFFFFFFFF);
					}
				}
				d3dxSRMgr->endDraw();		
				MirischFont->printText(gScoreStr,textPos);
				MirischFont->printText(gLivesStr,textPos2);
				d3dMgr->endRender();

			}
		}
	}
	d3dxSRMgr->cleanUp();
	d3dMgr->clean();
	return (int) msg.wParam;
}

// Problems:
// Shark moves with the items
// Delay time between items
// Items need to be a different height
// Font for lives left