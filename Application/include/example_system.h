#pragma once
#include <zel_api.h>
#include <zel_math.h>

const char* example_system_name = "example_system";

struct player_t { };

void example_system_update(zel_level_t* level, float delta_time)
{
	for (zel_entity_id entity : zel_entities_list<player_t>(level))
	{
		zel_transform_t* player_transform = zel_level_get_component<zel_transform_t>(level, entity);

		int state = zel_input_get_key_hold(ZEL_KEY_A);
		if (state)
		{
			player_transform->position.x -= delta_time;
		}

		state = zel_input_get_key_hold(ZEL_KEY_D);
		if (state)
		{
			player_transform->position.x += delta_time;
		}

		zel_print("Player is position: { %f, %f, %f }\n", player_transform->position.x, player_transform->position.y, player_transform->position.z);


		int state = zel_input_get_key_press(ZEL_KEY_A);
		if (state)
		{
			zel_print("Key A is pressed");
		}
	}
}