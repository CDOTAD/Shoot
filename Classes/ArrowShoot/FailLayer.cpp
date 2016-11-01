#include"FailLayer.h"
#include"FirstScene.h"
#include"MainScene.h"
//#include "SceneMComplete.h"

Scene* FailLayer::CreateScene(){
	auto scene = Scene::create();
	auto layer = FailLayer::create();
	scene->addChild(layer);
	return scene;
}

bool FailLayer::init(){
	if (!Layer::create()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background = Sprite::createWithSpriteFrameName("pausebackground.png");
	background->setPosition(visibleSize / 2);
	this->addChild(background, 0);

	Sprite* endSprite = Sprite::createWithSpriteFrameName("End.png");
	endSprite->setPosition(visibleSize / 2);
	this->addChild(endSprite, 1);

	auto againButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("again.png"),
		Sprite::createWithSpriteFrameName("againOn.png"),
		CC_CALLBACK_1(FailLayer::menuAgainCallBack, this));

	auto menuButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("menu.png"),
		Sprite::createWithSpriteFrameName("menuOn.png"),
		CC_CALLBACK_1(FailLayer::menuMenuCallBack, this));

	auto exitButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("exit.png"),
		Sprite::createWithSpriteFrameName("exitOn.png"),
		CC_CALLBACK_1(FailLayer::menuExitCallBack, this));
	auto menu = Menu::create(againButton, menuButton, exitButton, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height*0.4);
	menu->alignItemsVertically();
	this->addChild(menu, 2);

	return true;
}

void FailLayer::menuAgainCallBack(Ref* pSender){
	if (this->mainPlayLayer != NULL){
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(1.5f, MainScene::CreateScene()));
	}
	else if (this->mainStep2Layer != NULL){
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(1.5f, MainStep2Scene::CreateScene()));
	}
	else if (this->mainStep3Layer != NULL){
		this->removeFromParentAndCleanup(true);
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(1.5f, MainStep3Scene::CreateScene()));
	}
}

void FailLayer::menuExitCallBack(Ref* pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

void FailLayer::menuMenuCallBack(Ref* pSender){
	Director::getInstance()->resume();
	//Director::getInstance()->replaceScene(SceneMComplete::createScene(3));
	
	/*
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(FirstScene::CreateScene());*/
}
