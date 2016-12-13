#include "SceneProduct.h"
#include "MonsterProduct.h"
#include "ArrowProduct.h"
#include "AbstractFactory.h"

Scene* SceneProduct::operationScene() {
	return CreateScene();
}

Scene* SceneProduct::CreateScene() {
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0, -980));

	auto layer = SceneProduct::create();
	scene->addChild(layer);

	return scene;
}

bool SceneProduct::init() {
	if (!Layer::create()) {
		return false;
	}
	auto dirs = Director::getInstance();
	Size visibleSize = dirs->getVisibleSize();
	/*异步加载*/
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Pictures.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("AS_Zombie.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("B_Figure.plist");

	auto backGround = Sprite::createWithSpriteFrameName("SkullBarMain.png");
	backGround->setPosition(visibleSize / 2);
	this->addChild(backGround);

	auto label = Label::create("My Game", "Marker Felt", 36);
	label->setPosition(ccp(visibleSize.width / 2, visibleSize.height - 50));
	this->addChild(label, 1);

	auto startItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("Play.png"),
		Sprite::createWithSpriteFrameName("Play.png"),
		CC_CALLBACK_1(SceneProduct::menuStartCallback, this));
	auto closeItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrameName("exit.png"),
		Sprite::createWithSpriteFrameName("exitOn.png"),
		CC_CALLBACK_1(SceneProduct::menuCloseCallback, this));

	auto menu = Menu::create(startItem, closeItem, NULL);
	menu->alignItemsVertically();
	this->addChild(menu, 1);

	return true;
}

void SceneProduct::menuStartCallback(Ref* pSender) {
	Director::getInstance()->replaceScene(
		TransitionSplitRows::create(3.0f, Scene1::CreateScene()));
}

void SceneProduct::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

Vec2 SceneProduct::getSpeed()
{
	return Vec2();
}


Scene * Scene1::operationScene()
{
	return Scene1::CreateScene();
}

Scene* Scene1::CreateScene() {
	auto scene = Scene::createWithPhysics();
	//scene->setTag(123321);
	scene->getPhysicsWorld()->setGravity(Vect(0, -980));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = Scene1::create();

	scene->addChild(layer);

	return scene;
}

