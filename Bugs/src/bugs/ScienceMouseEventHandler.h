#pragma once

#include "sssf\game\Game.h"
#include "sssf\input\MouseEventHandler.h"

class ScienceMouseEventHandler : public MouseEventHandler
{
public:
	ScienceMouseEventHandler() {}
	~ScienceMouseEventHandler() {}
	void handleMousePressEvent(Game *game, int mouseX, int mouseY);
	void handleMouseMoveEvent(Game *game, int mouseX, int mouseY);
};