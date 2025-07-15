#include <fstream>
#include "ByteCore/Modules/Tracer.h"

std::vector<TraceEvent> Tracer::complete = std::vector<TraceEvent>();
std::vector<TraceEvent> Tracer::active = std::vector<TraceEvent>();
std::mutex Tracer::mutex;

void Tracer::Begin(const std::string& name)
{
	auto now = NowMicros();
	std::lock_guard<std::mutex> lock(mutex);
	active.emplace_back(name, now, 0, GetThreadId());
}

void Tracer::End()
{
	auto now = NowMicros();
	std::lock_guard<std::mutex> lock(mutex);
	auto& event = active.back();
	event.durationUs = now - event.startUs;
	complete.push_back(event);
	active.pop_back();
}

void Tracer::Export(const std::string& filePath)
{
	std::ofstream out(filePath);
	out << "[\n";
	for (size_t i = 0; i < complete.size(); ++i) {
		const auto& e = complete[i];
		out << "  { \"name\": \"" << e.name
			<< "\", \"ph\": \"X\", \"ts\": " << e.startUs
			<< ", \"dur\": " << e.durationUs
			<< ", \"pid\": 0, \"tid\": " << e.tid << " }";
		if (i + 1 < complete.size()) out << ",";
		out << "\n";
	}
	out << "]\n";
}

uint64_t Tracer::NowMicros()
{
	auto now = std::chrono::high_resolution_clock::now();
	auto us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
	return us.count();
}

uint32_t Tracer::GetThreadId()
{
	std::hash<std::thread::id> hasher;
	return static_cast<uint32_t>(hasher(std::this_thread::get_id()));
}
