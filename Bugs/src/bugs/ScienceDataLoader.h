/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	ScienceDataLoader.h

	This class provides a custom importer for the ScienceGame to import
	game data, gui data, and world (i.e. level) data.
*/
#pragma once
#include "bugs_VS\stdafx.h"
#include "sssf\data_loader\GameDataLoader.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\platforms\DirectX\DirectXTextureManager.h"
#include "Box2D\Box2D.h"

class ScienceDataLoader : public GameDataLoader
{
private:
	// WE NEED THESE GUYS TO INIT OUR WINDOWS WINDOW
	HINSTANCE hInstance;
	int nCmdShow;

public:
	ScienceDataLoader()	{}
	~ScienceDataLoader()	{}

	// INLINED MUTATOR METHOD
	void initWinHandle(HINSTANCE initHInstance, int initNCmdShow)
	{
		hInstance = initHInstance;
		nCmdShow = initNCmdShow;
	}


	// THESE SHOULD BE LOADING DATA FROM FILES. THEY
	// ARE ALL DEFINED IN SciceneDataLoader.cpp
	void loadGame(Game *game, wstring gameInitFile);
	void loadGUI(Game *game, wstring guiInitFile);
	void loadWorld(Game *game, wstring levelInitFile);

	// THESE ARE HARD-CODED EXAMPLES OF GUI DATA LOADING
	void hardCodedLoadGUIExample(Game *game);

	// SOME HELPER METHODS FOR SETTING UP THE GAME
	void initColors(GameGraphics *graphics,	map<wstring,wstring> *properties);
	void initViewport(GameGUI *gui, map<wstring,wstring> *properties);
	void makeRandomJumpingBot(Game *game, AnimatedSpriteType *randomJumpingBotType, float initX, float initY);
//	void makeRandomEnemyBot(Game *game, AnimatedSpriteType *randomEnemyBotType, float initX, float initY);     //Added to add Enemys to the level

	// AND SOME HELPER METHODS FOR LOADING THE GUI
	void initCursor(GameGUI *gui, DirectXTextureManager *guiTextureManager);
	void initSplashScreen(Game *game, GameGUI *gui,	DirectXTextureManager *guiTextureManager);
	void initMainMenu(GameGUI *gui,	DirectXTextureManager *guiTextureManager);
	void initInGameGUI(GameGUI *gui, DirectXTextureManager *guiTextureManager);
};