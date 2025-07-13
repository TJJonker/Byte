#include <iostream>
#include "ThreadPool.h"


void Task1() {
	std::cout << "Completed Task One! \n";
}

void Task2() {
	std::cout << "Completed Task Two! \n";
}

ThreadPool<2> threadPool;

int main() {
	threadPool.Enqueue(Task1);
	threadPool.Enqueue(Task1);
	threadPool.Enqueue(Task2);
	threadPool.Enqueue(Task1);
	threadPool.Enqueue(Task1);
	threadPool.Enqueue(Task2);
	threadPool.Enqueue(Task1);
	threadPool.Enqueue(Task2);
	threadPool.Enqueue(Task1);


	while (threadPool.GetQueueSize() != 0)
		continue;

	std::cout << "Main thread finished" << std::endl;
	return 0;
}