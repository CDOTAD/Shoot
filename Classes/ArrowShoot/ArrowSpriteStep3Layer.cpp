#include"ArrowSpriteStep3Layer.h"

bool ArrowSpriteStep3Layer::init()
{
	if (!ArrowSpriteLayer::create())
	{
		return false;
	}

	this->ARROWNUMBER = 6;

	setArroSprite(this);

	setListener(this);
	setLabel(this);

	scheduleUpdate();
	return true;
}