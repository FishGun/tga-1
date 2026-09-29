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
	const int globalTypesSize = static_cast<int>(GenerationTypes::CountOrUntyped);
	const int globalEasyMagnitude = 1;
	const int globalMediumMagnitude = 3;
	const int globalHardMagnitude = 5;

	struct GenerationData
	{
		const GenerationTypes eventType;
		const int magnitude;
		//const std::string name;
	};
}