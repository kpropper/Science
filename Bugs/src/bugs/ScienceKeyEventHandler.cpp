/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	ScienceKeyEventHandler.cpp

	See ScienceKeyEventHandler.h for a class description.
*/

#include "bugs_VS\stdafx.h"
#include "bugs\ScienceGame.h"
#include "bugs\ScienceKeyEventHandler.h"
#include "sssf\game\Game.h"
#include "sssf\game\WStringTable.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\physics\Physics.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\state\GameState.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gui\Cursor.h"
#include "sssf\gui\GameGUI.h"
#include "sssf\input\GameInput.h"
#include "sssf\timer\GameTimer.h"
#include "sssf\platforms\Windows\WindowsTimer.h"
#include "sssf\gsm\ai\bots\RandomJumpingBot.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
	handleKeyEvent - this method handles all keyboard interactions. Note that every frame this method
	gets called and it can respond to key interactions in any custom way. Ask the GameInput class for
	key states since the last frame, which can allow us to respond to key presses, including when keys
	are held down for multiple frames.
*/
void ScienceKeyEventHandler::handleKeyEvents(Game *game)
{
	// WE CAN QUERY INPUT TO SEE WHAT WAS PRESSED
	GameInput *input = game->getInput();

	// LET'S GET THE PLAYER'S PHYSICAL PROPERTIES, IN CASE WE WANT TO CHANGE THEM
	GameStateManager *gsm = game->getGSM();
	AnimatedSprite *player = gsm->getSpriteManager()->getPlayer();
	PhysicalProperties *pp = player->getPhysicalProperties();
	Viewport *viewport = game->getGUI()->getViewport();
	float viewportWidth = (viewport->getViewportWidth())/2;
	float viewportHeight = (viewport->getViewportHeight())/2;


	SpriteManager *spriteManager = gsm->getSpriteManager();
	AnimatedSpriteType *enemySpriteType = spriteManager->getSpriteType(1);
	
	// INITALIZE RANDOM SEED
	srand(time(NULL));

	// IF THE GAME IS IN PROGRESS
	if (gsm->isGameInProgress())
	{
		if (input->isKeyDownForFirstTime(P_KEY))
		{
			gsm->getPhysics()->togglePhysics();
		}
		if (input->isKeyDownForFirstTime(T_KEY))
		{
			gsm->getPhysics()->activateForSingleUpdate();
		}
		if (input->isKeyDownForFirstTime(D_KEY))
		{
			viewport->toggleDebugView();
			game->getGraphics()->toggleDebugTextShouldBeRendered();
		}
		if (input->isKeyDownForFirstTime(L_KEY))
		{
			game->getGraphics()->togglePathfindingGridShouldBeRendered();
		}
		if (input->isKeyDownForFirstTime(F_KEY))
		{
			game->getGraphics()->togglePathfindingPathShouldBeRendered();
		}

		bool viewportMoved = false;
		float viewportVx = 0.0f;
		float viewportVy = 0.0f;
		float viewportX = viewport->getViewportX();
		float viewportY = viewport->getViewportY();

		if (input->isKeyDown(UP_KEY))
		{
			viewportVy -= MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(DOWN_KEY))
		{
			viewportVy += MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(LEFT_KEY))
		{
			viewportVx -= MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}
		if (input->isKeyDown(RIGHT_KEY))
		{
			viewportVx += MAX_VIEWPORT_AXIS_VELOCITY;
			viewportMoved = true;
		}

		//IF THE VIEWPORT IS NOT BEING MOVED BY THE USER MAKE SURE THE PLAYER SPRITE IS ONSCREEN
		if (!viewportMoved)
		{
			//300 WIDTH BUFFER ALLOWS THE PLAYER TO ORIENT THE SCREEN AS THEY SEE FIT
			if (viewportX > pp->getX() - viewportWidth + 300 || viewportX < pp->getX() - viewportWidth - 300)
			{
				if (viewportX > pp->getX() - viewportWidth - 10)
				{
					viewportVx -= MAX_VIEWPORT_AXIS_VELOCITY;
					viewportMoved = true;
				}

				if (viewportX < pp->getX() - viewportWidth + 10)
				{
					viewportVx += MAX_VIEWPORT_AXIS_VELOCITY;
					viewportMoved = true;
				}
			}

			//150 WIDTH BUFFER ALLOWS THE PLAYER TO ORIENT THE SCREEN AN THEY SEE FIT
			if (viewportY > pp->getY() - viewportHeight - 150 || viewportX < pp->getX() - viewportHeight + 150 )
			{
				if (viewportY < pp->getY() - viewportHeight + 10)
				{
					viewportVy += MAX_VIEWPORT_AXIS_VELOCITY;
					viewportMoved = true;
				}

				if (viewportY > pp->getY() - viewportHeight - 10)
				{
					viewportVy -= MAX_VIEWPORT_AXIS_VELOCITY;
					viewportMoved = true;
				}
			}
		}

		if (viewportMoved)
			viewport->moveViewport((int)floor(viewportVx + 0.5f), (int)floor(viewportVy + 0.5f), game->getGSM()->getWorld()->getWorldWidth(), game->getGSM()->getWorld()->getWorldHeight());		
	}

	// 0X43 is HEX FOR THE 'C' VIRTUAL KEY
	// THIS CHANGES THE CURSOR IMAGE
	if ((input->isKeyDownForFirstTime(C_KEY))
		&& input->isKeyDown(VK_SHIFT))
	{
		Cursor *cursor = game->getGUI()->getCursor();
		unsigned int id = cursor->getActiveCursorID();
		id++;
		if (id == cursor->getNumCursorIDs())
			id = 0;		
		cursor->setActiveCursorID(id);
	}

	//LET'S ADD 10 ENEMIES IF THE USER PRESSED TO '+'  KEY
	if (input->isKeyDownForFirstTime(VK_ADD))
	{
		int worldHeight = game->getGSM()->getWorld()->getWorldHeight();
		int worldWidth = game->getGSM()->getWorld()->getWorldWidth();
		for (int b = 10; b > 0; b--)
		{
			Physics *physics = game->getGSM()->getPhysics();
			RandomJumpingBot *bot = new RandomJumpingBot(physics, 30, 120, 40);
			physics->addCollidableObject(bot);
			PhysicalProperties *pp = bot->getPhysicalProperties();
			pp->setPosition((rand() % worldWidth),(rand() % worldHeight));
			pp->setVelocity(((((float)rand()) / RAND_MAX * 20 - 10.0) *.01f), ((((float)rand()) / RAND_MAX * 20 - 10.0) *.01f));
			bot->setSpriteType(enemySpriteType);
			bot->setCurrentState(IDLE);
			bot->setAlpha(255);
			spriteManager->addBot(bot);
			bot->affixTightAABBBoundingVolume();
		}
	}

	//LET'S REMOVE 10 ENEMIES IF THE USER PRESSED TO '-'  KEY
	if (input->isKeyDownForFirstTime(VK_SUBTRACT))
	{
		int numberOfSprites = spriteManager->getNumberOfSprites();
		if (numberOfSprites >= 10)
		{
			for (int b = 10; b > 0; b--)
			{
				Bot *bot = spriteManager->getBotAtFront();
				spriteManager->removeBot(bot);
			}
		}
	}

	// LET'S MESS WITH THE TARGET FRAME RATE IF THE USER PRESSES THE HOME OR END KEYS
	WindowsTimer *timer = (WindowsTimer*)game->getTimer();
	int fps = timer->getTargetFPS();

	// THIS SPEEDS UP OUR GAME LOOP AND THUS THE GAME, NOTE THAT WE COULD ALTERNATIVELY SCALE
	// DOWN THE GAME LOGIC (LIKE ALL VELOCITIES) AS WE SPEED UP THE GAME. THAT COULD PROVIDE
	// A BETTER PLAYER EXPERIENCE
	if (input->isKeyDown(VK_HOME) && (fps < MAX_FPS))
		timer->setTargetFPS(fps + FPS_INC);

	// THIS SLOWS DOWN OUR GAME LOOP, BUT WILL NOT GO BELOW 5 FRAMES PER SECOND
	else if (input->isKeyDown(VK_END) && (fps > MIN_FPS))
		timer->setTargetFPS(fps - FPS_INC);
}