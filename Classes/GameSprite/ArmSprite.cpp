#include "ArmSprite.h"

ArmSprite::ArmSprite()
{
}

ArmSprite::ArmSprite(Sprite * sprite)
{
	this->_sprite = sprite;
}

ArmSprite::~ArmSprite()
{
}

void ArmSprite::setRotation(float rotation)
{
	getSprite()->setRotation(rotation);
}
