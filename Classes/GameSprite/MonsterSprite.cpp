#include "MonsterSprite.h"

MonsterSprite::MonsterSprite()
{
}

MonsterSprite::~MonsterSprite()
{
}

Action * MonsterSprite::runAction(Action * action)
{
	return getSprite()->runAction(action);
}
