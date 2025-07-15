#pragma once
#include <chrono>
#include <string>
#include <vector>
#include <mutex>

class TraceEvent {
public:
	std::string name;
	uint64_t startUs;
	uint64_t durationUs;
	uint32_t tid;

	TraceEvent(std::string name, uint64_t start, uint64_t dur, uint32_t tid)
		: name(std::move(name)), startUs(start), durationUs(dur), tid(tid) {
	}
};

class Tracer {
public:
	static void Begin(const std::string& name);
	static void End();
	static void Export(const std::string& filePath);

private:
	static std::vector<TraceEvent> complete;
	static std::vector<TraceEvent> active;
	static std::mutex mutex;

	static uint64_t NowMicros();
	static uint32_t GetThreadId();
};