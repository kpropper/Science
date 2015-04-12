/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	SpriteManager.cpp

	See SpriteManager.h for a class description.
*/

#pragma once
#include "sssf_VS\stdafx.h"
#include "sssf\gsm\ai\Bot.h"
#include "sssf\gsm\physics\PhysicalProperties.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gsm\sprite\AnimatedSpriteType.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\state\GameStateManager.h"

list<Bot*> quadtree[22];
int gameWorldWidth = 0;
int gameWorldHeight = 0;
int spritesInScene = 0;


/*
	addSpriteToRenderList - This method checks to see if the sprite
	parameter is inside the viewport. If it is, a RenderItem is generated
	for that sprite and it is added to the render list.
*/
void SpriteManager::addSpriteToRenderList(AnimatedSprite *sprite,
										  RenderList *renderList,
										  Viewport *viewport)
{
	// GET THE SPRITE TYPE INFO FOR THIS SPRITE
	AnimatedSpriteType *spriteType = sprite->getSpriteType();
	PhysicalProperties *pp = sprite->getPhysicalProperties();
	float rotation = sprite->getRotationInRadians();

	// IS THE SPRITE VIEWABLE?
	if (viewport->areWorldCoordinatesInViewport(	
									pp->getX(),
									pp->getY(),
									spriteType->getTextureWidth(),
									spriteType->getTextureHeight()))
	{
		// SINCE IT'S VIEWABLE, ADD IT TO THE RENDER LIST
		RenderItem itemToAdd;
		itemToAdd.id = sprite->getFrameIndex();
		renderList->addRenderItem(	sprite->getCurrentImageID(),
									pp->round(pp->getX()-viewport->getViewportX()),
									pp->round(pp->getY()-viewport->getViewportY()),
									pp->round(pp->getZ()),
									sprite->getAlpha(),
									spriteType->getTextureWidth(),
									spriteType->getTextureHeight(),
									rotation);

		spritesInScene++;
	}
}

int SpriteManager::getSpritesinScene()
{
	return spritesInScene;
}

/*
	addSpriteItemsToRenderList - This method goes through all of the sprites,
	including the player sprite, and adds the visible ones to the render list.
	This method should be called each frame.
*/
void SpriteManager::addSpriteItemsToRenderList(	Game *game)
{
	GameStateManager *gsm = game->getGSM();
	GameGUI *gui = game->getGUI();
	if (gsm->isWorldRenderable())
	{
		GameGraphics *graphics = game->getGraphics();
		RenderList *renderList = graphics->getWorldRenderList();
		Viewport *viewport = gui->getViewport();

		// ADD THE PLAYER SPRITE
		addSpriteToRenderList(&player, renderList, viewport);
		spritesInScene = 0;
		// NOW ADD THE REST OF THE SPRITES
		list<Bot*>::iterator botIterator;
		botIterator = bots.begin();
		while (botIterator != bots.end())
		{			
			Bot *bot = (*botIterator);
			addSpriteToRenderList(bot, renderList, viewport);
			botIterator++;
		}
	}
}


/*
	addSprite - This method is for adding a new sprite to 
	this sprite manager. Once a sprite is added it can be 
	scheduled for rendering.
*/
void SpriteManager::addBot(Bot *botToAdd)
{
	bots.push_back(botToAdd);
}

/*
	addSpriteType - This method is for adding a new sprite
	type. Note that one sprite type can have many sprites. For
	example, we may say that there may be a "Bunny" type of
	sprite, and specify properties for that type. Then there might
	be 100 different Bunnies each with their own properties, but that
	share many things in common according to what is defined in
	the shared sprite type object.
*/
unsigned int SpriteManager::addSpriteType(AnimatedSpriteType *spriteTypeToAdd)
{
	spriteTypes.push_back(spriteTypeToAdd);
	return spriteTypes.size()-1;
}

/*
	clearSprites - This empties all of the sprites and sprite types.
*/
void SpriteManager::clearSprites()
{
	//spriteTypes.clear();
	//bots.clear();
}

/*
	getSpriteType - This gets the sprite type object that corresponds
	to the index argument.
*/
AnimatedSpriteType* SpriteManager::getSpriteType(unsigned int typeIndex)
{
	if (typeIndex < spriteTypes.size())
		return spriteTypes.at(typeIndex);
	else
		return NULL;
}

