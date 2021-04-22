#pragma once
#include <zel_base.h>
#include <zel_ecs.h>
#include <vector>
#include <zel_logging.h>

template <typename T>
class ZelComponent : public ZelComponentBase
{
public:
	T* create(zel_entity_id entity, T component)
	{
		if (last_component == ZEL_MAX_ENTITIES - 1)
		{
			zel_print("[%s] Maximum amount reached, can't add any more components\n", "zel_component_transform");
			return nullptr;
		}

		++last_component;

		zel_index last_index = last_component;
		components.push_back(component);
		component_to_entity[last_index].id = entity;
		component_to_entity[last_index].generation += 1;
		zel_component_id new_component_id = ZEL_CREATE_ID(component_to_entity[last_index].generation, last_component);

		zel_index entity_index = ZEL_GET_INDEX(entity);
		zel_generation entity_generation = ZEL_GET_GENERATION(entity);
		entity_to_component[entity_index].id = new_component_id;
		entity_to_component[entity_index].generation = entity_generation;

		return &components[last_index];
	}

	void destroy(zel_entity_id entity)
	{
		zel_index entity_to_destroy_index = ZEL_GET_INDEX(entity);
		zel_generational_ptr component_pointer = entity_to_component[entity_to_destroy_index];
		if (component_pointer.generation != ZEL_GET_GENERATION(entity))
		{
			zel_print("[%s] Generation not equal, component already destroyed.\n", "zel_component_...");
			return;
		}

		uint32_t component_to_destroy_index = ZEL_GET_INDEX(component_pointer.id);
		//uint32_t entity_to_destroy_index = ZEL_GET_INDEX(entity);

		destroy_function(&components[component_to_destroy_index]);

		if (component_to_destroy_index == last_component)
		{
			component_to_entity[component_to_destroy_index].id = 0;
			component_to_entity[component_to_destroy_index].generation += 1;
			entity_to_component[entity_to_destroy_index].id = 0;
			entity_to_component[entity_to_destroy_index].generation += 1;
			return;
		}

		zel_generational_ptr entity_pointer_to_swap = component_to_entity[last_component];
		components[component_to_destroy_index] = components[last_component];
		component_to_entity[component_to_destroy_index] = entity_pointer_to_swap;
		component_to_entity[last_component].generation += 1;

		entity_to_component[ZEL_GET_INDEX(entity_pointer_to_swap.id)].id = component_pointer.id;
		entity_to_component[entity_to_destroy_index].generation += 1;
	}

	T* get_component(zel_entity_id entity)
	{
		zel_index entity_index = ZEL_GET_INDEX(entity);
		zel_generation entity_generation = ZEL_GET_GENERATION(entity);
		zel_generational_ptr component_pointer = entity_to_component[entity_index];
		if (component_pointer.generation != entity_generation)
		{
			zel_print("[zel_component class] get component return nullptr | Entity: %d | Type: %s\n", entity, typeid(T).name());
			return nullptr;
		}

		zel_index component_index = ZEL_GET_INDEX(component_pointer.id);
		return &components[component_index];
	}

	void free()
	{
		if (destroy_function == NULL)
		{
			components.clear();
			return;
		}

		uint32_t components_size = components.size();
		for (size_t i = 1; i < components_size; ++i)
		{
			destroy_function(&components[i]);
		}
		components.clear();
	}

	std::vector<T>* get_all()
	{
		return &components;
	}

	void(*destroy_function)(T*);

private:
	std::vector<T> components = { {} };
};