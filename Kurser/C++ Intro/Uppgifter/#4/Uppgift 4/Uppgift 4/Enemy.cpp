#include "Enemy.h"

Enemy::Enemy(Entity aEntity) : myEntityClass(aEntity) {}

Entity& Enemy::GetEntity()
{
	return myEntityClass;
}