/*
	unloadSprites - This method removes all artwork from memory that
	has been allocated for game sprites.
*/
void SpriteManager::unloadSprites()
{
	// @TODO - WE'LL DO THIS LATER WHEN WE LEARN MORE ABOUT MEMORY MANAGEMENT
	/*list<Bot*>::iterator botsIt = bots.begin();
	while (botsIt != bots.end())
	{
		list<Bot*>::iterator tempIt = botsIt;
		botsIt++;
		Bot *botToDelete = (*tempIt);
		delete botToDelete;
	}
	bots.clear();

	vector<AnimatedSpriteType*>::iterator spriteTypesIt = spriteTypes.begin();
	while (spriteTypesIt != spriteTypes.end())
	{
		vector<AnimatedSpriteType*>::iterator tempIt = spriteTypesIt;
		spriteTypesIt++;
		AnimatedSpriteType *astToDelete = (*tempIt);
		delete astToDelete;
	}
	spriteTypes.clear();

	// DELETE THE PATHFINDER IF THERE IS ONE
	if (pathfinder != NULL)
		delete pathfinder;
		*/
}
Bot* SpriteManager::removeBot(Bot *botToRemove)
{
	bots.remove(botToRemove);
	return botToRemove;
	// @TODO - WE'LL DO THIS LATER WHEN WE LEARN MORE ABOUT MEMORY MANAGEMENT
}


/*
	update - This method should be called once per frame. It
	goes through all of the sprites, including the player, and calls their
	update method such that they may update themselves.
*/
void SpriteManager::update(Game *game)
{
	//UPDATE GAME WORLD SIZE
	gameWorldWidth = game->getGSM()->getWorld()->getWorldWidth();
	gameWorldHeight = game->getGSM()->getWorld()->getWorldHeight();
	

	// CLEAR THE QUADTREE
	//	for (int cl = 0; cl > 21; cl++)
	//	{
	quadtree[0].clear();
	quadtree[1].clear();
	quadtree[2].clear();
	quadtree[3].clear();
	quadtree[4].clear();
	quadtree[5].clear();
	quadtree[6].clear();
	quadtree[7].clear();
	quadtree[8].clear();
	quadtree[9].clear();
	quadtree[10].clear();
	quadtree[11].clear();
	quadtree[12].clear();
	quadtree[13].clear();
	quadtree[14].clear();
	quadtree[15].clear();
	quadtree[16].clear();
	quadtree[17].clear();
	quadtree[18].clear();
	quadtree[19].clear();
	quadtree[20].clear();
	quadtree[21].clear();
//	}


	// FIRST LET'S DO THE NECESSARY PATHFINDING
	pathfinder->updatePath(&player);
	list<Bot*>::iterator botIterator;
	botIterator = bots.begin();
	while (botIterator != bots.end())
	{
		Bot *bot = (*botIterator);
		updateQuadtree(bot);
		pathfinder->updatePath(bot);
		botIterator++;
	}

	// THEN UPDATE THE PLAYER SPRITE ANIMATION FRAME/STATE/ROTATION
	player.updateSprite();

	// NOW UPDATE THE REST OF THE SPRITES ANIMATION FRAMES/STATES/ROTATIONS
	botIterator = bots.begin();
	while (botIterator != bots.end())
	{
		Bot *bot = (*botIterator);
		bot->think(game);
		bot->updateSprite();
		botIterator++;
	}
}

