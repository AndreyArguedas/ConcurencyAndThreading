#include <iostream>
#include <thread>
void hello()
{
	std::cout << "Hello Concurrent World\n";
}
int main()
{
	std::thread t(hello);
	t.join();  //Join makes the "main thread" waits to the "t" thread finishes
	std::cin.get();
	return 0;
}