#pragma once
#include <zel_base.h>
#include <zel_ecs.h>
#include <zel_level.h>
#include <zel_component_base.h>
#include <zel_component_class.h>
#include <vector>
#include <string>

template <typename T>
std::vector<zel_entity_id> zel_entity_collection_create_single(zel_level_t* level)
{
	std::type_index component_type = std::type_index(typeid(T));
	zel_generational_ptr* component_to_entity = level->components[component_type]->component_to_entity;
	zel_generational_ptr* entity_to_component = level->components[component_type]->entity_to_component;
	uint32_t components_amount = level->components[component_type]->total_components();

	std::vector<zel_entity_id> collection;
	for (size_t component_index = 1; component_index < components_amount + 1; component_index++)
	{
		zel_ecs_id entity_id = component_to_entity[component_index].id;
		if (entity_id == 0)
			continue;

		zel_index entity_index = ZEL_GET_INDEX(entity_id);
		zel_generation entity_generation = ZEL_GET_GENERATION(entity_id);
		if (entity_generation == entity_to_component[entity_index].generation)
		{
			collection.push_back(entity_id);
		}
	}

	return collection;
}

template <typename A, typename... T>
std::vector<zel_entity_id> zel_entity_collection_create(zel_level_t* level)
{
	std::vector<zel_entity_id> collection;
	uint32_t total_entities = level->entities.size();
	bool* entity_map = new bool[total_entities] { false };

	std::type_index component_types[] = { std::type_index(typeid(A)), std::type_index(typeid(T))... };
	uint32_t types_size = sizeof...(T)+1;
	uint32_t lowest_amount_components = -1;
	uint8_t index = 0;
	for (uint8_t i = 0; i < types_size; i++)
	{
		uint32_t amount = level->components[component_types[i]]->total_components();
		if (amount < lowest_amount_components)
		{
			lowest_amount_components = amount;
			index = i;
		}
	}

	zel_generational_ptr* component_to_entity = level->components[component_types[index]]->component_to_entity;
	zel_generational_ptr* entity_to_component = level->components[component_types[index]]->entity_to_component;
	for (size_t component_index = 1; component_index < lowest_amount_components + 1; component_index++)
	{
		zel_ecs_id entity_id = component_to_entity[component_index].id;
		if (entity_id == 0)
			continue;

		zel_index entity_index = ZEL_GET_INDEX(entity_id);
		if (!entity_map[entity_index])
		{
			zel_generation entity_generation = ZEL_GET_GENERATION(entity_id);
			if (entity_generation == entity_to_component[entity_index].generation)
			{
				collection.push_back(entity_id);
				entity_map[entity_index] = true;
			}
		}
	}

	delete[] entity_map;
	return collection;
}