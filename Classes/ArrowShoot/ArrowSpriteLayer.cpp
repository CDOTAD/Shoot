#include"ArrowSpriteLayer.h"
#include<cmath>
#include"MonsterSpriteLayer.h"

#define pi 3.1415926


bool ArrowSpriteLayer::onTouchBegan(Touch* touch, Event* event)
{
	if (_arrowSprite)
	{

		/*设置时钟频率*/
		this->setTimeFrequency();
		//记录触摸事件发生时的时间
		LARGE_INTEGER startPerformanceCount;
		QueryPerformanceCounter(&startPerformanceCount);
		touchBeganTime = startPerformanceCount.QuadPart;
		/*使箭头装箱鼠标所在位置*/
		Point locationTouch = touch->getLocation();
		Point locationArrowSprite = _arrowSprite->getPosition();
		/*计算所需转过的角度*/
		float angel = atan((locationTouch.y - locationArrowSprite.y) / (locationTouch.x - locationArrowSprite.x)) * 180 / pi;
		if (this->isflying == false && this->isPause == false) 
		{
			if (locationTouch.x == locationArrowSprite.x&&locationTouch.y < locationArrowSprite.y)
			{
				float angel0 = 90;
				_arrowSprite->setRotation(angel0);

				_observer->onEventHappen(this, ArrowRotate);
				/*if (layer1 != nullptr)
				{
					layer1->arch->setRotation(angel0);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(angel0);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(angel0);
				}*/
			}
			else if (locationTouch.x == locationArrowSprite.x&&locationTouch.y > locationArrowSprite.y)
			{
				float angel0 = -90;
				_arrowSprite->setRotation(angel0);
				_observer->onEventHappen(this, ArrowRotate);
				/*if (layer1 != nullptr)
				{
					layer1->arch->setRotation(angel0);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(angel0);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(angel0);
				}*/
			}
			else if (locationTouch.x < locationArrowSprite.x&&locationTouch.y == locationArrowSprite.y)
			{
				auto rotateTo = RotateTo::create(0.1f, -180);
				_arrowSprite->runAction(rotateTo);
				_observer->onEventHappen(this, ArrowRotate);
				/*arrowSprite->setRotation(-180);
				if (layer1 != nullptr)
				{
					layer1->arch->setRotation(-180);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(-180);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(-180);
				}*/
			}
			else if (locationTouch.x > locationArrowSprite.x&&locationTouch.y == locationArrowSprite.y)
			{

			}
			else if (locationTouch.x > locationArrowSprite.x&&locationTouch.y > locationArrowSprite.y)
			{
				float angel0 = angel;
				if (angel > 0)
				{
					angel0 = -angel;
					_arrowSprite->setRotation(angel0);
				}
				if (angel < 0)
				{
					_arrowSprite->setRotation(angel0);
				}

				_observer->onEventHappen(this, ArrowRotate);

				/*if (layer1 != nullptr)
				{
					layer1->arch->setRotation(angel0);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(angel0);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(angel0);
				}*/
			}
			else if (locationTouch.x > locationArrowSprite.x&&locationTouch.y < locationArrowSprite.y)
			{
				float angel0 = angel;
				if (angel < 0)
				{
					angel0 = -angel;
					_arrowSprite->setRotation(angel0);
				}
				if (angel > 0)
				{
					_arrowSprite->setRotation(angel0);
				}

				_observer->onEventHappen(this, ArrowRotate);
				/*if (layer1 != nullptr)
				{
					layer1->arch->setRotation(angel0);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(angel0);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(angel0);
				}*/
			}
			else if (locationTouch.x<locationArrowSprite.x&&locationTouch.y>locationArrowSprite.y)
			{
				float angel0 = -180.0 - angel;
				_arrowSprite->setRotation(angel0);

				_observer->onEventHappen(this, ArrowRotate);
				/*if (layer1 != nullptr)
				{
					layer1->arch->setRotation(angel0);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(angel0);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(angel0);
				}*/
			}
			else if (locationTouch.x < locationArrowSprite.x&&locationTouch.y < locationArrowSprite.y)
			{
				float angel0 = -180.0 - angel;
				_arrowSprite->setRotation(angel0);

				_observer->onEventHappen(this, ArrowRotate);
				/*if (layer1 != nullptr)
				{
					layer1->arch->setRotation(angel0);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(angel0);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(angel0);
				}*/
			}
		}
	}
	return true;
}

