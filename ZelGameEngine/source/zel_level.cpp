#include <zel_level.h>

zel_level_t* zel_level_create(const char* level_name)
{
	zel_level_t* new_level = new zel_level_t;
	new_level->level_name = level_name;
	//Add level to level manager/array

	return new_level;
}

void zel_level_destroy(zel_level_t* level)
{
	std::unordered_map<std::string, ZelComponentBase*>::iterator level_components_iterator = level->components.begin();
	while (level_components_iterator != level->components.end())
	{
		level_components_iterator->second->free();
		delete level_components_iterator->second;

		++level_components_iterator;
	}

	delete level;
}

zel_entity_id zel_level_create_entity(zel_level_t* level)
{
	if (!level->empty_entities_spots.empty())
	{
		uint32_t empty_spot = level->empty_entities_spots.front();
		level->empty_entities_spots.pop();
		level->entities[empty_spot] += 1;
		zel_entity_id new_entity = ZEL_CREATE_ID(level->entities[empty_spot], empty_spot);
		return new_entity;
	}

	level->entities.push_back(1);
	return ZEL_CREATE_ID(1, level->entities.size() - 1);
}

void zel_level_destroy_entity(zel_level_t* level, zel_entity_id entity)
{
	uint32_t entity_index = ZEL_GET_INDEX(entity);
	level->entities[entity_index] += 1;
	level->empty_entities_spots.push(entity_index);

	std::unordered_map<std::string, ZelComponentBase*>::iterator level_components_iterator = level->components.begin();
	while (level_components_iterator != level->components.end())
	{
		level_components_iterator->second->destroy(entity);

		++level_components_iterator;
	}
}

void zel_level_register_system(zel_level_t* level, zel_system_t system_update, const char* system_name)
{
	level->systems.insert({ system_name, system_update });
}

void zel_level_unregister_system(zel_level_t* level, const char* system_name)
{
	level->systems.erase(system_name);
}
