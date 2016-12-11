#include "GameLayer.h"
#include"FailLayer.h"


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