void ArrowSpriteLayer::onTouchEnded(Touch* touch, Event* event)
{
	if (_arrowSprite)
	{
		/*记录触摸事件结束时的时间*/
		LARGE_INTEGER endPerformanceCount;
		QueryPerformanceCounter(&endPerformanceCount);
		touchEndedTime = endPerformanceCount.QuadPart;

		/*计算触摸事件发生到结束时的时间间隔*/
		double pressTime;
		pressTime = (touchEndedTime - touchBeganTime) / timeFrequency;

		/*设置箭的飞行角度*/
		Point locationTouch = touch->getLocation();
		Point locationArrowSprite = _arrowSprite->getPosition();
		float angel = atan((locationTouch.y - locationArrowSprite.y) / (locationTouch.x - locationArrowSprite.y)) * 180 / pi;
		float angel1 = 0;
		if (locationTouch.x == locationArrowSprite.x&&locationTouch.y < locationArrowSprite.y)
		{
			angel1 = -90.0;
		}
		else if (locationTouch.x == locationArrowSprite.x&&locationTouch.y > locationArrowSprite.y)
		{
			angel1 = 90.0;
		}
		else if (locationTouch.x < locationArrowSprite.x&&locationTouch.y == locationArrowSprite.y)
		{
			angel1 = -180;
		}
		else if (locationTouch.x > locationArrowSprite.x&&locationTouch.y == locationArrowSprite.y)
		{
			angel1 = 0;
		}
		else if (locationTouch.x > locationArrowSprite.x&&locationTouch.y > locationArrowSprite.y)
		{
			angel1 = angel;
		}
		else if (locationTouch.x > locationArrowSprite.x&&locationTouch.y < locationArrowSprite.y)
		{
			angel1 = angel;
		}
		else if (locationTouch.x<locationArrowSprite.x&&locationTouch.y>locationArrowSprite.y)
		{
			angel1 = 180.0 + angel;
		}
		else if (locationTouch.x < locationArrowSprite.x&&locationTouch.y < locationArrowSprite.y)
		{
			angel1 = 180.0 + angel;
		}
		angel1 = angel1*pi / 180;

		/*判断是否有箭在飞，如果在飞则不作出动作，如果没有则执行动作*/
		/*根据按下的时间长短给予不同的初速度*/
		if (this->isflying == false && this->isPause == false)
		{
			_arrowSprite->getPhysicsBody()->setGravityEnable(true);

			auto moveBy = MoveBy::create(1.0f, Vec2(0, 0));
			RotateBy* rotateBy;
			if (locationTouch.x > locationArrowSprite.x)
			{
				rotateBy = RotateBy::create(0.1f, 10.0);
			}
			else
			{
				rotateBy = RotateBy::create(0.1f, -10.0);
			}
			if (pressTime >= 0.1 && pressTime <= 0.2)
			{
				_arrowSprite->getPhysicsBody()->setVelocity(Vec2(300 * cos(angel1), 300 * sin(angel1)));
			}
			else if (pressTime > 0.2 && pressTime <= 0.3)
			{
				_arrowSprite->getPhysicsBody()->setVelocity(Vec2(400 * cos(angel1), 400 * sin(angel1)));
			}
			else if (pressTime > 0.3 && pressTime <= 0.4)
			{
				_arrowSprite->getPhysicsBody()->setVelocity(Vec2(500 * cos(angel1), 500 * sin(angel1)));
			}
			else if (pressTime > 0.4 && pressTime <= 0.5)
			{
				_arrowSprite->getPhysicsBody()->setVelocity(Vec2(600 * cos(angel1), 600 * sin(angel1)));
			}
			else if (pressTime > 0.6 && pressTime <= 0.7)
			{
				_arrowSprite->getPhysicsBody()->setVelocity(Vec2(700 * cos(angel1), 700 * sin(angel1)));
			}
			else if (pressTime > 0.7 && pressTime <= 0.8)
			{
				_arrowSprite->getPhysicsBody()->setVelocity(Vec2(800 * cos(angel), 800 * sin(angel)));
			}
			else
			{
				_arrowSprite->getPhysicsBody()->setVelocity(Vec2(1000 * cos(angel1), 1000 * sin(angel1)));
			}
			auto repeatforever = RepeatForever::create(rotateBy);
			repeatforever->setTag(1);
			_arrowSprite->runAction(moveBy);
			_arrowSprite->runAction(repeatforever);
			this->isflying = true;
		}
	}
}

