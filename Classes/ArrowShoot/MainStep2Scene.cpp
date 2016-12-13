<<<<<<< HEAD
//#include"MainStep2Scene.h"
//#include"MainStep3Scene.h"
//#include"ArrowSpriteStep2Layer.h"
//#include"MonsterSpriteStep2Layer.h"
//
//float MainStep2Scene::Scores = 0;
//
//Scene* MainStep2Scene::CreateScene(){
//	auto scene = Scene::createWithPhysics();
//
//	scene->getPhysicsWorld()->setGravity(Vect(0, -980));
//	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
//
//	auto layer = MainStep2Scene::create();
//	scene->addChild(layer);
//
//	return scene;
//}
//
//bool MainStep2Scene::init(){
//	if (!Layer::create()){
//		return false;
//	}
//
//	//Size visibleSize = Director::getInstance()->getVisibleSize();
//
//	_arrowNumber = STEP_TWO_ARROW;
//	_monsterNumber = MONSTER_NUM;
//
//	_arrowNumber = STEP_TWO_ARROW;
//	_monsterNumber = MONSTER_NUM;
//
//	/*加载地图*/
//	setMap(MapLayer::create(), 2);
//
//	/*创建退出按钮*/
//
//	setCommonPart();
//
//	/*加载箭头*/
//
//	setArrowLayer(Arrow::create());
//
//
//	/*加载怪物*/
//	setMonsterLayer(Monster2::create());
//
//	/*创建英雄*/
//	setHero(Sprite::createWithSpriteFrameName("B_littlestar.png"));/*
//
//
//	/*碰撞监听器*/
//
//	setListener();
//	
//
//	///*键盘监听器*/
//	//auto listenerKeypad = EventListenerKeyboard::create();
//	//listenerKeypad->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
//	//	/*如果按ESC键创建暂停层*/
//	//	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE){
//	//		if (this->_flagPressed == false){
//	//			this->Pause();
//	//			this->_flagPressed = true;
//	//		}
//
//	//	}
//	//};
//	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeypad, this);
//
//	this->scheduleUpdate();
//
//	//this->schedule(schedule_selector(MainStep2Scene::judge), 3.0f, kRepeatForever, 0.0f);
//
//
//	return true;
//}
//
//void MainStep2Scene::onEventHappen(Layer * object, MyEvent e)
//{
//	switch (e)
//	{
//	case NoArrow: {
//		if (_monsterNumber > 0)
//		{
//			Size visibleSize = Director::getInstance()->getVisibleSize();
//			float score = MAX_SCORES - 20 * this->_monsterLayer->getMonsterNumber() - 0.1*this->scores;
//			int scorefinal = (int)(0.3*score + this->Scores);
//			char finalscore[20];
//			sprintf(finalscore, "%d", scorefinal);
//			auto scorelabel = LabelTTF::create(finalscore, "Brush Script MT", 32);
//			scorelabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 100);
//			MessageBox("There are no arrows left", "Poi!");
//			Director::getInstance()->pause();
//			this->faillayer = FailLayer::create();
//			this->faillayer->mainStep2Layer = this;
//			this->addChild(faillayer, 20);
//			this->addChild(scorelabel, 21);
//		}
//		break;
//	}
//	case NoMonster: {
//
//		//this->_arrowLayer->step = 3;
//		this->_mapLayer->step = 3;
//		//this->_monsterLayer->step = 3;
//		//auto step3 = MainStep3Scene::create();
//		//step3->Scores = 0.3*score;
//		Director::getInstance()->replaceScene(
//			TransitionSplitRows::create(3.0f, MainStep3Scene::CreateScene()));
//
//		break;
//
//	}
//	case ArrowRotate: {
//		if (((ArrowSpriteLayer*)object)->getArrowSprite())
//		{
//			float angle = ((ArrowSpriteLayer*)object)->getArrowSprite()->getRotation();
//
//			this->_arch->setRotation(angle);
//
//			break;
//		}
//	}
//	case Contact: {
//		if (MONSTER_LAYER_TAG == object->getTag())
//		{
//			this->_monsterNumber--;
//		}
//		else
//		{
//			this->_arrowNumber--;
//		}
//		break;
//	}
//	case ArrowOut: {
//		this->_arrowNumber--;
//
//		this->_arrowLayer->updateLabel();
//		break;
//	}
//	default:
//		break;
//	}
//}
//
//void MainStep2Scene::onAgain(Layer * objcet)
//{
//
//	//log("in mainstep2");
//	this->removeChild(objcet, true);
//
//	Director::getInstance()->resume();
//
//	this->_monsterLayer->unscheduleUpdate();
//	this->_arrowLayer->unscheduleUpdate();
//	this->unscheduleUpdate();
//
//	Director::getInstance()->replaceScene(
//		TransitionSplitRows::create(3.0f, MainStep2Scene::CreateScene()));
//
//}
//
//void MainStep2Scene::update(float dt)
//{
//	this->scores += 0.1;
//	/*判断箭是否碰撞到了障碍*/
//	Sprite* arrowSprite = this->_arrowLayer->getArrowSprite();
//	if (arrowSprite)
//	{
//
//		Point arrowPoint = arrowSprite->getPosition();
//		Size visibleSize = Director::getInstance()->getVisibleSize();
//		/*飞出屏幕上方则忽略*/
//		if (arrowPoint.y < visibleSize.height) {
//			/*将坐标转化为瓦片地图里的坐标*/
//			Size arrowSize = this->_arrowLayer->getArrowSprite()->getContentSize();
//			Size mapTiledNum = this->_mapLayer->getMap()->getMapSize();
//			Size tiledSize = this->_mapLayer->getMap()->getTileSize();
//			if (arrowPoint.x + arrowSize.width / 2 < visibleSize.width) {
//				int tiledPosX = (arrowPoint.x + arrowSize.width / 2) / tiledSize.width;
//				int tiledPosY = (640 - arrowPoint.y) / tiledSize.height;
//
//				Point tiledPos = Point(tiledPosX, tiledPosY);
//
//				TMXLayer* meta = this->_mapLayer->getMap()->getLayer("obscatle");
//				int tiledGid = meta->getTileGIDAt(tiledPos);
//
//				if (tiledGid != 0) {
//
//					arrowSprite->getPhysicsBody()->removeFromWorld();
//
//					//arrowSprite->removeFromParent();//removeFromPhysicsWorld();
//					arrowSprite->stopAllActions();
//
//					this->_arrowLayer->changeArrowSpriteReferTo();
//
//					this->_arrowLayer->updateLabel();
//				}
//			}
//		}
//	}
//
//}
//
//
//
=======
#include"MainStep2Scene.h"
#include"MainStep3Scene.h"
#include"ArrowSpriteStep2Layer.h"
#include"MonsterSpriteStep2Layer.h"
#include"MapStep2Layer.h"

