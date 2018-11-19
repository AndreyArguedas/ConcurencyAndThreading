#include <iostream>
#include <ctime>

#pragma once

class RandomGenerator {

private:

	RandomGenerator() { }

public:

	static int randomNumber(int maxRange);

	static void defineNewSeed();

};