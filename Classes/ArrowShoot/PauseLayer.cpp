#include"PauseLayer.h"
#include"MainScene.h"

int PauseLayer::step = 1;

Scene* PauseLayer::CreateScene(){
	auto scene = Scene::create();
	auto layer = PauseLayer::create();
	scene->addChild(layer);
	return scene;
}

bool PauseLayer::init(){
	if (!Layer::create()){
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background = Sprite::createWithSpriteFrameName("pausebackground.png");
	background->setPosition(visibleSize / 2);
	this->addChild(background, 1);

	auto pauseSprite = Sprite::createWithSpriteFrameName("pause.png");
	pauseSprite->setPosition(visibleSize / 2);
	this->addChild(pauseSprite, 1);

	auto againButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("again.png"),
		Sprite::createWithSpriteFrameName("againOn.png"),
		CC_CALLBACK_1(PauseLayer::menuAgainCallBack, this));
	
	auto resumeButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("continue.png"),
		Sprite::createWithSpriteFrameName("continueOn.png"),
		CC_CALLBACK_1(PauseLayer::menuResumeCallBack, this));
	
	auto exitButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("exit.png"),
		Sprite::createWithSpriteFrameName("exitOn.png"),
		CC_CALLBACK_1(PauseLayer::menuExitCallBack, this));
	
	auto menu = Menu::create(resumeButton,againButton,exitButton, NULL);
	menu->setPosition(visibleSize / 2);
	menu->alignItemsVertically();
	this->addChild(menu, 1);

	return true;
}

void PauseLayer::menuResumeCallBack(Ref* pSender){
	if (this->mainPlayLayer != NULL){
		this->mainPlayLayer->flagPressed = false;
		if (this->mainPlayLayer->arrow->isflying == true){
			this->mainPlayLayer->arrow->getArrowSprite()->getPhysicsBody()->setVelocity(this->mainPlayLayer->getSpeed());
			this->mainPlayLayer->arrow->getArrowSprite()->getPhysicsBody()->setGravityEnable(true);
		}
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();

	}
	else if (this->mainStep2Layer != NULL){
		this->mainStep2Layer->flagPressed = false;
		if (this->mainStep2Layer->arrow->isflying == true){
			this->mainStep2Layer->arrow->getArrowSprite()->getPhysicsBody()->setVelocity(this->mainStep2Layer->getSpeed());
			this->mainStep2Layer->arrow->getArrowSprite()->getPhysicsBody()->setGravityEnable(true);
		}
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
	}
	else if (this->mainStep3Layer != NULL){
		this->mainStep2Layer->flagPressed = false;
		if (this->mainStep3Layer->arrow->isflying == true){
			this->mainStep3Layer->arrow->getArrowSprite()->getPhysicsBody()->setVelocity(this->mainStep3Layer->getSpeed());
			this->mainStep3Layer->arrow->getArrowSprite()->getPhysicsBody()->setGravityEnable(true);		
		}	
	}
}

void PauseLayer::menuAgainCallBack(Ref* pSender){
	if (this->mainPlayLayer != NULL){
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(3.0f, MainScene::CreateScene()));

	}
	else if (this->mainStep2Layer != NULL){
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(3.0f, MainStep2Scene::CreateScene()));
	}
	else if (this->mainStep3Layer != NULL){
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(3.0f, MainStep3Scene::CreateScene()));
	
	}
}

void PauseLayer::menuExitCallBack(Ref* pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}