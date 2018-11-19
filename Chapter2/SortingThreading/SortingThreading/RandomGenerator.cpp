#include "RandomGenerator.h"

int RandomGenerator::randomNumber(int maxRange) {
	return  (rand() % maxRange) + 1;
}

void RandomGenerator::defineNewSeed()
{
	srand(time(NULL));
}
