#pragma once
// Original source by The Cherno
// https://www.youtube.com/watch?v=xlAH4dbMVnU&t=925s

#include <zel_base.h>
#include <zel_profiling.h>
#include <chrono>
#include <thread>

#ifdef PROFILING 
#define PROFILE_SCOPE(name) ZelProfilingTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
#endif

class ZelProfilingTimer
{
public:
	ZelProfilingTimer(const char* name)
		: timer_name(name), is_stopped(false)
	{
		start_timepoint = std::chrono::high_resolution_clock::now();
	}

	~ZelProfilingTimer()
	{
		if (!is_stopped)
			stop();
	}

	void stop()
	{
		auto end_timepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(start_timepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch().count();

		uint32_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
		zel_profiling_write({ timer_name, start, end, thread_id });
		is_stopped = true;
	}

private:
	const char* timer_name;
	std::chrono::time_point<std::chrono::steady_clock> start_timepoint;
	bool is_stopped;
};