#pragma once
#include "Enemy.h"

namespace EventData
{
	enum class GenerationTypes
	{
		Random,
		EasyCombat,
		MediumCombat,
		HardCombat,
		CountOrUntyped
	};
	const int TYPES_SIZE = static_cast<int>(GenerationTypes::CountOrUntyped);
	const int EASY_MAGNITUDE = 1;
	const int MEDIUM_MAGNITUDE = 3;
	const int HARD_MAGNITUDE = 5;

	struct GenerationData
	{
		const GenerationTypes eventType;
		const int magnitude;
	};
}