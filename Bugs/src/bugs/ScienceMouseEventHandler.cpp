#include "bugs_VS\stdafx.h"
#include "bugs\ScienceMouseEventHandler.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\sprite\SpriteManager.h"
#include "sssf\gsm\sprite\TopDownSprite.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"
#include "sssf\gui\Viewport.h"

void ScienceMouseEventHandler::handleMousePressEvent(Game *game, int mouseX, int mouseY)
{
	if (game->getGSM()->isGameInProgress())
	{
		Viewport *viewport = game->getGUI()->getViewport();
		
		// DETERMINE WHERE ON THE MAP WE HAVE CLICKED
		int worldCoordinateX = mouseX + viewport->getViewportX();
		int worldCoordinateY = mouseY + viewport->getViewportY();

		// NOW LET'S SEND THE PLAYER THERE
		GameStateManager *gsm = game->getGSM();
		SpriteManager *spriteManager = gsm->getSpriteManager();
		if (!(gsm->getIsSpriteSelected()))
		{
			if((spriteManager->getSpriteAt(worldCoordinateX, worldCoordinateY) != NULL))
			{
				AnimatedSprite *selected = spriteManager->getSpriteAt(worldCoordinateX, worldCoordinateY);
				gsm->setSpriteSelected(true, selected);
			}
		}
		else if (spriteManager->getSelectedSprite() != NULL)
		{
			AnimatedSprite *selected = spriteManager->getSelectedSprite();
			GridPathfinder *pathfinder = spriteManager->getPathfinder();
			pathfinder->mapPath(selected, (float)worldCoordinateX, (float)worldCoordinateY);
			gsm->setSpriteSelected(false, selected);
		}
	//	TopDownSprite *player = spriteManager->getPlayer();
	//	GridPathfinder *pathfinder = spriteManager->getPathfinder();
	//	pathfinder->mapPath(player, (float)worldCoordinateX, (float)worldCoordinateY);
	}
}

void ScienceMouseEventHandler::handleMouseMoveEvent(Game *game, int mouseX, int mouseY)
{
	// DETERMINE WHAT THE PATHFINDING GRID CELL
	// IS THAT THE MOUSE CURRENTLY IS ABOVE
	if (game->getGSM()->isGameInProgress())
	{
		// IF YOU LIKE YOU COULD DO SOME MOUSE OVER DEBUGGING STUFF HERE
	}
}