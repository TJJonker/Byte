#include "Tracer.h"
#include <iostream>

int main() {
	Tracer::Begin("SleepTask");
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	Tracer::End();

	Tracer::Begin("ComputeTask");
	for (int i = 0; i < 1000000; ++i); // dummy work
	Tracer::End();

	Tracer::Export("trace.json");

	std::cout << "Trace exported!" << std::endl;
}
