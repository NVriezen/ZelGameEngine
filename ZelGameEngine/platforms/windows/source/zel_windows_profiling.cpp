#include <zel_profiling.h>
#include <fstream>
#include <algorithm>
#include <string>

std::ofstream output_stream;
uint32_t profile_count;

void zel_profiling_begin(const char* name, const char* filepath)
{
#ifdef PROFILING
	output_stream.open(filepath);
	output_stream << "{\"otherData\": {},\"traceEvents\":[";
	output_stream.flush();
	profile_count = 0;
#endif // PROFILING
}

void zel_profiling_end()
{
#ifdef PROFILING
	output_stream << "]}";
	output_stream.flush();

	output_stream.close();
	profile_count = 0;
#endif // PROFILING
}

void zel_profiling_write(const profile_result result)
{
#ifdef PROFILING
	if (profile_count > 0)
		output_stream << ",";

	++profile_count;

	std::string name = result.name;
	std::replace(name.begin(), name.end(), '"', '\'');

	output_stream << "{";
	output_stream << "\"cat\":\"function\",";
	output_stream << "\"dur\":" << (result.end - result.start) << ',';
	output_stream << "\"name\":\"" << name << "\",";
	output_stream << "\"ph\":\"X\",";
	output_stream << "\"pid\":0,";
	output_stream << "\"tid\":" << result.thread_id << ",";
	output_stream << "\"ts\":" << result.start;
	output_stream << "}";

	output_stream.flush();
#endif // PROFILING
}