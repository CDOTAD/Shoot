#include "HeroSprite.h"

HeroSprite::HeroSprite()
{
}

HeroSprite::~HeroSprite()
{
}


void HeroSprite::setPosition(float x, float y)
{
	_sprite->setPosition(x, y);

	
}

const Vec2 & HeroSprite::getPosition() const
{
	return _sprite->getPosition();
	
}

PhysicsBody * HeroSprite::getPhysicsBody()
{
	return _physicsBody;
}

void HeroSprite::setTag(int tag)
{
	_sprite->setTag(tag);
}

void HeroSprite::setVisible(bool visible)
{
	_sprite->setVisible(visible);
}

Size HeroSprite::getContentSize()
{
	return _sprite->getContentSize();
}

void HeroSprite::setPhysicsBody()
{
	this->_physicsBody = NULL;
}

void HeroSprite::bingSprite(Sprite * sprite)
{
	_sprite = sprite;
	addChild(_sprite);
}
