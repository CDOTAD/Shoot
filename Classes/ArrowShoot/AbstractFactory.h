#pragma once
#ifndef _ABSTRACTFACTORY_H_	
#define _ABSTRACTFACTORY_H_

#include "MonsterProduct.h"
#include "ArrowProduct.h"
#include "SceneProduct.h"

class AbstractFactory {

public:
	AbstractFactory();
	virtual ~AbstractFactory();
	virtual SceneProduct* createSceneProduct();
	virtual MonsterProduct* createMonsterProduct();
	ArrowProduct* createArrowProduct();
};

class Factory1 : public AbstractFactory {

public:
	Factory1();
	~Factory1();
	SceneProduct* createSceneProduct();
	MonsterProduct* createMonsterProduct();
};

class Factory2 : public AbstractFactory {

public:
	Factory2();
	~Factory2();

	SceneProduct* createSceneProduct();
	MonsterProduct* createMonsterProduct();
};

class Factory3 : public AbstractFactory {

public:
	Factory3();
	~Factory3();

	SceneProduct* createSceneProduct();
	MonsterProduct* createMonsterProduct();
};

#endif  