#include"MainScene.h"
#include"FirstScene.h"
#include"MainStep2Scene.h"
#include"ArrowSpriteStep1Layer.h"
#include"MonsterSpriteStep1Layer.h"
#include"MapStep1Layer.h"



Scene* MainScene::CreateScene(){
	auto scene = Scene::createWithPhysics();
	//scene->setTag(123321);
	scene->getPhysicsWorld()->setGravity(Vect(0, -980));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = MainScene::create();

	scene->addChild(layer);
	
	return scene;
}

bool MainScene::init(){
	if (!GameLayer::create()){
		return false;
	}

	_arrowNumber = STEP_ONE_ARROW;
	_monsterNumber = MONSTER_NUM;


	
	/*加载地图*/

	setMap(MapStep1Layer::create());

	/*加载退出按钮 菜单 弓*/
	setCommonPart();

	
	/*加载箭头*/

	setArrowLayer(ArrowSpriteStep1Layer::create());

	/*加载怪物*/
	setMonsterLayer(MonsterSpriteStep1Layer::create());


	/*创建英雄*/
	setHero(Sprite::createWithSpriteFrameName("B_huolong.png"));
	
	/*创建火焰效果*/
	ValueMap firePointMap = this->_mapLayer->getObjectGroup()->getObject("Fire");
	float fireX = firePointMap.at("x").asFloat();
	float fireY = firePointMap.at("y").asFloat();
	ParticleSystemQuad* fire = ParticleSystemQuad::create("fire1.plist");
	fire->retain();
	ParticleBatchNode* batch = ParticleBatchNode::createWithTexture(fire->getTexture());
	batch->addChild(fire);
	fire->setPosition(fireX,fireY);
	fire->release();
	this->addChild(batch, 10);

	ValueMap burningfirePointMap = this->_mapLayer->getObjectGroup()->getObject("BurningFire");
	float burningfireX = burningfirePointMap.at("x").asFloat();
	float burningfireY = burningfirePointMap.at("y").asFloat();
	ParticleSystemQuad* burningfire = ParticleSystemQuad::create("burning.plist");
	burningfire->retain();
	this-> burningbatch = ParticleBatchNode::createWithTexture(burningfire->getTexture());
	burningbatch->addChild(burningfire);
	burningfire->setPosition(burningfireX, burningfireY);
	burningfire->release();
	burningbatch->setVisible(false);
	this->addChild(burningbatch, 10);

	/*碰撞监听器*/

	setListener();

	
	/*键盘监听器*/
	//auto listenerKeypad = EventListenerKeyboard::create();
	//listenerKeypad->onKeyPressed = [=](EventKeyboard::KeyCode keyCode,Event* event){
	//	/*如果按ESC键创建暂停层*/
	//	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE){
	//		if (this->_flagPressed == false){
	//			this->Pause();
	//			this->_flagPressed = true;
	//		}
	//		
	//	}
	//};
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeypad, this);
	//
	this->scheduleUpdate();

	//this->schedule(schedule_selector(MainScene::judge), 3.0f, kRepeatForever,0.0f);
	this->schedule(schedule_selector(MainScene::setBurning), 10.0f, kRepeatForever,0.0f);
	return true;
}


void MainScene::update(float dt){

	this->scores += 0.1;
	/*判断箭是否碰撞到了障碍*/
	Sprite* arrowSprite = this->_arrowLayer->getArrowSprite();

	if (arrowSprite)
	{
		Point arrowPoint = arrowSprite->getPosition();


		Size visibleSize = Director::getInstance()->getVisibleSize();
		/*飞出屏幕上方则忽略*/
		if (arrowPoint.y < visibleSize.height&&arrowPoint.x < visibleSize.width) {
			/*将坐标转化为瓦片地图里的坐标*/
			Size arrowSize = arrowSprite->getContentSize();
			//Size mapTiledNum = this->map->getMap()->getMapSize();
			Size tiledSize = this->_mapLayer->getMap()->getTileSize();
			if (arrowPoint.x + arrowSize.width / 2 < visibleSize.width) {
				int tiledPosX = (arrowPoint.x + arrowSize.width / 2) / tiledSize.width;
				int tiledPosY = (640 - arrowPoint.y) / tiledSize.height;

				//log("arrwPoint.y = %f", arrowPoint.y);

				Point tiledPos = Point(tiledPosX, tiledPosY);

				TMXLayer* meta = this->_mapLayer->getMap()->getLayer("obscatle");
				int tiledGid = meta->getTileGIDAt(tiledPos);

				if (tiledGid != 0) {
					arrowSprite->getPhysicsBody()->removeFromWorld();
					//arrowSprite->removeFromParentAndCleanup(true);
					//arrowSprite->removeFromParent();//removeFromPhysicsWorld();
					arrowSprite->stopAllActions();

					this->_arrowLayer->changeArrowSpriteReferTo();

					this->_arrowLayer->updateLabel();
				}
			}
		}
		if (this->_flagBurning == true) {
			float arrowX = arrowPoint.x;
			float arrowY = arrowPoint.y;
			float burningX = this->burningbatch->getPosition().x;
			float burningY = this->burningbatch->getPosition().y;
			if ((arrowX + arrowSprite->getContentSize().width / 2) >= 8 * 32 && (arrowX - arrowSprite->getContentSize().width / 2) <= 11 * 32) {
				//arrowSprite->getPhysicsBody()->removeFromWorld();
				arrowSprite->removeFromParent();//removeFromPhysicsWorld();
				arrowSprite->stopAllActions();
				arrowSprite->setVisible(false);

				this->_arrowLayer->changeArrowSpriteReferTo();

				this->_arrowLayer->updateLabel();
			}
		}
	}
}

