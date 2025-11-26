#pragma once
#include <random>

namespace GameFr{
	class Randomizer{
		std::random_device rd;
		std::mt19937 gen;
		std::uniform_int_distribution<int> distrib;
	public:
		Randomizer(int min, int max);
		Randomizer(const Randomizer& other);
		void ChangeRange(int min, int max);
		int GetRandomNumber();
	};
}
