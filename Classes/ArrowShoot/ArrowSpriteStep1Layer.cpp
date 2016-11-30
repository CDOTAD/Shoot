#include "ArrowSpriteStep1Layer.h"

bool ArrowSpriteStep1Layer::init()
{
	
	if (!ArrowSpriteLayer::create())
	{
		return false;
	}

	this->ARROWNUMBER = STEP_ONE_ARROW;

	setArroSprite();

	setListener();
	setLabel();

	scheduleUpdate();
	return true;
	
}
