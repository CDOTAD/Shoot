#include"MainScene.h"
#include"FirstScene.h"
#include"MainStep2Scene.h"
#include"ArrowSpriteStep1Layer.h"
#include"MonsterSpriteStep1Layer.h"



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

	
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("AS_Zombie.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("B_Figure.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Pictures.plist");

	_arrowNumber = STEP_ONE_ARROW;
	_monsterNumber = MONSTER_NUM;

	Director* dir = Director::getInstance();
	Size visibleSize = dir->getVisibleSize();
	
	/*加载地图*/
	this->_mapLayer = MapLayer::create();

	//this->map->setPosition(10, 10);

	this->_mapLayer->step = 1;
	this->addChild(_mapLayer, 1);
	
	//log("map.position = (%f , %f)", map->getPositionX(), map->getPositionY());


	/*创建退出按钮*/
	auto exitButton = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("exit.png"),
		Sprite::createWithSpriteFrameName("exitOn.png"),
		CC_CALLBACK_1(MainScene::menuExitCallBack, this));
	exitButton->setScale(0.4);
	
	auto menu = Menu::create(exitButton, NULL);
	menu->setPosition(visibleSize.width*0.9, 32);
	this->addChild(menu, 2);

	/*加载箭头*/
	this->_arrowLayer = ArrowSpriteStep1Layer::create();
	this->_arrowLayer->setTag(ARROW_LAYER_TAG);
	//this->_arrowLayer->step = 1;
	this->_arrowLayer->addObserver(this);
	_arrowLayer->setArrowPosition(this->_mapLayer->getObjectGroup());
	this->addChild(_arrowLayer,2);
	
	/*加载弓*/
	arch = Sprite::createWithSpriteFrameName("arch.png");
	ValueMap archPointMap = this->_mapLayer->getObjectGroup()->getObject("Heros");
	float archX = archPointMap.at("x").asFloat();
	float archY = archPointMap.at("y").asFloat();
	arch->setPosition(archX + 20 , archY + 30);
	arch->setScale(0.7f);
	this->addChild(arch, 1);

	/*加载怪物*/
	this-> _monsterLayer = MonsterSpriteStep1Layer::create();
	this->_monsterLayer->setTag(MONSTER_LAYER_TAG);
	this->_monsterLayer->addObserver(this);
	_monsterLayer->setMonstersPosition(this->_mapLayer->getObjectGroup());
	this->addChild(_monsterLayer, 2);
	
	/*创建英雄*/
	myHero = Sprite::createWithSpriteFrameName("B_huolong.png");
	ValueMap heroPointMap = this->_mapLayer->getObjectGroup()->getObject("Heros");
	float heroX = heroPointMap.at("x").asFloat();
	float heroY = heroPointMap.at("y").asFloat();
	myHero->setPosition(heroX + 25-64, heroY + 50);
	myHero->setScale(0.1f);
	this->addChild(myHero, 1);
	
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
	_contactListener = EventListenerPhysicsContact::create();
	
	_contactListener->onContactBegin = [=](PhysicsContact &contact){
		auto nodeA = contact.getShapeA()->getBody()->getNode();
		auto nodeB = contact.getShapeB()->getBody()->getNode();
		if (nodeA&&nodeB){
			if (nodeA->getTag() == 10){
				//nodeB->getPhysicsBody()->removeFromWorld();
				//nodeB->removeFromParent();
				

				/*

				this->monsterLayer->onContact(int tag);

				*/
				
				nodeB->getPhysicsBody()->removeFromWorld();
				nodeB->setVisible(false);
			}
			else if (nodeB->getTag() == 10){
				//nodeA->getPhysicsBody()->removeFromWorld();
				//nodeA->removeFromParent();
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
			/*this->getScene()->getPhysicsWorld()->removeBody(_arrowLayer->getArrowSprite()->getPhysicsBody());
			log("%d", this->getScene()->getTag());*/
			this->_arrowLayer->getArrowSprite()->setVisible(false);
			if (_monsterLayer->getMonsterNumber() > 0) {

				//log("contactSeparate");

				this->_arrowLayer->changeArrowSpriteReferTo();
				this->_arrowLayer->onContact();
				this->_arrowLayer->updateLabel();
			}
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_contactListener, this);
	
	/*键盘监听器*/
	auto listenerKeypad = EventListenerKeyboard::create();
	listenerKeypad->onKeyPressed = [=](EventKeyboard::KeyCode keyCode,Event* event){
		/*如果按ESC键创建暂停层*/
		if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE){
			if (this->_flagPressed == false){
				this->Pause();
				this->_flagPressed = true;
			}
			
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeypad, this);
	
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
		this->_mapLayer->step = 2;
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
			this->arch->setRotation(angle);
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

void MainScene::Pause(){
	Director::getInstance()->pause();
	if (this->_arrowLayer->isflying == true){
		speed = this->_arrowLayer->getArrowSprite()->getPhysicsBody()->getVelocity();
		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setVelocity(Vec2::ZERO);
		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setGravityEnable(FALSE);
	}
	//this->pauseSchedulerAndActions();
	this->pauselayer = PauseLayer::create();
	this->pauselayer->mainPlayLayer = this;
	this->pauselayer->mainStep2Layer = NULL;
	this->pauselayer->mainStep3Layer = NULL;
	this->addChild(pauselayer, 20);
}

Vec2 MainScene::getSpeed(){
	return this->speed;
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