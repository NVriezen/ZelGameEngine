#pragma once
#include <zel_base.h>
#include <zel_ecs.h>
#include <vector>
#include <zel_component_base.h>
#include <zel_component_class.h>
#include <unordered_map>
#include <queue>
#include <typeinfo>
#include <typeindex>

typedef struct zel_level_t _zel_level_t;
typedef void(*zel_system_t)(_zel_level_t* level, float delta_time);

template <class _Container>
class QueueContainerWrapper : public _Container {
public:
	typedef typename _Container::container_type container_type;
	container_type &get_container() { return this->c; }
};

/**
*	The struct which holds all the entities, components and systems data.
*/
struct zel_level_t
{
	const char* level_name;

	////game state:
	//components
	std::unordered_map<std::type_index, ZelComponentBase*> components;

	//systems
	std::unordered_map<std::string, zel_system_t> systems;

	//entities
	std::vector<uint8_t> entities = { 0 };
	QueueContainerWrapper<std::queue<uint32_t>> empty_entities_spots;
};

zel_level_t* zel_level_create(const char* level_name);
void zel_level_destroy(zel_level_t* level);
zel_entity_id zel_level_create_entity(zel_level_t* level);
void zel_level_destroy_entity(zel_level_t* level, zel_entity_id entity);
void zel_level_register_system(zel_level_t* level, zel_system_t system_update, const char* system_name);
void zel_level_unregister_system(zel_level_t* level, const char* system_name);

/**
*	Call this function before using a component type in your program to register it.
*	Only call this function once for every level.
*/
template <typename T>
void zel_level_register_component(zel_level_t* level)
{
	std::type_index type_index = std::type_index(typeid(T));
	if (level->components.find(type_index) != level->components.end())
	{
		//The component type is already registered
		return;
	}

	ZelComponent<T>* new_component_type = new ZelComponent<T>();
	ZelComponentBase* base_component_type = new_component_type;
	level->components.insert({ type_index, base_component_type });
}

/**
*	Call this function before using a component type in your program to register it.
*	Only call this function once for every level.
*	(Same as zel_level_register_component, but with the option to supply a destroy function)
*/
template <typename T>
void zel_level_register_component_with_destroy(zel_level_t* level, void (*destroy_function)(T*))
{
	std::type_index type_index = std::type_index(typeid(T));
	if (level->components.find(type_index) != level->components.end())
	{
		//The component type is already registered
		return;
	}

	ZelComponent<T>* new_component_type = new ZelComponent<T>();
	new_component_type->destroy_function = destroy_function;
	ZelComponentBase* base_component_type = new_component_type;
	level->components.insert({ type_index, base_component_type });
}

/**
*	Copies and adds a component to the specified entity in the specified level
*/
template <typename T>
void zel_level_add_component(zel_level_t* level, zel_entity_id entity, T component)
{
	std::type_index type_index = std::type_index(typeid(T));
	ZelComponent<T>* component_type = (ZelComponent<T>*)(level->components[type_index]);

	component_type->create(entity, component);
}

/**
*	Returns a pointer to the requested component for the specified entity in the specified level.
*	If the component does not exist, it returns a null pointer.
*	The pointer must not be freed, that's done when the component is destroyed.
*/
template <typename T>
T* zel_level_get_component(zel_level_t* level, zel_entity_id entity)
{
	std::type_index type_index = std::type_index(typeid(T));
	ZelComponent<T>* component_type = (ZelComponent<T>*)(level->components[type_index]);

	return component_type->get_component(entity);
}

template <typename A, typename... T>
bool zel_level_has_components(zel_level_t* level, zel_entity_id entity)
{
	std::type_index component_types[] = { std::type_index(typeid(A)), std::type_index(typeid(T))... };

	uint32_t types_size = sizeof...(T) + 1;
	std::vector<ZelComponentBase*> type_bases;
	for (size_t i = 0; i < types_size; i++)
	{
		//zel_print("Printing component template names: %s\n", component_names[i].c_str());
		type_bases.push_back(level->components[component_types[i]]);
	}

	for (size_t j = 0; j < types_size; j++)
	{
		if (!type_bases[j]->has_component(entity))
			return false;
	}

	return true;
}
