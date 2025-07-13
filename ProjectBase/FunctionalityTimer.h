#pragma once
#include <chrono>
#include <iostream>

class FunctionalityTimer {
public:
	FunctionalityTimer() : startTime(std::chrono::high_resolution_clock::now()) { }
	~FunctionalityTimer() {
		auto stop = std::chrono::high_resolution_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - startTime);
		std::cout << "Time elapsed: " << elapsedTime.count() << " Microseconds" << std::endl;
	}

private:
	std::chrono::steady_clock::time_point startTime;
};