bool Scene1::init() {
	if (!GameLayer::create()) {
		return false;
	}
	_arrowNumber = STEP_ONE_ARROW;
	_monsterNumber = MONSTER_NUM;
	AbstractFactory* factory = new Factory1();
	MonsterProduct* monster = factory->createMonsterProduct();
	ArrowProduct* arrow = factory->createArrowProduct();

	/*加载地图*/

	setMap(MapLayer::create(), 1);

	/*加载退出按钮 菜单 弓*/
	setCommonPart();


	/*加载箭头*/

	setArrowLayer(arrow->operationArrow());

	/*加载怪物*/
	setMonsterLayer(monster->operationMonster());


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
	fire->setPosition(fireX, fireY);
	fire->release();
	this->addChild(batch, 10);

	ValueMap burningfirePointMap = this->_mapLayer->getObjectGroup()->getObject("BurningFire");
	float burningfireX = burningfirePointMap.at("x").asFloat();
	float burningfireY = burningfirePointMap.at("y").asFloat();
	ParticleSystemQuad* burningfire = ParticleSystemQuad::create("burning.plist");
	burningfire->retain();
	this->burningbatch = ParticleBatchNode::createWithTexture(burningfire->getTexture());
	burningbatch->addChild(burningfire);
	burningfire->setPosition(burningfireX, burningfireY);
	burningfire->release();
	burningbatch->setVisible(false);
	this->addChild(burningbatch, 10);

	/*碰撞监听器*/

	setListener();


	/*键盘监听器*/
	auto listenerKeypad = EventListenerKeyboard::create();
	listenerKeypad->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		/*如果按ESC键创建暂停层*/
		if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
			if (this->_flagPressed == false) {
				this->Pause();
				this->_flagPressed = true;
			}

		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeypad, this);

	this->scheduleUpdate();

	//this->schedule(schedule_selector(MainScene::judge), 3.0f, kRepeatForever,0.0f);
	this->schedule(schedule_selector(SceneProduct::setBurning), 10.0f, kRepeatForever, 0.0f);
	delete factory;
	factory = NULL;
	delete arrow;
	arrow = NULL;
	delete monster;
	monster = NULL;

	return true;
}
void Scene1::onEventHappen(Layer * object, MyEvent e)
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
		auto step2 = Scene2::create();
		/*step2->Scores = 0.2*score;*/
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(3.0f, Scene2::CreateScene()));

		break;

	}
	case ArrowRotate: {
		if (((ArrowProduct*)object)->getArrowSprite())
		{
			float angle = ((ArrowProduct*)object)->getArrowSprite()->getRotation();

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

void Scene1::Pause() {
	Director::getInstance()->pause();
	if (this->_arrowLayer->isflying == true) {
		speed = this->_arrowLayer->getArrowSprite()->getPhysicsBody()->getVelocity();
		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setVelocity(Vec2::ZERO);
		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setGravityEnable(FALSE);
	}
	//this->pauseSchedulerAndActions();
	this->pauselayer = PauseLayer::create();
	//	this->pauselayer->mainStep2Layer = NULL;
	//	this->pauselayer->mainStep3Layer = NULL;
	//	this->pauselayer->mainPlayLayer = this;
	this->addChild(pauselayer, 20);
}

void Scene1::update(float dt){

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

void Scene1::judge(float dt){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (this->_arrowLayer->getArrowSpriteNumber() >= 0 && this->_monsterLayer->getMonsterNumber() == 0){		
		float score = MAX_SCORES+4 * this->_arrowLayer->getArrowSpriteNumber() - 8 * this->_monsterLayer->getMonsterNumber()-0.01*this->scores;
		//this->_arrowLayer->step = 2;
		this->_mapLayer->step = 2;
	//	this->_monsterLayer->step = 2;
		auto step2 = Scene2::create();
		step2->Scores = 0.2*score;
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(3.0f, Scene2::CreateScene()));
	}
	if (this->_arrowLayer->getArrowSpriteNumber() <= 0 && this->_monsterLayer->getMonsterNumber() > 0){
		float score = MAX_SCORES-20 * this->_monsterLayer->getMonsterNumber()-0.1*this->scores;
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
}
void Scene2::judge(float dt) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (this->_arrowLayer->getArrowSpriteNumber() >= 0 && this->_monsterLayer->getMonsterNumber() == 0) {
		float score = MAX_SCORES + 4 * this->_arrowLayer->getArrowSpriteNumber() - 8 * this->_monsterLayer->getMonsterNumber() - 0.01*this->scores;
		//this->_arrowLayer->step = 2;
		this->_mapLayer->step = 2;
		//	this->_monsterLayer->step = 2;
		auto step2 = Scene3::create();
		step2->Scores = 0.2*score;
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(3.0f, Scene3::CreateScene()));
	}
	if (this->_arrowLayer->getArrowSpriteNumber() <= 0 && this->_monsterLayer->getMonsterNumber() > 0) {
		float score = MAX_SCORES - 20 * this->_monsterLayer->getMonsterNumber() - 0.1*this->scores;
		int scorefinal = (int)(0.2*score);
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
}

void Scene1::setBurning(float dt){
	this->burningbatch->setVisible(true);
	this->_flagBurning = true;
	this->scheduleOnce(schedule_selector(Scene1::deleteBurning), 3.0f);
}

void Scene1::deleteBurning(float dt){
	this->burningbatch->setVisible(false);
	this->_flagBurning = false;
}


void Scene1::onAgain(Layer * objcet)
{
	this->removeChild(objcet, true);

	
	//this->removeAllChildrenWithCleanup(true);


	Director::getInstance()->resume();


	this->_monsterLayer->unscheduleUpdate();
	this->_arrowLayer->unscheduleUpdate();
	this->unscheduleUpdate();
	
	//log("in mainstep1");

	Director::getInstance()->replaceScene(
		TransitionSplitRows::create(3.0f,Scene1::CreateScene()));

}


void Scene1::menuExitCallBack(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void Scene2::menuExitCallBack(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void Scene3::menuExitCallBack(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
float Scene2::Scores = 0;



Scene* Scene2::operationScene() {
	return CreateScene();
}


Scene* Scene2::CreateScene() {
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setGravity(Vect(0, -980));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = Scene2::create();
	scene->addChild(layer);

	return scene;
}

bool Scene2::init() {
	if (!Layer::create()) {
		return false;
	}
	AbstractFactory* factory = new Factory2();
	MonsterProduct* monster = factory->createMonsterProduct();
	ArrowProduct* arrow = factory->createArrowProduct();
	//Size visibleSize = Director::getInstance()->getVisibleSize();

	_arrowNumber = STEP_TWO_ARROW;
	_monsterNumber = MONSTER_NUM;

	_arrowNumber = STEP_TWO_ARROW;
	_monsterNumber = MONSTER_NUM;

	/*加载地图*/
	setMap(MapLayer::create(), 2);

	/*创建退出按钮*/

	setCommonPart();

	/*加载箭头*/

	setArrowLayer(arrow->operationArrow());


	/*加载怪物*/
	setMonsterLayer(monster->operationMonster());

	/*创建英雄*/
	setHero(Sprite::createWithSpriteFrameName("B_littlestar.png"));/*


																   /*碰撞监听器*/

	setListener();


	/*键盘监听器*/
	auto listenerKeypad = EventListenerKeyboard::create();
	listenerKeypad->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		/*如果按ESC键创建暂停层*/
		if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
			if (this->_flagPressed == false) {
				this->Pause();
				this->_flagPressed = true;
			}

		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeypad, this);

	this->scheduleUpdate();

	//this->schedule(schedule_selector(Scene2::judge), 3.0f, kRepeatForever, 0.0f);

	delete factory;
	factory = NULL;
	delete arrow;
	arrow = NULL;
	delete monster;
	monster = NULL;
	return true;
}
void  Scene2::onAgain(Layer * objcet)
{

	//log("in mainstep2");
	this->removeChild(objcet, true);

	Director::getInstance()->resume();

	this->_monsterLayer->unscheduleUpdate();
	this->_arrowLayer->unscheduleUpdate();
	this->unscheduleUpdate();

	Director::getInstance()->replaceScene(
		TransitionSplitRows::create(3.0f,  Scene2::CreateScene()));

}
void Scene2::onEventHappen(Layer * object, MyEvent e)
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
		this->_mapLayer->step = 3;
		//this->_monsterLayer->step = 3;
		//auto step3 = Scene3::create();
		//step3->Scores = 0.3*score;
		Director::getInstance()->replaceScene(
			TransitionSplitRows::create(3.0f, Scene3::CreateScene()));

		break;

	}
	case ArrowRotate: {
		if (((ArrowProduct*)object)->getArrowSprite())
		{
			float angle = ((ArrowProduct*)object)->getArrowSprite()->getRotation();

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

void Scene2::update(float dt)
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


void Scene2::Pause() {
	Director::getInstance()->pause();
	if (this->_arrowLayer->isflying == true) {
		speed = this->_arrowLayer->getArrowSprite()->getPhysicsBody()->getVelocity();
		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setVelocity(Vec2::ZERO);
		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setGravityEnable(FALSE);
	}
	//this->pauseSchedulerAndActions();
	this->pauselayer = PauseLayer::create();
	//	this->pauselayer->mainStep2Layer = this;
	//	this->pauselayer->mainStep3Layer = NULL;
	//	this->pauselayer->mainPlayLayer = NULL;
	this->addChild(pauselayer, 20);
}

float Scene3::Scores = 0;

Scene* Scene3::operationScene() {
	return CreateScene();
}


Scene* Scene3::CreateScene() {
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setGravity(Vect(0, -980));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = Scene3::create();
	scene->addChild(layer);

	return scene;
}

bool Scene3::init() {
	if (!Layer::create()) {
		return false;
	}
	AbstractFactory* factory = new Factory3();
	MonsterProduct* monster = factory->createMonsterProduct();
	ArrowProduct* arrow = factory->createArrowProduct();
	_monsterNumber = MONSTER_NUM;
	_arrowNumber = STEP_THREE_ARROW;

	/*加载地图*/
	setMap(MapLayer::create(), 3);

	setCommonPart();
	/*加载箭头*/

	setArrowLayer(arrow->operationArrow());

	/*加载怪物*/

	setMonsterLayer(monster->operationMonster());

	/*创建英雄*/
	setHero(Sprite::createWithSpriteFrameName("B_sensen.png"));

	/*创建火焰效果*/

	ValueMap burningfirePointMap = this->_mapLayer->getObjectGroup()->getObject("BurningFire");
	float burningfireX = burningfirePointMap.at("x").asFloat();
	float burningfireY = burningfirePointMap.at("y").asFloat();
	ParticleSystemQuad* burningfire = ParticleSystemQuad::create("burning.plist");
	burningfire->retain();
	this->burningbatch = ParticleBatchNode::createWithTexture(burningfire->getTexture());
	burningbatch->addChild(burningfire);
	burningfire->setPosition(burningfireX, burningfireY);
	burningfire->release();
	burningbatch->setVisible(false);
	this->addChild(burningbatch, 10);

	/*碰撞监听器*/


	setListener();


	/*键盘监听器*/
	auto listenerKeypad = EventListenerKeyboard::create();
	listenerKeypad->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		/*如果按ESC键创建暂停层*/
		if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
			if (this->_flagPressed == false) {
				this->Pause();
				this->_flagPressed = true;
			}

		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeypad, this);

	this->scheduleUpdate();
	this->schedule(schedule_selector(Scene3::setBurning), 6.0f, kRepeatForever, 0.0f);
	delete factory;
	factory = NULL;
	delete arrow;
	arrow = NULL;
	delete monster;
	monster = NULL;
	return true;

}

void Scene3::update(float dt) {
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


void SceneProduct::update(float dt)
{
}

void SceneProduct::setBurning(float dt)
{
	
}

void SceneProduct::onEventHappen(Layer * object, MyEvent e)
{
}

void SceneProduct::onAgain(Layer * objcet)
{
}

void SceneProduct::onResume(Layer * objcet)
{
}



void Scene3::Pause() {
	Director::getInstance()->pause();
	if (this->_arrowLayer->isflying == true) {
		speed = this->_arrowLayer->getArrowSprite()->getPhysicsBody()->getVelocity();
		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setVelocity(Vec2::ZERO);
		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setGravityEnable(FALSE);
	}
	//this->pauseSchedulerAndActions();
	this->pauselayer = PauseLayer::create();
	//	this->pauselayer->mainStep3Layer = this;
	//	this->pauselayer->mainPlayLayer = NULL;
	//	this->pauselayer->mainStep2Layer = NULL;
	this->addChild(pauselayer, 20);
}

void  Scene3::setBurning(float dt)
{
	this->burningbatch->setVisible(true);
	this->_flagBurning = true;
	this->scheduleOnce(schedule_selector( Scene3::deleteBurning), 1.5f);
}
void  Scene3::onEventHappen(Layer * object, MyEvent e)
{
	switch (e)
	{
	case NoArrow: {
		if (_monsterNumber > 0)
		{
			Size visibleSize = Director::getInstance()->getVisibleSize();
			float score = MAX_SCORES - 20 * this->_monsterLayer->getMonsterNumber() - 0.1*this->scores;
			int scorefinal = (int)(0.5*score + this->Scores);
			char finalscore[20];
			sprintf(finalscore, "%d", scorefinal);
			auto scorelabel = LabelTTF::create(finalscore, "Brush Script MT", 32);
			scorelabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 100);
			MessageBox("There are no arrows left", "Poi!");
			Director::getInstance()->pause();
			this->faillayer = FailLayer::create();
			this->faillayer->mainStep3Layer = this;
			this->addChild(faillayer, 20);
			this->addChild(scorelabel, 21);
			break;
		}
	}
	case NoMonster: {

		Director::getInstance()->pause();
		this->winlayer = WinLayer::create();
		this->addChild(winlayer, 20);

		break;

	}
	case ArrowRotate: {
		if (((ArrowProduct*)object)->getArrowSprite())
		{
			float angle = ((ArrowProduct*)object)->getArrowSprite()->getRotation();
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

void Scene3::onAgain(Layer * objcet)
{

	this->removeChild(objcet, true);

	Director::getInstance()->resume();

	this->_monsterLayer->unscheduleUpdate();
	this->_arrowLayer->unscheduleUpdate();
	this->unscheduleUpdate();
	

	Director::getInstance()->replaceScene(
		TransitionSplitRows::create(3.0f, Scene3::CreateScene()));
}
void Scene3::deleteBurning(float dt)
{
	this->burningbatch->setVisible(false);
	this->_flagBurning = false;
}