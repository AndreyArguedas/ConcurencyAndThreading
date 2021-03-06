#include <functional>
#include <ctime>
#include <random>
#include "SortingThreaderDistributor.h"

vector<unsigned long> numbers;

const unsigned long maxRange = 1e7;

/* Seed */
std::random_device rd;

/* Random number generator */
std::default_random_engine generator(rd());

/* Distribution on which to apply the generator */
std::uniform_int_distribution<long long unsigned> distribution(0, 0xFFFFFFFFFFFFFFFF);

void insertRandomNumber(long number) {
	numbers.push_back(distribution(generator) % maxRange);
}

int main() {

	vector<long> v(maxRange);

	for_each(v.begin(), v.end(), insertRandomNumber);

	/*time_t start, end;

	double diff;

	time(&start);

	std::sort(numbers.begin(), numbers.end());

	time(&end);

	diff = difftime(end, start);

	cout << "Duration in sorting with 1 thread : " << diff << " seconds" << endl;*/

	SortingThreaderDistributor().SortCollectionWithThreads(numbers, 4);



	cin.get();

	return 0;
}