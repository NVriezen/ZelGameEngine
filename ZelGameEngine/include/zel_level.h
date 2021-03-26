#pragma once
#include <zel_base.h>
#include <zel_ecs.h>
#include <vector>
#include <zel_component_base.h>
#include <zel_component_class.h>
#include <unordered_map>
#include <queue>

typedef struct zel_level_t _zel_level_t;
typedef void(*zel_system_t)(_zel_level_t* level, float delta_time);

struct zel_level_t
{
	const char* level_name;

	////game state:
	//components
	std::unordered_map<std::string, ZelComponentBase*> components;

	//systems
	std::unordered_map<std::string, zel_system_t> systems;

	//entities
	std::vector<uint8_t> entities = { 0 };
	std::queue<uint32_t> empty_entities_spots;
};


struct zel_component_t
{
	std::vector<void*> components = { {} };
	zel_generational_ptr component_to_entity[ZEL_MAX_ENTITIES]; // replace with std::vector and make it as big as the actual data vector
	zel_generational_ptr entity_to_component[ZEL_MAX_ENTITIES]; // replace with std::vector and make it as big as the biggest entity_id requesting a component
	uint32_t last_component = 0;
	uint32_t component_size;
};

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
	level->systems.insert({system_name, system_update});
}

void zel_level_unregister_system(zel_level_t* level, const char* system_name)
{
	level->systems.erase(system_name);
}

template <typename T>
void zel_level_register_component(zel_level_t* level)
{
	ZelComponent<T>* new_component_type = new ZelComponent<T>();
	ZelComponentBase* base_component_type = new_component_type;
	std::string type_name = typeid(T).name();
	level->components.insert({ type_name, base_component_type });
}

template <typename T>
void zel_level_add_component(zel_level_t* level, zel_entity_id entity, T component)
{
	std::string type_name = std::string(typeid(T).name());
	ZelComponent<T>* component_type = (ZelComponent<T>*)(level->components[type_name]);

	component_type->create(entity, component);
}

template <typename T>
T* zel_level_get_component(zel_level_t* level, zel_entity_id entity)
{
	std::string type_name = std::string(typeid(T).name());
	ZelComponent<T>* component_type = (ZelComponent<T>*)(level->components[type_name]);

	return component_type->get_component(entity);
}

template <typename T>
std::vector<T>* zel_level_get_all_components(zel_level_t* level)
{
	std::string type_name = std::string(typeid(T).name());
	ZelComponent<T>* component_type = (ZelComponent<T>*)(level->components[type_name]);

	return component_type->get_all();
}
