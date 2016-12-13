#include "MonsterSpriteStep2Layer.h"


bool MonsterSpriteStep2Layer::init()
{
	if (!Layer::create()) {
		return false;
	}

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//addMonster();
	this->_vecMonsterSprite = new ConcreteAggregate<Sprite*>(MONSTER_NUM);

	/*将怪物精灵装进容器*/
	this->addMonster();
	for (int i = 1; i <= MONSTER_NUM; i++) {
		
		Sprite* monsterSprite = this->_vecMonsterSprite->Pop(i - 1);

		auto moveBy1 = MoveBy::create(timerand(i), Vec2(64, monsterSprite->getPositionY()));
		auto moveBy2 = MoveBy::create(1.5*timerand(i), Vec2(-128, monsterSprite->getPositionY()));
		auto moveBy3 = MoveBy::create(timerand(i), Vec2(64, monsterSprite->getPositionY()));
		auto moveSeq = Sequence::create(moveBy1, moveBy2, moveBy3, NULL);
		monsterSprite->runAction(RepeatForever::create(moveSeq));
		

		
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
