#include <iostream>
#include<thread>

struct func
{
	int & i;

	func(int& i_) :i(i_) {}

	void operator()()
	{
		for (unsigned j = 0; j < 1000000; ++j)
		{
			i += j;
		}
		std::cout << "Finished" << i << std::endl;
	}
};

void oops()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::cout << my_func.i << std::endl;
	std::thread my_thread(my_func);
	std::cout << my_func.i << std::endl;
	//Case 1: Does not wait for the thread to end, value of i changes after oops finishes

	//my_thread.detach();  //Does not wait for the thread to end (finishes before operator()())

	//Case 2: Waits for the thread to end, value of i wont be finished after oops finishes
	
	my_thread.join();  

	std::cout << my_func.i << std::endl;
}

int main() {
	oops();
	std::cin.get();
	return 0;
}