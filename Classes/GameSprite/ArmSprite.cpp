#include "ArmSprite.h"

ArmSprite::ArmSprite()
{
}

ArmSprite::ArmSprite(Sprite * sprite)
{
}

ArmSprite::~ArmSprite()
{
}

void ArmSprite::setRotation(float rotation)
{
	getSprite()->setRotation(rotation);
}
