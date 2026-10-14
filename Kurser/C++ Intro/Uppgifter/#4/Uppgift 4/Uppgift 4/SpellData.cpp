#include "SpellData.h"
#include "RandomController.h"

#include <assert.h>

namespace SpellData
{
	const SpellInstanceData& GetSpellData(SpellType aType)
	{
		if (aType == SpellType::CountOrRandom)
		{
			aType = static_cast<SpellType>(RandomController::GenerateNumber(0, static_cast<int>(SpellType::CountOrRandom) - 1));
		}
		const int index = static_cast<int>(aType);

		assert(index < SPELL_TYPE_SIZE && "Fatal Error: Attempted to get an item reference outside valid index");

		if (!globalSpellDataCollectedAtIndex[index])
		{
			globalSpellDataCollection[index] = CreateNewSpellData(aType);
			globalSpellDataCollectedAtIndex[index] = true;
		}
		return globalSpellDataCollection[index];
	}
	SpellInstanceData& CreateNewSpellData(SpellType aType)
	{
		switch (aType)
		{
			default:
				assert(false && "Fatal Error: A new item was attempted to be made without specifying its type");
			case SpellType::Power1: return *new SpellInstanceData
			{
				EntityData::BaseData
				{
					.name = "Power",
					.strength = 3,
					.physique = 1
				},
				EntityData::DerivedData
				{
					.attack = 5,
				},
				6
			};
			case SpellType::Power2: return *new SpellInstanceData
			{
				EntityData::BaseData
				{
					.name = "Condensed Power",
					.strength = 6,
					.physique = 2
				},
				EntityData::DerivedData
				{
					.attack = 10,
					.carryingCapacity = 2
				},
				3
			};
			case SpellType::Shield1: return *new SpellInstanceData
			{
				EntityData::BaseData
				{
					.name = "Shield",
					.dexterity = 3,
					.physique = 1
				},
				EntityData::DerivedData
				{
					.defense = 5,
				},
				6
			};
			case SpellType::Shield2: return *new SpellInstanceData
			{
				EntityData::BaseData
				{
					.name = "Condensed Shield",
					.dexterity = 6,
					.physique = 2
				},
				EntityData::DerivedData
				{
					.defense = 10,
					.hitPointMax = 20
				},
				3
			};
			case SpellType::Berserker: return *new SpellInstanceData
			{
				EntityData::BaseData
				{
					.name = "Berserker",
					.strength = 3,
					.dexterity = 3,
					.physique = 3
				},
				EntityData::DerivedData
				{
					.attack = 10,
					.defense = -30
				},
				5
			};
			case SpellType::Reduce: return *new SpellInstanceData
			{
				EntityData::BaseData
				{
					.name = "Reduce",
					.strength = -2,
					.dexterity = 5,
					.physique = -2
				},
				EntityData::DerivedData
				{
					.attack = -2,
					.defense = 20,
					.carryingCapacity = -4,
					.hitPointMax = -5
				},
				5
			};
		}
	}

	const ActivatedSpell& CreateNewActivatedSpell(SpellInstanceData* aSpellData, int currentRound)
	{
		return *new ActivatedSpell(aSpellData, currentRound);
	}
	std::vector<const SpellData::SpellInstanceData*> GenerateWeightedSpellVector(float aSpellLikelyhood, int aSpellMax)
	{
		std::vector<const SpellInstanceData*> toReturn;
		toReturn.reserve(aSpellMax);
		const int spellLikelyhoodWeight = static_cast<int>(1.0f / aSpellLikelyhood);
		for (int i = 0; i < aSpellMax; i++)
		{
			if (RandomController::GenerateNumber(1, spellLikelyhoodWeight) <= 1)
			{
				toReturn.push_back(&GetSpellData(SpellType::CountOrRandom));
			}
		}
		return toReturn;
	}

	SpellInstanceData globalSpellDataCollection[SPELL_TYPE_SIZE];
	bool globalSpellDataCollectedAtIndex[SPELL_TYPE_SIZE] = { false };
}