#include "HeroSprite.h"

HeroSprite::HeroSprite()
{
}

HeroSprite::~HeroSprite()
{
}



Sprite * HeroSprite::getSprite()
{
	return _sprite;
}

void HeroSprite::setPosition(float x, float y)
{
	_sprite->setPosition(x, y);

	
}

const Vec2 & HeroSprite::getPosition() const
{
	return _sprite->getPosition();
	
}

void HeroSprite::bingSprite(Sprite * sprite)
{
	_sprite = sprite;
	addChild(_sprite);
}
