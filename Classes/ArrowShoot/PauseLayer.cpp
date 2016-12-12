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
	_observer->onResume(this);
}

void PauseLayer::menuAgainCallBack(Ref* pSender){

	_observer->onAgain(this);
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

void PauseLayer::addObserver(PauseObserver * observer)
{
	_observer = observer;
}
