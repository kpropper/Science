/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	ScienceGame.cpp

	This is a test game application, a game that demonstrates use of the 
	SideScrollerFramework to make a little scrolling, interactive demo. It
	demonstrates the rendering of images and text as well as responding to
	key presses and button cicks. Students should make their own named game
	applictions using a similar pattern, gradually adding other components,
	like additional gui controls, tiles, sprites, ai, and physics.
 */

#include "bugs_VS\stdafx.h"

// Science GAME INCLUDES
#include "bugs\ScienceButtonEventHandler.h"
#include "bugs\ScienceCollisionListener.h"
#include "bugs\ScienceDataLoader.h"
#include "bugs\ScienceGame.h"
#include "bugs\ScienceKeyEventHandler.h"
#include "bugs\ScienceMouseEventHandler.h"
#include "bugs\ScienceTextGenerator.h"

// GAME OBJECT INCLUDES
#include "sssf\game\Game.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\state\GameState.h"
#include "sssf\gui\Cursor.h"
#include "sssf\gui\GameGUI.h"
#include "sssf\gui\ScreenGUI.h"
#include "sssf\input\GameInput.h"
#include "sssf\os\GameOS.h"
#include "sssf\text\GameText.h"

// WINDOWS PLATFORM INCLUDES
#include "sssf\platforms\Windows\WindowsOS.h"
#include "sssf\platforms\Windows\WindowsInput.h"
#include "sssf\platforms\Windows\WindowsTimer.h"

// DIRECTX INCLUDES
#include "sssf\platforms\DirectX\DirectXGraphics.h"
#include "sssf\platforms\DirectX\DirectXTextureManager.h"

/*
	WinMain - This is the application's starting point. In this method we will construct a Game object, 
	then initialize all the platform-dependent technologies, then construct all the custom data for our 
	game, and then initialize the Game with	our custom data. We'll then start the game loop.
*/

struct Nums
{
	int num1;
	int num2;
};

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
	// CREATE THE GAME
	Game *scienceGame = new Game();

	// FIRST WE'LL SETUP THE DATA LOADER, SINCE IT MAY NEED TO READ
	// IN DATA TO SETUP OTHER STUFF
	ScienceDataLoader *scienceDataLoader = new ScienceDataLoader();
	scienceDataLoader->initWinHandle(hInstance, nCmdShow);
	scienceGame->setDataLoader(scienceDataLoader);
	scienceDataLoader->loadGame(scienceGame, W_INIT_FILE);
	
	// WHAT WE SHOULD BE DOING HERE IS LOADING THE GAME DATA FROM FILES. THIS
	// MEANS THE GUIS THEMSELVES AS WELL AS THE LEVELS. THAT WILL BE LEFT
	// FOR BECHMARK HWS. FOR NOW WE WILL JUST HARD CODE THE LOADING OF THE GUI

	// LOAD THE GUI STUFF, AGAIN, NOTE THAT THIS SHOULD REALLY
	// BE DONE FROM A FILE, NOT HARD CODED
	scienceDataLoader->loadGUI(scienceGame, W_GUI_INIT_FILE);

	// SPECIFY WHO WILL HANDLE BUTTON EVENTS
	ScienceButtonEventHandler *scienceButtonHandler = new ScienceButtonEventHandler();
	GameGUI *gui = scienceGame->getGUI();
	gui->registerButtonEventHandler((ButtonEventHandler*)scienceButtonHandler);

	// SPECIFY WHO WILL HANDLE KEY EVENTS
	ScienceKeyEventHandler *scienceKeyHandler = new ScienceKeyEventHandler();
	scienceGame->getInput()->registerKeyHandler((KeyEventHandler*)scienceKeyHandler);

	// SPECIFY WHO WILL HANDLE MOUSE EVENTS NOT RELATED TO THE GUI
	ScienceMouseEventHandler *scienceMouseHandler = new ScienceMouseEventHandler();
	scienceGame->getInput()->registerMouseHandler((MouseEventHandler*)scienceMouseHandler);

	// THIS WILL HANDLE PHYSICS COLLISION EVENTS
	ScienceCollisionListener *scienceCollisionListener = new ScienceCollisionListener();
	scienceGame->getGSM()->getPhysics()->setCollisionListener(scienceCollisionListener);

	// START THE GAME LOOP
	scienceGame->runGameLoop();

	// GAME'S OVER SHUTDOWN ALL THE STUFF WE CONSTRUCTED HERE
	delete (WindowsOS*)scienceGame->getOS();
	delete (WindowsInput*)scienceGame->getInput();
	delete (WindowsTimer*)scienceGame->getTimer();
	delete (DirectXGraphics*)scienceGame->getGraphics();
	delete (ScienceTextGenerator*)scienceGame->getText()->getTextGenerator();
	delete scienceButtonHandler;
	delete scienceKeyHandler;
	delete scienceGame;

	// AND RETURN
	return 0;
}