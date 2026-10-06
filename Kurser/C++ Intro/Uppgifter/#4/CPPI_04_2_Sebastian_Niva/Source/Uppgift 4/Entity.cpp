#include "Entity.h"
#include "InputController.h"
#include "DisplayManager.h"

Entity::Entity(EntityData::BaseData aBaseData) : myBaseData(aBaseData)
{
	myActiveSpells.clear();
	myHitPoints = GetMaxHP();
}

int Entity::DamageCalculator(int aAttackValue, int aDefenseValue)
{
	int toReturn = aAttackValue - (aDefenseValue / EntityData::DEFENSE_DIVIDER);
	if (toReturn < 0)
	{
		toReturn = 0;
	}
	return toReturn;
}

const EntityData::BaseData& Entity::GetUnmodifiedBaseStats() const
{
	return myBaseData;
}
const int Entity::GetStrength() const
{
	return myBaseData.strength + GetStrMod();
}
const int Entity::GetDexterity() const
{
	return myBaseData.dexterity + GetDexMod();
}
const int Entity::GetPhysique() const
{
	return myBaseData.physique + GetPhyMod();
}
const int Entity::GetAttack() const
{
	return GetStrength() * GetDexterity() + GetAttMod();
}
const int Entity::GetMaxHP() const
{
	return GetPhysique() * 4 + GetStrength() * 6 + GetDexterity() * 3 + GetMaxHPMod();
}
const int Entity::GetCarryingCapacity() const
{
	return GetStrength() + GetDexterity() / 3 + GetCarMod();
}
const int Entity::GetDefense() const
{
	return GetPhysique() * GetDexterity() + GetDefMod();
}
const int Entity::GetHP() const
{
	return myHitPoints;
}
const bool Entity::IsDead() const
{
	return myHitPoints <= 0;
}
const char* Entity::GetName() const
{
	return myBaseData.name;
}
const char* Entity::SetName()
{
	InputController::AskForName(myBaseData.name, EntityData::MIN_NAME_LENGTH, EntityData::MAX_NAME_LENGTH - 1);
	return myBaseData.name;
}

const int Entity::GetStrMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItemData.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItemData.at(i)->baseModifiers.strength;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->baseModifiers.strength;
	}
	return total;
}
const int Entity::GetDexMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItemData.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItemData.at(i)->baseModifiers.dexterity;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->baseModifiers.dexterity;
	}
	return total;
}
const int Entity::GetPhyMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItemData.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItemData.at(i)->baseModifiers.physique;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->baseModifiers.physique;
	}
	return total;
}
const int Entity::GetAttMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItemData.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItemData.at(i)->derivedModifiers.attack;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->derivedModifiers.attack;
	}
	return total;
}
const int Entity::GetMaxHPMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItemData.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItemData.at(i)->derivedModifiers.hitPointMax;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->derivedModifiers.hitPointMax;
	}
	return total;
}
const int Entity::GetCarMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItemData.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItemData.at(i)->derivedModifiers.carryingCapacity;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->derivedModifiers.carryingCapacity;
	}
	return total;
}
const int Entity::GetDefMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItemData.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItemData.at(i)->derivedModifiers.defense;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->derivedModifiers.defense;
	}
	return total;
}

bool Entity::TryAddItem(const ItemData::ItemInstanceData* aItemDataPointer, const bool aShouldCallout)
{
	if (GetCarryingCapacity() > static_cast<int>(myItemData.size()))
	{
		myItemData.push_back(aItemDataPointer);
		myHitPoints += aItemDataPointer->derivedModifiers.hitPointMax;
		if (aShouldCallout)
		{
			DisplayManager::ItemPickupCallout(*this, *aItemDataPointer);
		}
		return true;
	}
	else
	{
		if (aShouldCallout)
		{
			DisplayManager::ItemPickupFailedCallout(*this);
		}
		return false;
	}
}
void Entity::ActivateSpell(const SpellData::SpellInstanceData* aSpellDataPointer, int aRound)
{
	myActiveSpells.push_back(SpellData::ActivatedSpell(aSpellDataPointer, aRound));
}
void Entity::CleanSpells(int aRound)
{
	int spellCount = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellCount; i++)
	{
		const SpellData::ActivatedSpell& spell = myActiveSpells.at(i);
		const int endRound = spell.roundAquisition + spell.data->roundDuration;
		if (endRound <= aRound)
		{
			myActiveSpells.erase(myActiveSpells.begin() + i);
			DisplayManager::SpellEndCallout(*spell.data);
			i--;
			spellCount--;
		}
	}
}

void Entity::TakeDamage(int aValue)
{
	const int maxHP = GetMaxHP();
	myHitPoints -= DamageCalculator(aValue, GetDefense());
	if (myHitPoints > maxHP)
	{
		myHitPoints = maxHP;
	}
	else if (myHitPoints < 0)
	{
		myHitPoints = 0;
	}
}
void Entity::Heal(int aValue)
{
	const int maxHP = GetMaxHP();
	myHitPoints += aValue;
	if (myHitPoints > maxHP)
	{
		myHitPoints = maxHP;
	}
	else if (myHitPoints < 0)
	{
		myHitPoints = 0;
	}
}

const int Entity::ChangeStat(EntityData::BaseStatsEnum aBaseStat, int aValue)
{
	switch (aBaseStat)
	{
	case EntityData::BaseStatsEnum::Strength:
		myBaseData.strength += aValue;
		break;
	case EntityData::BaseStatsEnum::Dexterity:
		myBaseData.dexterity += aValue;
		break;
	case EntityData::BaseStatsEnum::Physique:
		myBaseData.physique += aValue;
		break;
	case EntityData::BaseStatsEnum::Length:
	default:
		return 0;
	}
	return aValue;
}

Entity& Entity::operator += (int rValue)
{
	this->myHitPoints += rValue;
	return *this;
}