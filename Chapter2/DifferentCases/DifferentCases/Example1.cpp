#include <iostream>
#include<thread>

void do_something()
{
	std::cout << "Doing something \n";
}

void do_something_else()
{
	std::cout << "Doing something else \n";
}

class background_task
{
public:
	void operator()() const
	{
		do_something();
		do_something_else();
	}
};

int main() {

	//Case 1

	/* 
	background_task f;
	std::thread my_thread(f);
	my_thread.join();  //Join makes the "main thread" waits to the "t" thread finishes, without this error is cause
	*/

	//Case 2
	
	/* 

	//declares a function my_thread that takes a single parameter (of type pointer to a function
	//taking no parameters and returning a background_task object) and returns a
	//std::thread object, rather than launching a new thread.

	std::thread my_thread(background_task());

	*/

	// Case 3 -> Avoiding case 2

	/*

	std::thread my_thread((background_task()));
	//std::thread my_thread{ background_task() }; // This way also works but I prefer the oter
	my_thread.join();  //Join makes the "main thread" waits to the "t" thread finishes, without this error is cause
	*/

	//Case 4 -> Using lambda Expression

	std::thread my_thread([] { do_something(); do_something_else(); });
	my_thread.join();  //Join makes the "main thread" waits to the "t" thread finishes, without this error is cause

	std::cin.get();
	return 0;
}