float MainStep2Scene::Scores = 0;

Scene* MainStep2Scene::CreateScene(){
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setGravity(Vect(0, -980));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = MainStep2Scene::create();
	scene->addChild(layer);

	return scene;
}

bool MainStep2Scene::init(){
	if (!Layer::create()){
		return false;
	}

	//Size visibleSize = Director::getInstance()->getVisibleSize();

	_arrowNumber = STEP_TWO_ARROW;
	_monsterNumber = MONSTER_NUM;

	_arrowNumber = STEP_TWO_ARROW;
	_monsterNumber = MONSTER_NUM;

	/*加载地图*/
	setMap(MapStep2Layer::create());

	/*创建退出按钮*/

	setCommonPart();

	/*加载箭头*/

	setArrowLayer(ArrowSpriteStep2Layer::create());


	/*加载怪物*/
	setMonsterLayer(MonsterSpriteStep2Layer::create());

	/*创建英雄*/
	setHero(Sprite::createWithSpriteFrameName("B_littlestar.png"));/*


	/*碰撞监听器*/

	setListener();
	

	///*键盘监听器*/
	//auto listenerKeypad = EventListenerKeyboard::create();
	//listenerKeypad->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
	//	/*如果按ESC键创建暂停层*/
	//	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE){
	//		if (this->_flagPressed == false){
	//			this->Pause();
	//			this->_flagPressed = true;
	//		}

	//	}
	//};
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeypad, this);

	this->scheduleUpdate();

	//this->schedule(schedule_selector(MainStep2Scene::judge), 3.0f, kRepeatForever, 0.0f);


	return true;
}

