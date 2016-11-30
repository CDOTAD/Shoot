#include "ArrowSpriteStep2Layer.h"

bool ArrowSpriteStep2Layer::init()
{
	if (!ArrowSpriteLayer::create())
	{
		return false;
	}

	this->ARROWNUMBER = 7;

	setArroSprite(this);

	setListener(this);
	setLabel(this);

	scheduleUpdate();
	return true;
}
