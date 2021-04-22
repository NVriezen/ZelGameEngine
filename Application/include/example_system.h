#pragma once
#include <zel_api.h>
#include <zel_math.h>

const char* example_system_name = "example_system";

float speed = 100;

void example_system_update(zel_level_t* level, float delta_time)
{
	for (zel_entity_id entity : zel_entities_list<zel_transform_t>(level))
	{
		zel_transform_t* transform = zel_level_get_component<zel_transform_t>(level, entity);
		
		//transform->rotation.x += speed * delta_time;
		transform->rotation.y += speed * delta_time;
		//transform->rotation.z += speed * delta_time;
	}
}