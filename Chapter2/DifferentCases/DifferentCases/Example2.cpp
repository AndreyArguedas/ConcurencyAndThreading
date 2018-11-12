#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <thread>

char *  getCurrentTime() {
	time_t _tm = time(NULL);
	struct tm * curtime = localtime(&_tm);
	return asctime(curtime);
}

struct func {
	int & i;

	func(int& i_) :i(i_) {}

	void operator()() {

		time_t start, end;

		double diff;

		time(&start); 
		
		std::cout << "Started at " << getCurrentTime() << '\n';

		for (unsigned j = 0; j < 100000000; ++j) { i += j; }

		time(&end);

		diff = difftime(end, start);

		std::cout << "Finished, total value : " << i << '\n' <<"Finished at: " << getCurrentTime() << '\n';

		std::cout << "Total duration: " << diff << " seconds" << '\n';
	}
};

void oops() {
	int some_local_state = 0;
	func my_func(some_local_state);

	std::thread my_thread(my_func);
	std::cout << my_func.i << std::endl;
	//Case 1: Does not wait for the thread to end, value of i changes after oops finishes

	//my_thread.detach();  //Does not wait for the thread to end (finishes before operator()())

	//Case 2: Waits for the thread to end, value of i wont be finished after oops finishes
	
	my_thread.join();  

	std::cout << my_func.i << std::endl;
}

/*
	This function is to visualize that a thread could throw an error while is executing
	that is why is good to use try/cath before the thread finishes
*/

void f() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	try {
		std::cout<<"Doing something while thread 't' runs " << std::endl;
	}
	catch (...) {
		t.join();
		throw;
	}

	t.join();

	std::cout << my_func.i << std::endl;
}

/*
	Another way to make safer threads is to override the destructor function
*/

class thread_guard {
	std::thread& t;
public:

	explicit thread_guard(std::thread& t_) : t(t_){}
	
	~thread_guard(){
		if (t.joinable()) { //This is important because join can only be called once
			t.join();
			std::cout << "Thread deleted with destructor function " << std::endl;
		}
	}

	thread_guard(thread_guard const&) = delete; //Copy constructor deletes to execute the destuctor function of thread_guard
	thread_guard& operator=(thread_guard const&) = delete;
};

void thread_guarding() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	std::cout << "Doing something while thread 't' runs " << std::endl;
}

int main() {
	//oops();
	f();
	//thread_guarding();
	std::cin.get();
	return 0;
}