void ArrowSpriteLayer::onTouchCancelled(Touch* touch, Event* event)
{
	return;
}

void ArrowSpriteLayer::setTimeFrequency()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	timeFrequency = (double)frequency.QuadPart;
}

void ArrowSpriteLayer::setListener()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(ArrowSpriteLayer::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(ArrowSpriteLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ArrowSpriteLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto watch = EventListenerMouse::create();

	watch->onMouseMove = CC_CALLBACK_1(ArrowSpriteLayer::onMouseMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(watch, this);
}

void ArrowSpriteLayer::setLabel()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* arrowIcon = Sprite::createWithSpriteFrameName("Arrow.png");
	arrowIcon->setPosition(48, visibleSize.height - 25);
	this->addChild(arrowIcon, 1);
	char num[20];
	sprintf(num, "%d", this->ARROWNUMBER - spriteNum);
	this->labelArrowNumLeft = LabelTTF::create(num, "Brush Script MT", 32);
	labelArrowNumLeft->setColor(Color3B(225, 225, 225));
	labelArrowNumLeft->setPosition(100, visibleSize.height - 25);
	this->addChild(labelArrowNumLeft, 1);
}

void ArrowSpriteLayer::setArroSprite()
{

	this->spriteNum = 0;

	for (int i = 1; i <= this->ARROWNUMBER; i++)
	{
		Sprite* arrowSprite = Sprite::createWithSpriteFrameName("Arrow.png");



		_vecArrowSprite.pushBack(arrowSprite);
	}
	_arrowSprite = _vecArrowSprite.at(0);
	_arrowSprite->setTag(10);
	auto physicsArrowBody = PhysicsBody::createBox(_arrowSprite->getContentSize());


	physicsArrowBody->setGravityEnable(false);
	/* 设置碰撞掩码*/
	physicsArrowBody->setCategoryBitmask(1);
	physicsArrowBody->setCollisionBitmask(-1);
	physicsArrowBody->setContactTestBitmask(-1);
	physicsArrowBody->setMass(100);


	_arrowSprite->setPhysicsBody(physicsArrowBody);
	this->addChild(_arrowSprite, 1);
}

Sprite* ArrowSpriteLayer::getArrowSprite()
{
	return _arrowSprite;
}

void ArrowSpriteLayer::changeArrowSpriteReferTo()
{

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (spriteNum <= this->ARROWNUMBER)
	{
		spriteNum++;
	}
	if (spriteNum < this->ARROWNUMBER)
	{

		_arrowSprite = _vecArrowSprite.at(spriteNum);
		auto physicsArrowBody = PhysicsBody::createBox(_arrowSprite->getContentSize());
		physicsArrowBody->setGravityEnable(false);
		physicsArrowBody->setCategoryBitmask(1);
		physicsArrowBody->setCollisionBitmask(-1);
		physicsArrowBody->setContactTestBitmask(-1);
		_arrowSprite->setPhysicsBody(physicsArrowBody);
		_arrowSprite->setVisible(true);
		_arrowSprite->setTag(10);
		this->addChild(_arrowSprite, 1);
		this->isflying = false;
	}
	else
	{
		_arrowSprite = NULL;
	}
}

void ArrowSpriteLayer::update(float dt)
{
	/*判断箭是否飞出屏幕，如果飞出则换箭（可以飞出屏幕上方再落回）*/
	log("this->arrownumber = %d - this->spriteNum = %d  = %d", this->ARROWNUMBER, this->spriteNum, this->ARROWNUMBER - this->spriteNum);
	
	if (_arrowSprite) 
	{
		Point arrowSpritePosition = _arrowSprite->getPosition();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		if (arrowSpritePosition.x > visibleSize.width || arrowSpritePosition.x < 0 || arrowSpritePosition.y < 0)
		{
			if (spriteNum < this->ARROWNUMBER)
			{
				this->_arrowSprite->getPhysicsBody()->removeFromWorld();

				this->_arrowSprite->setVisible(false);

				this->_arrowSprite->removeFromParentAndCleanup(true);

				_observer->onEventHappen(this, ArrowOut);


				//arrowSprite->removeFromPhysicsWorld();
				changeArrowSpriteReferTo();
			}
		}
	}
	else 
	{
		unscheduleUpdate();
		_observer->onEventHappen(this, NoArrow);
	}
	
	/*更新计数图标*/
	/*if (this->ARROWNUMBER - spriteNum >= 0)
	{
		this->labelArrowNumLeft->removeFromParentAndCleanup(true);
		char num[20];
		sprintf(num, "%d", this->ARROWNUMBER - spriteNum);
		this->labelArrowNumLeft = LabelTTF::create(num, "Brush Script MT", 32);
		labelArrowNumLeft->setColor(Color3B(225, 225, 225));
		labelArrowNumLeft->setPosition(100, visibleSize.height - 25);
		this->addChild(labelArrowNumLeft, 1);
	}*/
}

void ArrowSpriteLayer::updateLabel()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*if (this->ARROWNUMBER - spriteNum >= 0)
	{
		layer->labelArrowNumLeft->removeFromParentAndCleanup(true);
		char num[20];
		sprintf(num, "%d", this->ARROWNUMBER - spriteNum);
		layer->labelArrowNumLeft = LabelTTF::create(num, "Brush Script MT", 32);
		labelArrowNumLeft->setColor(Color3B(225, 225, 225));
		labelArrowNumLeft->setPosition(100, visibleSize.height - 25);
		layer->addChild(labelArrowNumLeft, 1);
	}*/
	if (this->ARROWNUMBER - spriteNum >= 0)
	{
		this->labelArrowNumLeft->removeFromParentAndCleanup(true);
		char num[20];
		sprintf(num, "%d", this->ARROWNUMBER - spriteNum);
		this->labelArrowNumLeft = LabelTTF::create(num, "Brush Script MT", 32);
		labelArrowNumLeft->setColor(Color3B(225, 225, 225));
		labelArrowNumLeft->setPosition(100, visibleSize.height - 25);
		this->addChild(labelArrowNumLeft, 1);
	}
}

