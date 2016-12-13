#include "ArrowSpriteStep2Layer.h"

bool ArrowSpriteStep2Layer::init()
{
	if (!ArrowSpriteLayer::create())
	{
		return false;
	}

	this->ARROWNUMBER = STEP_TWO_ARROW;

	setArroSprite();

	setListener();
	setLabel();

	scheduleUpdate();
	return true;
}
