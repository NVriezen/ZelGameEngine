#pragma once
#include <zel_base.h>
#include <zel_types.h>

struct zel_transform_t
{
	vector3 position;
	vector3 rotation;
	vector3 scale;
};

//std::vector<zel_transform_t> transforms = { {} };
//zel_generational_ptr	component_to_entity [ZEL_MAX_ENTITIES]; // replace with std::vector and make it as big as the actual data vector
//zel_generational_ptr	entity_to_component [ZEL_MAX_ENTITIES]; // replace with std::vector and make it as big as the biggest entity_id requesting a component
//uint32_t				last_component = 0;
//
//struct zel_component_t
//{
//	std::vector<void*> components = { {} };
//	zel_generational_ptr component_to_entity[ZEL_MAX_ENTITIES];
//	zel_generational_ptr entity_to_component[ZEL_MAX_ENTITIES];
//	uint32_t last_component = 0;
//	uint32_t component_size;
//};
//
//zel_component_t* transform_component;
//zel_component_t* zel_transform_type_create()
//{
//	zel_component_t* new_component_type = new zel_component_t;
//	new_component_type->component_size = sizeof(zel_transform_t);
//	//add to list of components in level;
//
//	transform_component = new_component_type;
//}
//
//zel_transform_t* zel_transform_create(zel_entity_id entity)
//{
//	if (last_component == ZEL_MAX_ENTITIES)
//	{
//		zel_print("[%s] Maximum amount reached, can't add any more components", "zel_component_transform");
//		return nullptr;
//	}
//
//	++last_component;
//
//	zel_transform_t* new_transform = new zel_transform_t;
//	new_transform->position = { 0,0,0 };
//	new_transform->rotation = { 0,0,0 };
//	new_transform->scale = { 1,1,1 };
//	//	{0,0,0},
//	//	{0,0,0},
//	//	{1,1,1}
//	//};
//	zel_index last_index = last_component;// *transform_component.component_size;
//	transform_component->components.push_back((void*)new_transform);
//	transform_component->component_to_entity[last_index].id = entity;
//	component_to_entity[last_index].generation += 1;
//	zel_component_id new_component_id = ZEL_CREATE_ID(transform_component->component_to_entity[last_index].generation, last_component);
//
//	zel_index entity_index = ZEL_GET_INDEX(entity);// *transform_component.component_size;
//	zel_generation entity_generation = ZEL_GET_GENERATION(entity);
//	transform_component->entity_to_component[entity_index].id = new_component_id;
//	transform_component->entity_to_component[entity_index].generation = entity_generation;
//
//	return (zel_transform_t*)transform_component->components[last_index];
//
//	//transforms.push_back(new_transform);//transform_components[last_component] = new_transform;
//	//component_to_entity[last_component].id = entity;
//	//component_to_entity[last_component].generation += 1;
//	//zel_component_id new_component_id = ZEL_CREATE_ID(component_to_entity[last_component].generation, last_component);
//
//	//zel_index entity_index = ZEL_GET_INDEX(entity);
//	//zel_generation entity_generation = ZEL_GET_GENERATION(entity);
//	//entity_to_component[entity_index].id = new_component_id;
//	//entity_to_component[entity_index].generation = entity_generation;
//
//	//return &transforms[last_component]; //&transform_components[last_component];
//}
//
//void zel_transform_destroy(zel_entity_id entity)
//{
//	zel_generational_ptr component_pointer = entity_to_component[entity];
//	if (component_pointer.generation != ZEL_GET_GENERATION(entity))
//	{
//		zel_print("[%s] Generation not equal, component already destroyed.", "zel_component_transform");
//		return;
//	}
//
//	uint32_t component_to_destroy_index = ZEL_GET_INDEX(component_pointer.id);
//	uint32_t entity_to_destroy_index = ZEL_GET_INDEX(entity);
//	if (component_to_destroy_index == last_component)
//	{
//		component_to_entity[component_to_destroy_index].id = 0;
//		component_to_entity[component_to_destroy_index].generation += 1;
//		entity_to_component[entity_to_destroy_index].id = 0;
//		entity_to_component[entity_to_destroy_index].generation += 1;
//		return;
//	}
//
//	zel_generational_ptr entity_pointer_to_swap = component_to_entity[last_component];
//	transforms[component_to_destroy_index] = transforms[last_component];
//	component_to_entity[component_to_destroy_index] = entity_pointer_to_swap;
//	component_to_entity[last_component].generation += 1;
//
//	entity_to_component[ZEL_GET_INDEX(entity_pointer_to_swap.id)].id = component_pointer.id;
//	entity_to_component[entity_to_destroy_index].generation += 1;
//}
//
//zel_entity_id zel_transform_get_entity(zel_component_id component)
//{
//	zel_index component_index = ZEL_GET_INDEX(component);
//	zel_generation component_generation = ZEL_GET_GENERATION(component);
//	zel_generational_ptr entity_pointer = component_to_entity[component_index];
//	if (entity_pointer.generation != component_generation)
//	{
//		return 0;
//	}
//
//	return entity_pointer.id;
//}
//
//zel_transform_t* zel_transform_get_component(zel_entity_id entity)
//{
//	//using general component type
//	zel_index entity_index = ZEL_GET_INDEX(entity);// *transform_component.component_size;
//	zel_generation entity_generation = ZEL_GET_GENERATION(entity);
//	zel_generational_ptr component_pointer = transform_component->entity_to_component[entity_index];
//	if (component_pointer.generation != entity_generation)
//	{
//		return nullptr;
//	}
//
//	zel_index component_index = ZEL_GET_INDEX(component_pointer.id);// *transform_component.component_size;
//	return (zel_transform_t*)transform_component->components[component_index];//&transform_components[component_index];
//
//	////using array
//	//zel_index entity_index = ZEL_GET_INDEX(entity);
//	//zel_generation entity_generation = ZEL_GET_GENERATION(entity);
//	//zel_generational_ptr component_pointer = entity_to_component[entity_index];
//	//if (component_pointer.generation != entity_generation)
//	//{
//	//	return nullptr;
//	//}
//
//	//zel_index component_index = ZEL_GET_INDEX(component_pointer.id);
//	//return &transforms[component_index];//&transform_components[component_index];
//}
//
//bool zel_transform_has_component(zel_entity_id entity)
//{
//	zel_index entity_index = ZEL_GET_INDEX(entity);
//	zel_generation entity_generation = ZEL_GET_GENERATION(entity);
//	zel_generational_ptr component_pointer = entity_to_component[entity_index];
//
//	return component_pointer.generation == entity_generation;
//}