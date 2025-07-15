#pragma once
#include <mutex>
#include <queue>
#include <functional>
#include <array>

using MutexGuard = std::lock_guard<std::mutex>;
using VoidFunction = std::function<void()>;
using FunctionQueue = std::queue<VoidFunction>;



template <size_t N>
class ThreadPool {
public:
	ThreadPool() {
		for (auto& t : threads)
			t = std::thread(&ThreadPool::WorkerThread, this);
	}

	~ThreadPool() {
		running = false;
		checkQueue.notify_all();
		for (auto& t : threads)
			t.join();
	}

	void Enqueue(VoidFunction function) {
		MutexGuard lock(queueMutex);
		taskQueue.push(function);
		checkQueue.notify_all();
	}

	inline size_t GetQueueSize() { return taskQueue.size(); }

private:
	FunctionQueue taskQueue;
	std::condition_variable checkQueue;
	std::mutex queueMutex;
	std::atomic_bool running = true;
	std::array<std::thread, N> threads;

	void WorkerThread() {
		while (running) {
			std::function<void()> func;

			{
				std::unique_lock<std::mutex> lk(queueMutex);
				checkQueue.wait(lk, [this] { return !taskQueue.empty() || !running; });

				if (!running)
					return;

				func = taskQueue.front();
				taskQueue.pop();
			}

			func();
		}
	}
};