#pragma once
#include <zel_api.h>
#include <zel_math.h>

const char* example_system_name = "example_system";

float speed = 100;

void example_system_update(zel_level_t* level, float delta_time)
{
	for (zel_entity_id entity : zel_entities_list<zel_transform_t>(level))
	{
		int state = zel_input_get_key_press(ZEL_KEY_A);
		if (state)
		{
			zel_print("Button A is pressed");
		}

		state = zel_input_get_key_release(ZEL_KEY_A);
		if (state)
		{
			zel_print("Button A is released");
		}

		//state = zel_input_get_key_hold(ZEL_KEY_A);
		//if (state)
		//{
		//	zel_print("Holding A");
		//}
	}
}