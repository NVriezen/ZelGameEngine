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

	zel_level_t* example_level = zel_level_create("Playtest Example Level");
	active_level = example_level;

	zel_level_register_component<zel_transform_t>(example_level);
	zel_level_register_component<player_t>(example_level);

	zel_entity_id player_entity = zel_level_create_entity(example_level);
	zel_entity_id enemy1_entity = zel_level_create_entity(example_level);
	zel_entity_id enemy2_entity = zel_level_create_entity(example_level);

	zel_transform_t player_transform;
	player_transform.position = {0, 128, 0};
	zel_level_add_component<zel_transform_t>(example_level, player_entity, player_transform);

	player_t player_tag;
	zel_level_add_component<player_t>(example_level, player_entity, player_tag);

	zel_transform_t enemy1_transform;
	enemy1_transform.position = { -64, 0, 0 };

	zel_transform_t enemy2_transform;
	enemy2_transform.position = { 64, 0, 0 };

	zel_level_add_component<zel_transform_t>(example_level, enemy1_entity, enemy1_transform);
	zel_level_add_component<zel_transform_t>(example_level, enemy2_entity, enemy2_transform);

	zel_level_register_system(example_level, example_system_update, example_system_name);
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