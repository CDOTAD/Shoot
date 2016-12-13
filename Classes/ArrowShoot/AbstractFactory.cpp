#include "AbstractFactory.h"

AbstractFactory::AbstractFactory() {}
AbstractFactory::~AbstractFactory() {}

SceneProduct* AbstractFactory::createSceneProduct() {
	SceneProduct* temp = NULL;
	temp = new SceneProduct();
	return temp;
}

MonsterProduct * AbstractFactory::createMonsterProduct()
{
	return nullptr;
}

Factory1::Factory1() {}
Factory1::~Factory1() {}

ArrowProduct* AbstractFactory::createArrowProduct() {
	ArrowProduct* temp = NULL;
	temp = new Arrow();
	return temp;
}

MonsterProduct* Factory1::createMonsterProduct() {
	MonsterProduct* temp = NULL;
	temp = new Monster1();
	return temp;
}

SceneProduct* Factory1::createSceneProduct() {
	SceneProduct* temp = NULL;
	temp = new Scene1();
	return temp;
}


Factory2::Factory2()
{
}

Factory2::~Factory2()
{
}

SceneProduct* Factory2::createSceneProduct() {
	SceneProduct* temp = NULL;
	temp = new Scene2();
	return temp;
}

MonsterProduct* Factory2::createMonsterProduct() {
	MonsterProduct* temp = NULL;
	temp = new Monster2();
	return temp;
}


MonsterProduct* Factory3::createMonsterProduct() {
	MonsterProduct* temp = NULL;
	temp = new Monster3();
	return temp;
}
Factory3::Factory3()
{
}
Factory3::~Factory3()
{
}
SceneProduct* Factory3::createSceneProduct() {
	SceneProduct* temp = NULL;
	temp = new Scene3();
	return temp;
}