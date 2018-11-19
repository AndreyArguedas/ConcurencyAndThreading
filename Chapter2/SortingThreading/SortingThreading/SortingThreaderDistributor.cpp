#include "SortingThreaderDistributor.h"

void SortingThreaderDistributor::SortCollectionWithThreads(std::vector<unsigned long> elements, long threadsQuantity)
{
	unsigned long vectorDivision = elements.size() / threadsQuantity;
	unsigned long index = 0;

	std::vector<std::vector<unsigned long>> subVectors(threadsQuantity, std::vector<unsigned long>(vectorDivision));

	for (auto & subVec : subVectors) {
		
		std::copy_if(elements.begin(), elements.end(), subVec.begin(), [index, vectorDivision](unsigned long i) { return i > index && i <= index + vectorDivision; });

		index += vectorDivision;

	}
	
	for (auto n : subVectors[1]) {
		std::cout << n << " ";
	}
	
}
