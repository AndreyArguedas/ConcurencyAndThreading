#include <vector>
#include <algorithm>
#include <functional>

#include "RandomGenerator.h"

using namespace std;

vector<int> numbers;

const int maxRange = 100;

void insertRandomNumber(int max) {
	numbers.push_back(RandomGenerator::randomNumber(max));
}


int main() {

	vector<int> v(maxRange);

	

	RandomGenerator::defineNewSeed();

	// fill the array with 10 five times 
	//v.assign(10, RandomGenerator::randomNumber(100));

	for_each(v.begin(), v.end(), bind(insertRandomNumber, maxRange));

	cout << "The vector elements are: ";
	cout << numbers.size();
	for (int i = 0; i < numbers.size(); i++)
		cout << numbers[i] << " ";


	cin.get();

	return 0;
}