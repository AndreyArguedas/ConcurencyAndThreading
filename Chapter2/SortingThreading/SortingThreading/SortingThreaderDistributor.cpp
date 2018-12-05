#include "SortingThreaderDistributor.h"

void SortingThreaderDistributor::SortCollectionWithThreads(std::vector<unsigned long> elements, long threadsQuantity)
{
	unsigned long vectorDivision = elements.size() / threadsQuantity;
	unsigned long index = 0;

	std::vector<std::vector<unsigned long>> subVectors(threadsQuantity, std::vector<unsigned long>(elements.size()));

	for (auto & subVec : subVectors) {
		
		std::copy_if(elements.begin(), elements.end(), subVec.begin(), [index, vectorDivision](unsigned long i) { return i > index && i <= index + vectorDivision; });

		index += vectorDivision;

		subVec.erase(std::remove(subVec.begin(), subVec.end(), 0), subVec.end()); //Delete every 0 in the vector

	}

	/* Create a vector of threads and define wich function will execute */

	std::vector<std::thread> threads;

	time_t start, end;

	double diff;

	time(&start);

	for (unsigned i = 0; i < threadsQuantity; i++) {
		threads.emplace_back(std::thread(SortingThreaderDistributor::sorting, &subVectors[i]));
	}

	for (auto & t : threads) {
		t.join();
	}

	time(&end);

	diff = difftime(end, start);

	cout << "Duration in sorting with "<< threadsQuantity << " threads: " << diff << " seconds" << endl;

	std::vector<unsigned long> elementsSorted;

	for (auto & subVec : subVectors) {

		elementsSorted.insert(elementsSorted.end(), subVec.begin(), subVec.end());
	}

	//for_each(elementsSorted.begin(), elementsSorted.end(), [](unsigned long i) -> void {cout << i << " "; });
}

void SortingThreaderDistributor::sorting(std::vector<unsigned long> *subVector) {
	std::sort(subVector->begin(), subVector->end());
}
