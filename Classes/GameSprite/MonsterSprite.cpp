#include "MonsterSprite.h"

MonsterSprite::MonsterSprite()
{
	this->_sprite = Sprite::createWithSpriteFrameName("Monster.png");
	/*this->_physicsBody = PhysicsBody::createBox(this->getContentSize());
	this->setPhysicsBody();*/
}

MonsterSprite::~MonsterSprite()
{
}

Action * MonsterSprite::runAction(Action * action)
{
	return this->_sprite->runAction(action);
}

void MonsterSprite::onContact()
{
	this->_physicsBody->removeFromWorld();
	this->_sprite->setVisible(false);
}

PhysicsBody * MonsterSprite::getPhysicsBody()
{
	return _physicsBody;
}

void MonsterSprite::setPhysicsBody()
{
	this->_physicsBody = PhysicsBody::createBox(this->getContentSize());
	this->_physicsBody->setGravityEnable(false);
	this->_physicsBody->setCategoryBitmask(1);
	this->_physicsBody->setCollisionBitmask(-1);
	this->_physicsBody->setMass(100);
	this->_sprite->setPhysicsBody(this->_physicsBody);
}
