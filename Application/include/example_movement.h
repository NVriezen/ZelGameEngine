#pragma once
#include <zel_api.h>

const char* example_movement_name = "example_movement_system";

void example_movement_update(zel_level_t* level, float delta_time)
{
	//std::vector<zel_transform_t>* transforms = zel_level_get_all_components<zel_transform_t>(level);
	//for (size_t i = 0; i < transforms->size(); i++)
	//{
	//	(*transforms)[i].position.x += 1;
	//	zel_print("New transform X position: %0.1f\n", (*transforms)[i].position.x);
	//}

	//auto list = zel_entities_list<zel_transform_t>(level);
	//auto it = list.begin();
	//while (it != list.end())
	//{
	//	zel_level_get_component<zel_transform_t>(level, *it)->position.x += 1;
	//	//zel_print("New transform X position | entity [%d]: %0.1f\n", *it, zel_level_get_component<zel_transform_t>(level, *it)->position.x);
	//	++it;
	//}

	//{
	//	PROFILE_SCOPE("Movement Example Speed Test");

		for (zel_entity_id entity : zel_entities_list<zel_transform_t>(level))
		{
			zel_level_get_component<zel_transform_t>(level, entity)->position.x += 1;
			//zel_print("New transform X position | entity [%d]: %0.1f\n", entity, zel_level_get_component<zel_transform_t>(level, entity)->position.x);
		}
	//}

	//zel_print("has all components?: %d\n", zel_level_has_components<zel_transform_t, zel_transform_t>(level, ZEL_CREATE_ID(1, 1)));
}