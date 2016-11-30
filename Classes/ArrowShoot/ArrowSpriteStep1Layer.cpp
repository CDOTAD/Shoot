#include "ArrowSpriteStep1Layer.h"

bool ArrowSpriteStep1Layer::init()
{
	
	if (!ArrowSpriteLayer::create())
	{
		return false;
	}

	this->ARROWNUMBER = 10;

	setArroSprite(this);

	setListener(this);
	setLabel(this);

	scheduleUpdate();
	return true;
	
}
