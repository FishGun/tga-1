#pragma once
#include "Entity.h"

class Enemy
{
public:
	Enemy(Entity aEntity);

	Entity& GetEntity();

private:
	Entity myEntityClass;
};