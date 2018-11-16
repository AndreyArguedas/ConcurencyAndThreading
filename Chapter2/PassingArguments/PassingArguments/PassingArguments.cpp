#include <string>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

void f(int i, std::string const& s) {
	std::cout << "Integer is : " << i << std::endl << "String is: " << s << std::endl;
}

void do_something()
{
	std::cout << "Doing something \n";
}

void do_something_else()
{
	std::cout << "Doing something else \n";
}

void do_work(unsigned i, std::string name) {
	time_t start, end;

	double diff;

	time(&start);


	for (unsigned j = 0; j < 1e2; ++j) { std::cout << name << i << std::endl; }

	time(&end);

	diff = difftime(end, start);

	std::cout << "Total duration: " << diff << " seconds" << '\n';
}

int main() {

	//Case 1: Passing arguments with 
	std::thread t(f, 3, "hello");
	t.detach();

	//Case 2: Moving from threads

	/*
	std::thread t1(do_something); // Starts new thread
	std::thread t2 = std::move(t1); //Ownership of 'do something' is passed to t2, t1 is now doing nothing
	t1 = std::thread(do_something_else); //T1 starts doing something else
	std::thread t3; //t3 is default constructed e, which means that it’s created without any associated thread of execution
	t3 = std::move(t2); //t3 is now in responsability of doing something
	*/

	/*Error expected in this next line*/
	//t1 = std::move(t3); //This terminates the program because t1 was in charge of doing_something_else

	
	
	/*Running threads and waiting them to finish*/
	
	std::vector<std::thread> threads;
	for (unsigned i = 0; i < 5; ++i)
	{
		threads.push_back(std::thread(do_work, i, "Thread # "));
	}

	/* All the threads will end, because of the join, but look at the prints they are colliding with each other
	   This is because they are running simoultaneosly and need to print at the same time
	*/
	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

	std::cin.get();
	return 0;
}