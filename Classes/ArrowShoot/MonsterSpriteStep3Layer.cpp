#include "MonsterSpriteStep3Layer.h"



bool MonsterSpriteStep3Layer::init()
{
	if (!Layer::create()) {
		return false;
	}

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	this->_vecMonsterSprite = new ConcreteAggregate<Sprite*>(MONSTER_NUM);
	/*将怪物精灵装进容器*/
	this->addMonster();
	for (int i = 1; i <= MONSTER_NUM; i++) {
		Sprite* monsterSprite = this->_vecMonsterSprite->Pop(i - 1);
		switch (i)
		{
		case 1:{
					auto moveBy1 = MoveBy::create(0.1, Vec2(monsterSprite->getPositionX(), 16));
					auto moveBy2 = MoveBy::create(0.3, Vec2(monsterSprite->getPositionX(), 16));
					auto moveBy3 = MoveBy::create(0.5, Vec2(monsterSprite->getPositionX(), 32));
					auto moveBy4 = MoveBy::create(0.5, Vec2(monsterSprite->getPositionX(), -32));
					auto moveBy5 = MoveBy::create(0.3, Vec2(monsterSprite->getPositionX(), -16));
					auto moveBy6 = MoveBy::create(0.1, Vec2(monsterSprite->getPositionX(), -16));
					auto moveSeq = Sequence::create(moveBy1, moveBy2, moveBy3, moveBy4, moveBy5, moveBy6, NULL);
					monsterSprite->runAction(RepeatForever::create(moveSeq));
		}break;
		case 2:{
					auto moveBy1 = MoveBy::create(timerand(i), Vec2(64, monsterSprite->getPositionY()));
					auto moveBy2 = MoveBy::create(1.5*timerand(i), Vec2(-128, monsterSprite->getPositionY()));
					auto moveBy3 = MoveBy::create(timerand(i), Vec2(64, monsterSprite->getPositionY()));
					auto moveSeq = Sequence::create(moveBy1, moveBy2, moveBy3, NULL);
					monsterSprite->runAction(RepeatForever::create(moveSeq));
		}break;
		case 3:{
					auto moveBy1 = MoveBy::create(timerand(i), Vec2(64, monsterSprite->getPositionY()));
					auto moveBy2 = MoveBy::create(1.5*timerand(i), Vec2(-128, monsterSprite->getPositionY()));
					auto moveBy3 = MoveBy::create(timerand(i), Vec2(64, monsterSprite->getPositionY()));
					auto moveSeq = Sequence::create(moveBy1, moveBy2, moveBy3, NULL);
					monsterSprite->runAction(RepeatForever::create(moveSeq));
		}break;
		case 4:{
					auto moveBy1 = MoveBy::create(0.05, Vec2(monsterSprite->getPositionX(), 16));
					auto moveBy2 = MoveBy::create(0.1, Vec2(monsterSprite->getPositionX(), 16));
					auto moveBy3 = MoveBy::create(0.2, Vec2(monsterSprite->getPositionX(), 32));
					auto moveBy4 = MoveBy::create(0.3, Vec2(monsterSprite->getPositionX(), 64));
					auto moveBy5 = MoveBy::create(0.3, Vec2(monsterSprite->getPositionX(), -64));
					auto moveBy6 = MoveBy::create(0.5, Vec2(monsterSprite->getPositionX(), -32));
					auto moveBy7 = MoveBy::create(0.3, Vec2(monsterSprite->getPositionX(), -16));
					auto moveBy8 = MoveBy::create(0.1, Vec2(monsterSprite->getPositionX(), -16));
					auto moveSeq = Sequence::create(moveBy1, moveBy2, moveBy3, moveBy4, moveBy5, moveBy6,moveBy7,moveBy8, NULL);
					monsterSprite->runAction(RepeatForever::create(moveSeq));

					   
		}
		default:
			break;
		}

	}
	/*设置怪物计数图标*/
	Sprite* monsterIcon = Sprite::createWithSpriteFrameName("icon.png");
	monsterIcon->setPosition(visibleSize.width - 100, visibleSize.height - 25);
	this->addChild(monsterIcon, 1);

	this->labelMonsterNumLeft = LabelTTF::create("4", "Brush Script MT", 32);
	labelMonsterNumLeft->setColor(Color3B(225, 225, 225));
	labelMonsterNumLeft->setPosition(visibleSize.width - 25, visibleSize.height - 25);
	this->addChild(labelMonsterNumLeft, 1);

	scheduleUpdate();
	return true;
}
