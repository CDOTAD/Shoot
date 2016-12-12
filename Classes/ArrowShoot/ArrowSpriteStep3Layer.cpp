#include"ArrowSpriteStep3Layer.h"

bool ArrowSpriteStep3Layer::init()
{
	if (!ArrowSpriteLayer::create())
	{
		return false;
	}

	this->ARROWNUMBER = STEP_THREE_ARROW;

	setArroSprite();

	setListener();
	setLabel();

	scheduleUpdate();
	return true;
}