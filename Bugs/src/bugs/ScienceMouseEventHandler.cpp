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

		// NOW LET'S SEE IF THERE IS A SPRITE THERE
		GameStateManager *gsm = game->getGSM();
		SpriteManager *spriteManager = gsm->getSpriteManager();

		
		// IF THERE IS NO SELECTED SPRITE LOOK FOR ONE
		if (!(spriteManager->getIsSpriteSelected()))
		{
			// IF THIS DOES NOT RETURN NULL THEN YOU FOUND A SPRITE AT THAT LOCATION
			if((spriteManager->getSpriteAt(worldCoordinateX, worldCoordinateY) != NULL))
			{
				AnimatedSprite *selected = spriteManager->getSpriteAt(worldCoordinateX, worldCoordinateY);
				spriteManager->setIsSpriteSelected(true);
			}
		}
		else if (spriteManager->getSelectedSprite() != NULL)
		{
			// MOVE A SPRITE IN A DESIRED DIRECTION 
			AnimatedSprite *selected = spriteManager->getSelectedSprite();
			PhysicalProperties *pp = selected->getPhysicalProperties();
			float spriteX = pp->getX();
			float spriteY = pp->getY();

			//IF A SPRITE IS WHERE YOU WANT IT THEN STOP IT
			if (((spriteX > worldCoordinateX - 64) && (spriteX < worldCoordinateX + 64)) && (spriteY > worldCoordinateY - 64) && (spriteY < worldCoordinateY + 64))
			{
				pp->setVelocity(0, 0);
			}
			else
			{
				float deltaX = worldCoordinateX - spriteX;
				float deltaY = worldCoordinateY - spriteY;
				float hyp = sqrtf((deltaX * deltaX) + (deltaY * deltaY));

				pp->setVelocity((deltaX / hyp) * 3, (deltaY / hyp) * 3);
			}
			spriteManager->setIsSpriteSelected(false);

		//	GridPathfinder *pathfinder = spriteManager->getPathfinder();
		//	pathfinder->mapPath(selected, (float)worldCoordinateX, (float)worldCoordinateY);
		//	gsm->setSpriteSelected(false, selected);
		}
		else
		{
			spriteManager->setIsSpriteSelected(false);
		}
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