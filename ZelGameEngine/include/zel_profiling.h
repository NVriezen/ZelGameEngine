#pragma once
// Original source by The Cherno
// https://www.youtube.com/watch?v=xlAH4dbMVnU&t=925s

#include <zel_base.h>

struct profile_result
{
	const char* name;
	long long start, end;
	uint32_t thread_id;
};

#ifdef PROFILING 
#define ZEL_PROFILING_BEGIN_SESSION(name, filepath) zel_profiling_begin(name, filepath);
#define ZEL_PROFILING_END_SESSION() zel_profiling_end();
#else
#define ZEL_PROFILING_BEGIN_SESSION(name, filepath)
#define ZEL_PROFILING_END_SESSION()
#endif

void zel_profiling_begin(const char* name, const char* filepath = "profiling_result.json");
void zel_profiling_end();
void zel_profiling_write(const profile_result result);