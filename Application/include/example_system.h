#pragma once
#include <zel_api.h>
#include <zel_math.h>

const char* example_system_name = "example_system";

void example_system_update(zel_level_t* level, float delta_time)
{
	for (zel_entity_id entity : zel_entities_list<zel_transform_t>(level))
	{
		zel_level_get_component<zel_transform_t>(level, entity)->position.x += 1;
		//zel_print("New transform X position | entity [%d]: %0.1f\n", entity, zel_level_get_component<zel_transform_t>(level, entity)->position.x);
	}
}