//void MainScene::judge(float dt){
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	if (this->_arrowLayer->getArrowSpriteNumber() >= 0 && this->_monsterLayer->getMonsterNumber() == 0){		
//		float score = MAX_SCORES+4 * this->_arrowLayer->getArrowSpriteNumber() - 8 * this->_monsterLayer->getMonsterNumber()-0.01*this->scores;
//		//this->_arrowLayer->step = 2;
//		this->_mapLayer->step = 2;
//		this->_monsterLayer->step = 2;
//		auto step2 = MainStep2Scene::create();
//		step2->Scores = 0.2*score;
//		Director::getInstance()->replaceScene(
//			TransitionSplitRows::create(3.0f, MainStep2Scene::CreateScene()));
//	}
//	if (this->_arrowLayer->getArrowSpriteNumber() <= 0 && this->_monsterLayer->getMonsterNumber() > 0){
//		float score = MAX_SCORES-20 * this->_monsterLayer->getMonsterNumber()-0.1*this->scores;
//		int scorefinal = (int)(0.2*score);
//		char finalscore[20];
//		sprintf(finalscore, "%d", scorefinal);
//		auto scorelabel = LabelTTF::create(finalscore, "Brush Script MT", 32);
//		scorelabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 100);
//		MessageBox("There are no arrows left", "Poi!");
//		Director::getInstance()->pause();
//		this->faillayer = FailLayer::create();
//		this->faillayer->mainPlayLayer = this;
//		this->addChild(faillayer, 20);
//		this->addChild(scorelabel, 21);
//	}
//}

void MainScene::setBurning(float dt){
	this->burningbatch->setVisible(true);
	this->_flagBurning = true;
	this->scheduleOnce(schedule_selector(MainScene::deleteBurning), 3.0f);
}

void MainScene::deleteBurning(float dt){
	this->burningbatch->setVisible(false);
	this->_flagBurning = false;
}

void MainScene::onEventHappen(Layer * object, MyEvent e)
{

	switch (e)
	{
	case NoArrow: {

		if (_monsterNumber > 0)
		{
			Size visibleSize = Director::getInstance()->getVisibleSize();
			float score = MAX_SCORES - 20 * this->_monsterLayer->getMonsterNumber() - 0.1*this->scores;
			int scorefinal = (int)(0.2*score);
			char finalscore[20];
			sprintf(finalscore, "%d", scorefinal);
			auto scorelabel = LabelTTF::create(finalscore, "Brush Script MT", 32);
			scorelabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 100);
			MessageBox("There are no arrows left", "Poi!");
			Director::getInstance()->pause();
			this->faillayer = FailLayer::create();
			this->faillayer->mainPlayLayer = this;
			this->addChild(faillayer, 20);
			this->addChild(scorelabel, 21);
		}
		break;
	}
	case NoMonster: {

		float score = MAX_SCORES + 4 * this->_arrowLayer->getArrowSpriteNumber() - 8 * this->_monsterLayer->getMonsterNumber() - 0.01*this->scores;
		//this->_arrowLayer->step = 2;
		//this->_mapLayer->step = 2;
		//this->_monsterLayer->step = 2;
		auto step2 = MainStep2Scene::create();
		/*step2->Scores = 0.2*score;*/
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(3.0f, MainStep2Scene::CreateScene()));

		break;
	
	}
	case ArrowRotate: {
		if (((ArrowSpriteLayer*)object)->getArrowSprite()) 
		{
			float angle = ((ArrowSpriteLayer*)object)->getArrowSprite()->getRotation();

			this->_arch->setRotation(angle);

		}		break;
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

void MainScene::onAgain(Layer * objcet)
{
	this->removeChild(objcet, true);

	
	//this->removeAllChildrenWithCleanup(true);


	Director::getInstance()->resume();


	this->_monsterLayer->unscheduleUpdate();
	this->_arrowLayer->unscheduleUpdate();
	this->unscheduleUpdate();
	
	//log("in mainstep1");

	Director::getInstance()->replaceScene(
		TransitionSplitRows::create(3.0f,MainScene::CreateScene()));

}


void MainScene::menuExitCallBack(Ref* pSender){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}