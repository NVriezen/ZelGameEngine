#pragma once
#include <zel_api.h>
#include <zel_math.h>

const char* example_system_name = "example_system";

void example_system_update(zel_level_t* level, float delta_time)
{
	zel_component_collection<zel_transform_t> transform_collection = zel_component_collection_create<zel_transform_t>(level);
	for (size_t component_index = 1; component_index < transform_collection.length; component_index++)
	{
		zel_transform_t* transform = &(*transform_collection.first)[component_index];
		transform->position.x += 1;
		//zel_print("New transform X position | entity [%d]: %0.1f\n", transform_collection.entities[component_index], transform->position.x);
	}
}