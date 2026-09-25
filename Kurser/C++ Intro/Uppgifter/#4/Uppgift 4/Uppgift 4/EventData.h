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
		Count
	};
	const int typesSize = static_cast<int>(GenerationTypes::Count);
	const int easyMagnitude = 1;
	const int mediumMagnitude = 3;
	const int hardMagnitude = 5;

	struct GenerationData
	{
		const GenerationTypes eventType;
		const int magnitude;
		//const std::string name;
	};
}