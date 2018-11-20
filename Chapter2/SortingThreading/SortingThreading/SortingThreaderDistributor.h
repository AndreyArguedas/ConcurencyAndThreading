#include <vector>
#include <algorithm>
#include <iostream>
#include <thread>
#include <iostream>
#include <iterator>
#include <memory>

using namespace std;

#pragma once

class SortingThreaderDistributor {

public:

	static void SortCollectionWithThreads(std::vector<unsigned long>, long);

	static void sorting(std::vector<unsigned long> *);
};
