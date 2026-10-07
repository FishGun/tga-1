#pragma once
#include "EntityData.h"

class ItemType
{
public:
	ItemType() = delete;
	ItemType(const EntityData::BaseData aBaseModifiers, const EntityData::DerivedData aDerivedModifiers);

	const EntityData::BaseData& GetBaseData() const;
	const EntityData::DerivedData& GetDerivedData() const;

private:
	const EntityData::BaseData myBaseModifiers{ 0 };
	const EntityData::DerivedData myDerivedModifiers{ 0 };

public:
	static constexpr float ENEMY_KILLED_DROP_CHANCE = 0.25f;
	static constexpr float ROOM_DROP_SPAWN_CHANCE = 0.5f;
	static constexpr int ROOM_DROP_SPAWN_TRIES = 2;
	static constexpr float ROOM_CHEST_SPAWN_CHANCE = 0.34f;
	static constexpr float ROOM_SPELL_SPAWN_CHANCE = 0.5f;
};

