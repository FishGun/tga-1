#include "RandomController.h"
#include <random>

const int RandomController::GenerateNumber(int minValue, int maxValue)
{
	static std::random_device randomDevice;
	static std::mt19937 rng(randomDevice());
	std::uniform_int_distribution<std::mt19937::result_type> randomDistribution(minValue, maxValue);
	return randomDistribution(rng);
}