void ArrowSpriteLayer::onContact()
{
	//this->changeArrowSpriteReferTo();
	_observer->onEventHappen(this, Contact);
}




void ArrowSpriteLayer::setArrowPosition(TMXObjectGroup* arrowObjectGroup)
{
	ValueMap arrowPointMap = arrowObjectGroup->getObject("Heros");
	float arrowX = arrowPointMap.at("x").asFloat();
	float arrowY = arrowPointMap.at("y").asFloat();
	for (int i = 0; i < this->ARROWNUMBER; i++)
	{
		Sprite* spriteArrow = this->_vecArrowSprite.at(i);
		spriteArrow->setPosition(arrowX + 25, arrowY + 25);
	}
}

int ArrowSpriteLayer::getArrowSpriteNumber()
{
	//log("aasdfsdfsd   %d", spriteNum);
	return this->ARROWNUMBER - this->spriteNum;
}

void ArrowSpriteLayer::addObserver(Observer * observer)
{
	_observer = observer;
}

void ArrowSpriteLayer::onMouseMove(Event* event)
{
	if (_arrowSprite)
	{
		auto mouse = (EventMouse*)event;
		/*使箭头转向鼠标所在位置*/
		Point locationTouch = mouse->getLocation();
		Point locationArrowSprite = _arrowSprite->getPosition();
		/*计算需要转的角度*/
		float locationTouchY = 1280 - locationTouch.y;
		float angel = atan((locationTouchY - locationArrowSprite.y) / (locationTouch.x - locationArrowSprite.y)) * 180 / pi;
		if (this->isflying == false && this->isPause == false) 
		{
			// log("locationTouch.x = %lf,locationTouch.y = %lf, locationArrowSprite.x = %lf locationArrowSprite.y = %lf", locationTouch.x, 1280.0 - locationTouch.y, locationArrowSprite.x, locationArrowSprite.y);
			if (locationTouch.x == locationArrowSprite.x&&locationTouchY < locationArrowSprite.y)
			{
				float angel0 = 90;
				_arrowSprite->setRotation(angel0);

				_observer->onEventHappen(this, ArrowRotate);
				/*if (layer1 != nullptr)
				{
					layer1->arch->setRotation(angel0);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(angel0);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(angel0);
				}*/
			}
			else if (locationTouch.x == locationArrowSprite.x&&locationTouchY > locationArrowSprite.y)
			{
				float angel0 = -90;
				_arrowSprite->setRotation(angel0);

				_observer->onEventHappen(this, ArrowRotate);
				/*if (layer1 != nullptr)
				{
					layer1->arch->setRotation(angel0);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(angel0);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(angel0);
				}*/
			}
			else if (locationTouch.x < locationArrowSprite.x&&locationTouchY == locationArrowSprite.y)
			{
				auto rotateTo = RotateTo::create(0.1f, -180);
				_arrowSprite->runAction(rotateTo);
				_arrowSprite->setRotation(-180);

				_observer->onEventHappen(this, ArrowRotate);
				/*if (layer1 != nullptr)
				{
					layer1->arch->setRotation(-180);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(-180);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(-180);
				}*/
			}
			else if (locationTouch.x > locationArrowSprite.x&&locationTouchY == locationArrowSprite.y)
			{

			}
			else if (locationTouch.x > locationArrowSprite.x&&locationTouchY > locationArrowSprite.y)
			{
				float angel0 = angel;
				if (angel > 0)
				{
					angel0 = -angel;
					_arrowSprite->setRotation(angel0);
				}
				if (angel < 0)
				{
					_arrowSprite->setRotation(angel0);
				}

				_observer->onEventHappen(this, ArrowRotate);
				/*if (layer1 != nullptr)
				{
					layer1->arch->setRotation(angel0);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(angel0);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(angel0);
				}*/
			}
			else if (locationTouch.x > locationArrowSprite.x&&locationTouchY < locationArrowSprite.y)
			{
				float angel0 = angel;
				if (angel < 0)
				{
					angel0 = -angel;
					_arrowSprite->setRotation(angel0);
				}
				if (angel > 0)
				{
					_arrowSprite->setRotation(angel0);
				}

				_observer->onEventHappen(this, ArrowRotate);
				/*if (layer1 != nullptr)
				{
					layer1->arch->setRotation(angel0);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(angel0);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(angel0);
				}*/
			}
			else if (locationTouch.x<locationArrowSprite.x&&locationTouchY>locationArrowSprite.y)
			{
				float angel0 = -180.0 - angel;
				_arrowSprite->setRotation(angel0);

				_observer->onEventHappen(this, ArrowRotate);
				/*if (layer1 != nullptr)
				{
					layer1->arch->setRotation(angel0);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(angel0);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(angel0);
				}*/
			}
			else if (locationTouch.x < locationArrowSprite.x&&locationTouchY < locationArrowSprite.y)
			{
				float angel0 = -180.0 - angel;
				_arrowSprite->setRotation(angel0);

				_observer->onEventHappen(this, ArrowRotate);
				/*if (layer1 != nullptr)
				{
					layer1->arch->setRotation(angel0);
				}
				else if (layer2 != nullptr)
				{
					layer2->arch->setRotation(angel0);
				}
				else if (layer3 != nullptr)
				{
					layer3->arch->setRotation(angel0);
				}*/
			}
		}
	}
}