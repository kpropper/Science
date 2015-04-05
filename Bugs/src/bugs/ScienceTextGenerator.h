/*	
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	ScienceTextGenerator.h

	This class is a custom text generator for the EmptyGame
	application. Basically, by defining the initText and updateText
	methods, we can have it display whatever text we like.
*/

#pragma once
#include "bugs_VS\stdafx.h"
#include "sssf\text\TextGenerator.h"

class ScienceTextGenerator : public TextGenerator
{
private:
	// THIS IS THE TEXT THIS OBJECT WILL UPDATE EACH FRAME
	wstring textToGenerate;
	wstring pathfindingText;
	wstring enemyLocationText;

public:
	// NOTHING TO INITIALIZE OR DESTROY
	ScienceTextGenerator()	{}
	~ScienceTextGenerator()	{}

	// DEFINED IN ScienceTextGenerator.cpp
	void appendMouseCoords(Game *game);
	void appendEnemyLocation(Game *game);
	void appendAntRotationInfo(Game *game);
	void appendPathfindingText(Game *game);
	void initText(Game *game);
	void updateText(Game *game);
};