void SpriteManager::updateQuadtree(Bot *botToAdd)
{
	float lx = botToAdd->getBoundingVolume()->getLeft();
	float rx = botToAdd->getBoundingVolume()->getRight();
	float ty = botToAdd->getBoundingVolume()->getTop();
	float by = botToAdd->getBoundingVolume()->getBottom();
	float quarterHeight = (gameWorldHeight / 4);
	float halfHeight = (gameWorldHeight / 2);
	float threeQuarterHeight = ((3 * gameWorldHeight) / 4);
	float quarterWidth = (gameWorldWidth / 4);
	float halfWidth = (gameWorldWidth / 2);
	float threeQuarterWidth = ((3 * gameWorldWidth) / 4);

	if ((lx <= halfWidth) && (rx >= halfWidth) && (ty <= halfHeight) && (by >= halfHeight))
		quadtree[0].push_back(botToAdd);
	else if ((lx <= quarterWidth) && (rx >= quarterWidth) && (ty <= quarterHeight) && (by >= quarterHeight))
		quadtree[1].push_back(botToAdd);
	else if ((lx <= threeQuarterWidth) && (rx >= threeQuarterWidth) && (ty <= quarterHeight) && (by >= quarterHeight))
		quadtree[2].push_back(botToAdd);
	else if ((lx <= quarterWidth) && (rx >= quarterWidth) && (ty <= threeQuarterHeight) && (by >= threeQuarterHeight))
		quadtree[3].push_back(botToAdd);
	else if ((lx <= threeQuarterWidth) && (rx >= threeQuarterWidth) && (ty <= threeQuarterHeight) && (by >= threeQuarterHeight))
		quadtree[4].push_back(botToAdd);
	else if ((rx < (gameWorldWidth) / 4) && (by < quarterHeight))
		quadtree[5].push_back(botToAdd);
	else if ((lx > quarterWidth) && (rx < halfHeight) && (by < quarterHeight))
		quadtree[6].push_back(botToAdd);
	else if ((rx < quarterWidth) && (ty > quarterHeight) && (by < halfHeight))
		quadtree[7].push_back(botToAdd);
	else if ((lx > quarterWidth) && (rx < halfWidth) && (ty > quarterHeight) && (by < halfHeight))
		quadtree[8].push_back(botToAdd);
	else if ((lx > gameWorldWidth / 2) && (rx < threeQuarterWidth) && (by < quarterHeight))
		quadtree[9].push_back(botToAdd);
	else if ((lx > threeQuarterWidth) && (by < quarterHeight))
		quadtree[10].push_back(botToAdd);
	else if ((lx > halfWidth) && (rx < threeQuarterWidth) && (ty > quarterHeight) && (by < halfHeight))
		quadtree[11].push_back(botToAdd);
	else if ((lx > threeQuarterWidth) && (ty > quarterHeight) && (by < halfHeight))
		quadtree[12].push_back(botToAdd);
	else if ((rx < quarterWidth) && (ty > halfHeight) && (by < threeQuarterHeight))
		quadtree[13].push_back(botToAdd);
	else if ((lx >quarterWidth) && (rx < halfWidth) && (ty >halfHeight) && (by < threeQuarterHeight))
		quadtree[14].push_back(botToAdd);
	else if ((rx < quarterWidth) && (ty > threeQuarterHeight))
		quadtree[15].push_back(botToAdd);
	else if ((lx > quarterWidth) && (rx < halfWidth) && (ty > threeQuarterHeight))
		quadtree[16].push_back(botToAdd);
	else if ((lx > halfWidth) && (rx < threeQuarterWidth) && (ty > halfHeight) && (by < threeQuarterHeight))
		quadtree[17].push_back(botToAdd);
	else if ((lx > threeQuarterWidth) && (ty > halfHeight) && (by < threeQuarterHeight))
		quadtree[18].push_back(botToAdd);
	else if ((lx > halfWidth) && (rx < threeQuarterWidth) && (ty > threeQuarterHeight))
		quadtree[19].push_back(botToAdd);
	else if ((lx > threeQuarterWidth) && (ty > threeQuarterHeight))
		quadtree[20].push_back(botToAdd);
	else
		quadtree[21].push_back(botToAdd);
}

int SpriteManager::getNumberOfBotsInNode(int index)
{
	return quadtree[index].size();
}

AnimatedSprite* SpriteManager::getSpriteAt(int x, int y)
{
	int botX;
	int botXW;
	int botY;
	int botYH;
	list<Bot*>::iterator botIterator;
	botIterator = bots.begin();
	while (botIterator != bots.end())
	{
		Bot *bot = (*botIterator);
		botX = bot->getBoundingVolume()->getLeft();
		botY = bot->getBoundingVolume()->getTop();
		botXW = bot->getBoundingVolume()->getRight();
		botYH = bot->getBoundingVolume()->getBottom();
		if (((x > botX) && (x < botXW)) && ((y > botY) && (y > botYH)))
		{
			AnimatedSprite *selected = bot;
			return selected;
		}
		botIterator++;

		return NULL;
	}
}

AnimatedSprite* SpriteManager::getSelectedSprite()
{

	list<Bot*>::iterator botIterator;
	botIterator = bots.begin();
	while (botIterator != bots.end())
	{
		Bot *bot = (*botIterator);
		if (bot->getIsSelected())
		{
			AnimatedSprite *selected = bot;
			return selected;
		}
		botIterator++;

		return NULL;
	}
}


