#include"MonsterSpriteLayer.h"
#include"MapLayer.h"


float MonsterSpriteLayer::timerand(int i) {
	float x = i;
	float rand = 0.1*(x - 4)*(x - 3) + 0.2*(x - 2)*(x - 1);
	return rand;
}

void MonsterSpriteLayer::addMonster()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	/*�������ﲢװ������*/
	for (int i = 1; i <= MONSTER_NUM; i++) {
		sprintf(name, "zombie%d.png", i);
		Sprite* monsterSprite = Sprite::createWithSpriteFrameName(name);
		monsterSprite->setTag(5);

		auto physicsMonsterBody = PhysicsBody::createBox(monsterSprite->getContentSize());
		physicsMonsterBody->setGravityEnable(false);

		physicsMonsterBody->setCategoryBitmask(1);
		physicsMonsterBody->setCollisionBitmask(-1);
		physicsMonsterBody->setContactTestBitmask(-1);
		physicsMonsterBody->setMass(100);

		monsterSprite->setPhysicsBody(physicsMonsterBody);

		this->addChild(monsterSprite);

		this->_vecMonsterSprite->Push(monsterSprite,i-1);
			
	}
}

void MonsterSpriteLayer::monsterNumberDecrease(){
	 monsterNumber--;
}

void MonsterSpriteLayer::setMonstersPosition(TMXObjectGroup* monsterObjectGroup){
	char monstername[20];
	/*ʹ�õ��������������еĹ����������Ӧ��λ��*/
	Iterator<Sprite*>* it = this->_vecMonsterSprite->createIterator();
	for (it->first(); !it->isDone(); it->next())
	{
			Sprite* monsterSprite = it->currentItem();
			sprintf(monstername, "Monster%d", it->current()+1);
			ValueMap monsterPointMap = monsterObjectGroup->getObject(monstername);
			float monsterX = monsterPointMap.at("x").asFloat();
			float monsterY = monsterPointMap.at("y").asFloat();
			log("monsterX = %f monsterY = %f", monsterX, monsterY);
			monsterSprite->setPosition(monsterX + 25, monsterY + 25);
	}
}

int MonsterSpriteLayer::getMonsterNumber(){
	return monsterNumber;
}
/*������ײʱ���õĺ���*/
void MonsterSpriteLayer::onContact()
{
	this->monsterNumber--;
	_observer->onEventHappen(this, Contact);
}

/*��ӹ۲���*/
void MonsterSpriteLayer::addObserver(Observer * observer)
{
	_observer = observer;
}

void MonsterSpriteLayer::update(float dt){

	if (this->monsterNumber == 0)
	{
		this->unscheduleUpdate();
		_observer->onEventHappen(this, NoMonster);

		
	}
}