#include "sssf_VS\stdafx.h"
#include "sssf\gsm\sprite\TopDownSprite.h"

void TopDownSprite::updateSprite()
{
	// CALL THE PARENT METHOD TO UPDATE ANIMATION
	AnimatedSprite::updateSprite();


	//SPRITE ROTATION IS NOT USED IN THIS GAME, UNCOMMENT THIS TO INCLUDE SPRITE ROTATION

	/*
	// AND NOW CALCULATE THE RADIANS
	// FOR RENDERING THIS SPRITE
	float vX = pp.getVelocityX();
	float vY = pp.getVelocityY();
	float epsilon = 0.00001f;

	// IF THE Y VELOCITY IS 0 WE HAVE TO BE CAREFUL DIVIDING
	if (fabs(vY) < epsilon)
	{
		// IF X ISN'T MOVING EITHER, LEAVE IT WHAT IT IS
		// AND PUT IT INTO AN IDLE STATE
		if (fabs(vX) > epsilon)
		{
			if (vX < 0.0f)
			{
				rotationInRadians = PI;
			}
			else
				rotationInRadians = 0.0f;
		}
	}
	else
	{
		float tanTheta = vY/vX;
		rotationInRadians = atan(tanTheta);
		if (vX < 0.0f)
		{
			if (vY < 0.0f)
				rotationInRadians += PI;
			else
				rotationInRadians -= PI;
		}
	} */

	rotationInRadians = 0.0f;
}