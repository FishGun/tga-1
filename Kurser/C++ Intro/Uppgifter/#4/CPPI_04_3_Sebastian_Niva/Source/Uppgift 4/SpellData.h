#pragma once
#include "EntityData.h"
#include <vector>

namespace SpellData
{
	enum class SpellTypes
	{
		Power1,
		Power2,
		Shield1,
		Shield2,
		Berserker,
		Reduce,
		CountOrRandom
	};
	const int SPELL_TYPES_SIZE = static_cast<int>(SpellTypes::CountOrRandom);


	struct SpellInstanceData
	{
		EntityData::BaseData baseModifiers { 0 };
		EntityData::DerivedData derivedModifiers {0};
		int roundDuration;
	};

	struct ActivatedSpell
	{
		const SpellInstanceData* data;
		int roundAquisition;
	};

	extern SpellInstanceData globalSpellDataCollection[];
	extern bool globalSpellDataCollectedAtIndex[];

	const SpellInstanceData& GetSpellData(SpellTypes aType);
	SpellInstanceData& CreateNewSpellData(SpellTypes aType);

	const ActivatedSpell& CreateNewSpellInstance(SpellInstanceData* aSpellData);
	std::vector<const SpellData::SpellInstanceData*> GenerateWeightedSpellVector(float aSpellLikelyhood, int aSpellMax);
}