#include"MainStep3Scene.h"
#include"ArrowSpriteStep3Layer.h"
#include"MonsterSpriteStep3Layer.h"
#include"MainStep3Scene.h"
#include"MapStep3Layer.h"

float MainStep3Scene::Scores = 0;

Scene* MainStep3Scene::CreateScene(){
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setGravity(Vect(0, -980));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = MainStep3Scene::create();
	scene->addChild(layer);

	return scene;
}

bool MainStep3Scene::init(){
	if (!Layer::create()){
		return false;
	}

	_monsterNumber = MONSTER_NUM;
	_arrowNumber = STEP_THREE_ARROW;

	/*加载地图*/
	setMap(MapStep3Layer::create());

	setCommonPart();
	/*加载箭头*/

	setArrowLayer(ArrowSpriteStep3Layer::create());

	/*加载怪物*/
	
	setMonsterLayer(MonsterSpriteStep3Layer::create());

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
	this->schedule(schedule_selector(MainStep3Scene::setBurning), 6.0f, kRepeatForever, 0.0f);

	return true;

}

void MainStep3Scene::update(float dt){
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


void MainStep3Scene::setBurning(float dt)
{
	this->burningbatch->setVisible(true);
	this->_flagBurning = true;
	this->scheduleOnce(schedule_selector(MainStep3Scene::deleteBurning), 1.5f);
}

void MainStep3Scene::onEventHappen(Layer * object, MyEvent e)
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

void MainStep3Scene::onAgain(Layer * objcet)
{

	this->removeChild(objcet, true);

	Director::getInstance()->resume();

	this->_monsterLayer->unscheduleUpdate();
	this->_arrowLayer->unscheduleUpdate();
	this->unscheduleUpdate();
	

	Director::getInstance()->replaceScene(
		TransitionSplitRows::create(3.0f, MainStep3Scene::CreateScene()));


}

void MainStep3Scene::deleteBurning(float dt)
{
	this->burningbatch->setVisible(false);
	this->_flagBurning = false;
}

Vec2 MainStep3Scene::getSpeed(){
	return this->speed;
}

//void MainStep3Scene::Pause(){
//	Director::getInstance()->pause();
//	if (this->_arrowLayer->isflying == true){
//		speed = this->_arrowLayer->getArrowSprite()->getPhysicsBody()->getVelocity();
//		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setVelocity(Vec2::ZERO);
//		this->_arrowLayer->getArrowSprite()->getPhysicsBody()->setGravityEnable(FALSE);
//	}
//	//this->pauseSchedulerAndActions();
//	this->pauselayer = PauseLayer::create();
//	this->pauselayer->mainStep3Layer = this;
//	this->pauselayer->mainPlayLayer = NULL;
//	this->pauselayer->mainStep2Layer = NULL;
//	this->addChild(pauselayer, 20);
//}
