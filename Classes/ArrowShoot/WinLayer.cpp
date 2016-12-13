#include"WinLayer.h"
#include"SceneProduct.h"
//#include "SceneMComplete.h"

Scene* WinLayer::CreateScene(){
	auto scene = Scene::create();
	auto layer = WinLayer::create();
	scene->addChild(layer);
	return scene;
}

bool WinLayer::init(){
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

	auto nextButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("next.png"),
		Sprite::createWithSpriteFrameName("nextOn.png"),
		CC_CALLBACK_1(WinLayer::menuNextCallBack, this));

	auto againButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("again.png"),
		Sprite::createWithSpriteFrameName("againOn.png"),
		CC_CALLBACK_1(WinLayer::menuAgainCallBack, this));

	auto menuButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("menu.png"),
		Sprite::createWithSpriteFrameName("menuOn.png"),
		CC_CALLBACK_1(WinLayer::menuMenuCallBack, this));

	auto exitButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("exit.png"),
		Sprite::createWithSpriteFrameName("exitOn.png"),
		CC_CALLBACK_1(WinLayer::menuExitCallBack, this));
	auto menu = Menu::create(nextButton,  menuButton, exitButton, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height*0.4);
	menu->alignItemsVertically();
	this->addChild(menu, 2);

	return true;
}

void WinLayer::menuNextCallBack(Ref* pSender){
	Director::getInstance()->resume();
	//Director::getInstance()->replaceScene(SceneMComplete::createScene(3));
}

void WinLayer::menuAgainCallBack(Ref* pSender){
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(Scene1::CreateScene());
	
}

void WinLayer::menuExitCallBack(Ref* pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

void WinLayer::menuMenuCallBack(Ref* pSender){
	Director::getInstance()->resume();
	Director::getInstance()->replaceScene(SceneProduct::CreateScene());
}