void MainStep2Scene::onEventHappen(Layer * object, MyEvent e)
{
	switch (e)
	{
	case NoArrow: {
		if (_monsterNumber > 0)
		{
			Size visibleSize = Director::getInstance()->getVisibleSize();
			float score = MAX_SCORES - 20 * this->_monsterLayer->getMonsterNumber() - 0.1*this->scores;
			int scorefinal = (int)(0.3*score + this->Scores);
			char finalscore[20];
			sprintf(finalscore, "%d", scorefinal);
			auto scorelabel = LabelTTF::create(finalscore, "Brush Script MT", 32);
			scorelabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 100);
			MessageBox("There are no arrows left", "Poi!");
			Director::getInstance()->pause();
			this->faillayer = FailLayer::create();
			this->faillayer->mainStep2Layer = this;
			this->addChild(faillayer, 20);
			this->addChild(scorelabel, 21);
		}
		break;
	}
	case NoMonster: {

		//this->_arrowLayer->step = 3;
		//this->_mapLayer->step = 3;
		//this->_monsterLayer->step = 3;
		//auto step3 = MainStep3Scene::create();
		//step3->Scores = 0.3*score;
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(3.0f, MainStep3Scene::CreateScene()));

		break;

	}
	case ArrowRotate: {
		if (((ArrowSpriteLayer*)object)->getArrowSprite())
		{
			float angle = ((ArrowSpriteLayer*)object)->getArrowSprite()->getRotation();

			this->_arch->setRotation(angle);

			break;
		}
	}
	case Contact: {
		if (MONSTER_LAYER_TAG == object->getTag())
		{
			this->_monsterNumber--;
		}
		else
		{
			this->_arrowNumber--;
		}
		break;
	}
	case ArrowOut: {
		this->_arrowNumber--;

		this->_arrowLayer->updateLabel();
		break;
	}
	default:
		break;
	}
}

void MainStep2Scene::onAgain(Layer * objcet)
{

	//log("in mainstep2");
	this->removeChild(objcet, true);

	Director::getInstance()->resume();

	this->_monsterLayer->unscheduleUpdate();
	this->_arrowLayer->unscheduleUpdate();
	this->unscheduleUpdate();

	Director::getInstance()->replaceScene(
		TransitionSplitRows::create(3.0f, MainStep2Scene::CreateScene()));

}

void MainStep2Scene::update(float dt)
{
	this->scores += 0.1;
	/*判断箭是否碰撞到了障碍*/
	Sprite* arrowSprite = this->_arrowLayer->getArrowSprite();
	if (arrowSprite)
	{

		Point arrowPoint = arrowSprite->getPosition();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		/*飞出屏幕上方则忽略*/
		if (arrowPoint.y < visibleSize.height) {
			/*将坐标转化为瓦片地图里的坐标*/
			Size arrowSize = this->_arrowLayer->getArrowSprite()->getContentSize();
			Size mapTiledNum = this->_mapLayer->getMap()->getMapSize();
			Size tiledSize = this->_mapLayer->getMap()->getTileSize();
			if (arrowPoint.x + arrowSize.width / 2 < visibleSize.width) {
				int tiledPosX = (arrowPoint.x + arrowSize.width / 2) / tiledSize.width;
				int tiledPosY = (640 - arrowPoint.y) / tiledSize.height;

				Point tiledPos = Point(tiledPosX, tiledPosY);

				TMXLayer* meta = this->_mapLayer->getMap()->getLayer("obscatle");
				int tiledGid = meta->getTileGIDAt(tiledPos);

				if (tiledGid != 0) {

					arrowSprite->getPhysicsBody()->removeFromWorld();

					//arrowSprite->removeFromParent();//removeFromPhysicsWorld();
					arrowSprite->stopAllActions();

					this->_arrowLayer->changeArrowSpriteReferTo();

					this->_arrowLayer->updateLabel();
				}
			}
		}
	}

}



>>>>>>> 0c0a614325d6aed0ec766814c0becf9829151b09
