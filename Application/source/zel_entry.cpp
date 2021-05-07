#include "zel_api.h"
#include "../include/example_system.h"

//TODO game version going up when hitting build

#define ZEL_MAX_ENTITIES 0xFFFE //TODO fix this!!

zel_level_t* active_level;

// Called before the very first frame of the application.
void zel_initialization()
{
	PROFILE_FUNCTION();

	// Main Initialization
	zel_io_initialization();
	zel_resources_init();

	// Level Initialization - TODO: put this somewhere else (Level manager?)
	zel_print("Hello World\n");
}

// Called every frame. Put your logic here.
void zel_logic(float delta_time)
{
	PROFILE_FUNCTION();

	for (std::pair<std::string, zel_system_t> system : active_level->systems)
	{
		system.second(active_level, delta_time);
	}
}

// Called every frame. Put your render code here.
void zel_render()
{
	PROFILE_FUNCTION();

	zel_clear_screen(0.03f, 0.07f, 0.21f, 1.0f);
}

// Called when the user wants to close the application
void zel_termination()
{
	zel_level_destroy(active_level);

	zel_print("Shutting down...");
}