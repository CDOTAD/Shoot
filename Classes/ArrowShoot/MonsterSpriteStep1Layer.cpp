#include "MonsterSpriteStep1Layer.h"

bool MonsterSpriteStep1Layer::init()
{
		if (!Layer::create()){
			return false;
		}
	
		auto origin = Director::getInstance()->getVisibleOrigin();
		auto visibleSize = Director::getInstance()->getVisibleSize();
	
		this->_vecMonsterSprite = new ConcreteAggregate<Sprite*>(MONSTER_NUM);

		/*将怪物精灵装进容器*/
		this->addMonster();

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
