#include "zel_api.h"
#include "../include/example_movement.h"

#define ZEL_MAX_ENTITIES 0xFFFE

zel_entity_id first_entity;
zel_level_t* active_level;

// Called before the very first frame of the application.
void zel_initialization()
{
	zel_print("Hello World\n");

	zel_level_t* example_level = zel_level_create("Example Level");
	active_level = example_level;
	
	zel_level_register_component<zel_transform_t>(active_level);
	zel_transform_t transform{ { 0.0f,0.0f,0.0f },{ 0.0f,0.0f,0.0f },{ 1.0f,1.0f,1.0f } };

	zel_entity_id entity = zel_level_create_entity(active_level);
	zel_level_add_component(active_level, entity, transform);

	zel_level_register_system(active_level, example_movement_update, example_movement_name);
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
	zel_print("Shutting down...");
}