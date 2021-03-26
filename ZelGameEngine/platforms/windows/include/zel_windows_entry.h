#pragma once
#include <zel_application.h>
#include <zel_window.h>
#include <zel_platform_utils.h>
#include <zel_engine_settings.h>

int main()
{
	ZEL_PROFILING_BEGIN_SESSION("Window_Creation", "window_creation_profile.json");
	zel_window_t window = nullptr;
	uint8_t error_code = zel_window_create(&window);
	if (error_code) return 1;
	ZEL_PROFILING_END_SESSION();

	zel_initialization();

	double total_time = zel_get_time(); // in micro seconds or nano seconds
	double previous_timestamp = total_time;
	float delta_time = 0;
	ZEL_PROFILING_BEGIN_SESSION("Runtime", "runtime_profile.json");
	while (!zel_engine_running)
	{
		PROFILE_SCOPE("Main Loop");

		previous_timestamp = total_time;
		total_time = zel_get_time();
		delta_time = (float)(total_time - previous_timestamp);

		//input checking

		// run game code
		zel_logic(delta_time);
		zel_render();

		zel_window_update(window);
	}
	ZEL_PROFILING_END_SESSION();

	zel_termination();

	zel_window_destroy(window);
	zel_window_terminate();
	return 0;
}

#if NDEBUG
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	main();
}
#endif