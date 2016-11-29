#include "ArrowSprite.h"

ArrowSprite::ArrowSprite()
{
	this->_sprite = Sprite::createWithSpriteFrameName("Arrow.png");
	//this->_physicsBody = PhysicsBody::createBox(this->getContentSize());
	
	
}

ArrowSprite::~ArrowSprite()
{
}

bool ArrowSprite::isFly()
{
	return _isFly;
}

void ArrowSprite::setPhysicsBody()
{
	this->_physicsBody = PhysicsBody::createBox(this->getContentSize());
	this->_physicsBody->setGravityEnable(false);
	this->_physicsBody->setCategoryBitmask(1);
	this->_physicsBody->setCollisionBitmask(-1);
	this->_physicsBody->setMass(100);
	this->_sprite->setPhysicsBody(this->_physicsBody);
}

Action * ArrowSprite::runAction(Action * action)
{
	return this->_sprite->runAction(action);
}

void ArrowSprite::onContact()
{
	this->_physicsBody->removeFromWorld();
	this->_sprite->setVisible(false);
}

Vec2 ArrowSprite::getSpeed()
{
	return _speed;
}

PhysicsBody * ArrowSprite::getPhysicsBody()
{
	return this->_physicsBody;
}
