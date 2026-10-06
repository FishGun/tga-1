#pragma once
#include "EntityData.h"
#include "Item.h"
#include "SpellData.h"

#include <vector>

class Entity
{
public:
	Entity() = delete;
	Entity(EntityData::BaseData aBaseStats);

	static int DamageCalculator(int aAttackValue, int aDefenseValue);

	const EntityData::BaseData& GetUnmodifiedBaseStats() const;

	const int GetStrength() const;
	const int GetDexterity() const;
	const int GetPhysique() const;

	const int GetAttack() const;
	const int GetMaxHP() const;
	const int GetCarryingCapacity() const;
	const int GetDefense() const;
	const int GetHP() const;
	const bool IsDead() const;
	const char* GetName() const;
	const char* SetName();

	const int GetStrMod() const;
	const int GetDexMod() const;
	const int GetPhyMod() const;
	const int GetAttMod() const;
	const int GetMaxHPMod() const;
	const int GetCarMod() const;
	const int GetDefMod() const;

	const std::vector<const Item*>& GetItemVector() const;
	const std::vector<SpellData::ActivatedSpell>& GetSpellVector() const;

	bool TryAddItem(const Item* aItemDataPointer, const bool aShouldCallout = true);
	void ActivateSpell(const SpellData::SpellInstanceData* aSpellDataPointer, int aRound);
	void CleanSpells(int aRound);

	void TakeDamage(int aValue);
	void Heal(int aValue);
	const int ChangeStat(EntityData::BaseStatsEnum aBaseStat, int aValue);

	Entity& operator += (int rValue);
private:
	std::vector<const Item*> myItemData;
	std::vector<SpellData::ActivatedSpell> myActiveSpells;

	EntityData::BaseData myBaseData;
	int myHitPoints;
};