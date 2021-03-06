#include "GameLayer.h"
#include"FailLayer.h"


void GameLayer::onResume(Layer * objcet)
{
	_flagPressed = false;
	this->_arrowLayer->myResume();

	if (this->_arrowLayer->isflying) 
	{
		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setVelocity(_speed);
		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setGravityEnable(TRUE);
	}
	this->removeChild(objcet, true);

	Director::getInstance()->resume();
}

void GameLayer::deleteBurning(float dt)
{
	this->_burningBatch->setVisible(false);
	this->_flagBurning= false;
}

void GameLayer::menuExitCallBack(cocos2d::Ref * pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

bool GameLayer::isPause()
{
	return _flagPressed;
}

void GameLayer::setMap(MapLayer * mapLayer)
{
	this->_mapLayer = mapLayer;

	this->addChild(_mapLayer, 1);
}

void GameLayer::setCommonPart()
{
	Director* dir = Director::getInstance();
	Size visibleSize = dir->getVisibleSize();
	/*创建退出按钮*/
	auto exitButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("exit.png"),
		Sprite::createWithSpriteFrameName("exitOn.png"),
		CC_CALLBACK_1(GameLayer::menuExitCallBack, this));
	exitButton->setScale(0.4);

	auto menu = Menu::create(exitButton, NULL);
	menu->setPosition(visibleSize.width*0.9, 32);
	this->addChild(menu, 2);

	/*加载弓*/

	this->_arch = Sprite::createWithSpriteFrameName("arch.png");
	ValueMap archPointMap = this->_mapLayer->getObjectGroup()->getObject("Heros");
	float archX = archPointMap.at("x").asFloat();
	float archY = archPointMap.at("y").asFloat();
	this->_arch->setPosition(archX + 20, archY + 30);
	this->_arch->setScale(0.7f);
	this->addChild(_arch, 1);
}

void GameLayer::setArrowLayer(ArrowSpriteLayer * arrowLayer)
{
	this->_arrowLayer = arrowLayer;
	this->_arrowLayer->setTag(ARROW_LAYER_TAG);

	this->_arrowLayer->addObserver(this);
	this->_arrowLayer->setArrowPosition(this->_mapLayer->getObjectGroup());
	this->addChild(_arrowLayer, 2);

}

void GameLayer::setMonsterLayer(MonsterSpriteLayer * monsterLayer)
{
	this->_monsterLayer = monsterLayer;
	this->_monsterLayer->setTag(MONSTER_LAYER_TAG);
	//this->_monsterLayer->step = step;
	this->_monsterLayer->addObserver(this);
	this->_monsterLayer->setMonstersPosition(this->_mapLayer->getObjectGroup());
	this->addChild(_monsterLayer, 2);
}

void GameLayer::setHero(Sprite * myHero)
{
	this->_myHero = myHero;

	ValueMap heroPointMap = this->_mapLayer->getObjectGroup()->getObject("Heros");
	float heroX = heroPointMap.at("x").asFloat();
	float heroY = heroPointMap.at("y").asFloat();
	_myHero->setPosition(heroX + 25 - 64, heroY + 50);
	_myHero->setScale(0.1f);
	this->addChild(_myHero, 1);
}

void GameLayer::setListener()
{
	_contactListener = EventListenerPhysicsContact::create();

	_contactListener->onContactBegin = [=](PhysicsContact &contact) {
		auto nodeA = contact.getShapeA()->getBody()->getNode();
		auto nodeB = contact.getShapeB()->getBody()->getNode();
		if (nodeA&&nodeB) {
			if (nodeA->getTag() == 10) {
				
				nodeB->getPhysicsBody()->removeFromWorld();
				nodeB->setVisible(false);
			}
			else if (nodeB->getTag() == 10) {

				nodeA->getPhysicsBody()->removeFromWorld();
				nodeA->setVisible(false);
			}
			_monsterLayer->onContact();
		}


		return true;
	};

	_contactListener->onContactSeparate = [=](PhysicsContact &contact) {
		if (this->_arrowLayer->getArrowSprite())
		{
			this->_arrowLayer->getArrowSprite()->getPhysicsBody()->removeFromWorld();

			this->_arrowLayer->getArrowSprite()->setVisible(false);
			if (_monsterLayer->getMonsterNumber() > 0) {

				this->_arrowLayer->changeArrowSpriteReferTo();
				this->_arrowLayer->onContact();
				this->_arrowLayer->updateLabel();
			}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(_contactListener, this);

	auto listenerKeypad = EventListenerKeyboard::create();
	listenerKeypad->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		/*如果按ESC键创建暂停层*/
		if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
			if (this->_flagPressed == false) {
				this->_flagPressed = true;
				this->Pause();
			}

		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeypad, this);


}

void GameLayer::Pause()
{
	Director::getInstance()->pause();

	this->_arrowLayer->myPause();

	if (this->_arrowLayer->isflying == true) 
	{
		_speed = this->_arrowLayer->getArrowSprite()->getPhysicsBody()->getVelocity();
		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setVelocity(Vec2::ZERO);
		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setGravityEnable(FALSE);
	}
	//this->pauseSchedulerAndActions();
	this->_pauseLayer = PauseLayer::create();
	this->_pauseLayer->addObserver(this);
	this->addChild(_pauseLayer, 20);
}
