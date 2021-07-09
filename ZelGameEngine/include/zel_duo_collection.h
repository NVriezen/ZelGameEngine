#pragma once
#include <zel_base.h>
#include <zel_ecs.h>
#include <zel_level.h>
#include <zel_component_base.h>
#include <zel_component_class.h>
#include <vector>
#include <string>

template <typename A, typename B, typename C, typename D>
struct zel_duo_collection4
{
	uint32_t length;
	std::vector<A*> first;
	std::vector<B*> second;
	std::vector<C*> third;
	std::vector<D*> fourth;
	std::vector<zel_entity_id> entities;
};

template <typename A, typename B, typename C>
struct zel_duo_collection3
{
	uint32_t length;
	std::vector<A*> first;
	std::vector<B*> second;
	std::vector<C*> third;
	std::vector<zel_entity_id> entities;
};

template <typename A, typename B>
struct zel_duo_collection2
{
	uint32_t length;
	std::vector<A*> first;
	std::vector<B*> second;
	std::vector<zel_entity_id> entities;
};

template <typename A>
struct zel_duo_collection
{
	uint32_t length;
	std::vector<A>* first;
	std::vector<zel_entity_id> entities;
};

template <typename A>
zel_duo_collection<A> zel_duo_collection_create(zel_level_t* level)
{
	std::type_index component_type = std::type_index(typeid(A));
	ZelComponent<A>* component_container = (ZelComponent<A>*)level->components[component_type];

	zel_duo_collection<A> collection;
	collection.first = &component_container->components;

	zel_generational_ptr* component_to_entity = level->components[component_type]->component_to_entity;
	uint32_t amount_of_components = component_container->total_components() + 1;
	for (size_t component_index = 0; component_index < amount_of_components; component_index++)
	{
		zel_entity_id entity = component_to_entity[component_index].id;
		collection.entities.push_back(entity);
	}
	collection.length = amount_of_components;

	return collection;
}

template <typename A, typename B>
zel_duo_collection2<A, B> zel_duo_collection_create(zel_level_t* level)
{
	std::type_index component_types[] = { std::type_index(typeid(A)), std::type_index(typeid(B)) };

	uint32_t lowest_amount_components = -1;
	//uint8_t index = 0;
	//for (uint8_t i = 0; i < 2; i++)
	//{
	//	uint32_t amount = level->components[component_types[i]]->total_components();
	//	if (amount < lowest_amount_components)
	//	{
	//		lowest_amount_components = amount;
	//		index = i;
	//	}
	//}

	std::type_index component_type_a = std::type_index(typeid(A));
	std::type_index component_type_b = std::type_index(typeid(B));
	uint32_t amount_a = level->components[component_type_a]->total_components();
	uint32_t amount_b = level->components[component_type_b]->total_components();
	uint8_t index = (amount_b <= amount_a);
	lowest_amount_components = (amount_a < amount_b)*amount_a + index * amount_b;

	zel_duo_collection2<A, B> collection;
	collection.length = lowest_amount_components - 1;

	zel_generational_ptr* component_to_entity = level->components[component_names[index]]->component_to_entity;
	for (size_t component_index = 1; component_index < lowest_amount_components + 1; component_index++)
	{
		zel_entity_id entity = component_to_entity[component_index].id;
		collection.entities.push_back(entity);
		collection.first.push_back(zel_level_get_component<A>(level, entity));
		collection.second.push_back(zel_level_get_component<B>(level, entity));
	}

	return collection;
}

template <typename A, typename B, typename C>
zel_duo_collection3<A, B, C> zel_duo_collection_create(zel_level_t* level)
{
	std::type_index component_types[] = { std::type_index(typeid(A)), std::type_index(typeid(B)), std::type_index(typeid(C)) };

	uint32_t lowest_amount_components = -1;
	uint8_t index = 0;
	for (uint8_t i = 0; i < 3; i++)
	{
		uint32_t amount = level->components[component_types[i]]->total_components();
		if (amount < lowest_amount_components)
		{
			lowest_amount_components = amount;
			index = i;
		}
	}

	zel_duo_collection3<A, B, C> collection;
	collection.length = lowest_amount_components - 1;

	zel_generational_ptr* component_to_entity = level->components[component_types[index]]->component_to_entity;
	for (size_t component_index = 1; component_index < lowest_amount_components + 1; component_index++)
	{
		zel_entity_id entity = component_to_entity[component_index].id;
		collection.entities.push_back(entity);
		collection.first.push_back(zel_level_get_component<A>(level, entity));
		collection.second.push_back(zel_level_get_component<B>(level, entity));
		collection.third.push_back(zel_level_get_component<C>(level, entity));
	}

	return collection;
}

template <typename A, typename B, typename C, typename D>
zel_duo_collection4<A, B, C, D> zel_duo_collection_create(zel_level_t* level)
{
	std::type_index component_types[] = { std::type_index(typeid(A)), std::type_index(typeid(B)), std::type_index(typeid(C)), std::type_index(typeid(D)) };

	uint32_t lowest_amount_components = -1;
	uint8_t index = 0;
	for (uint8_t i = 0; i < 4; i++)
	{
		uint32_t amount = level->components[component_types[i]]->total_components();
		if (amount < lowest_amount_components)
		{
			lowest_amount_components = amount;
			index = i;
		}
	}

	zel_duo_collection4<A, B, C, D> collection;
	collection.length = lowest_amount_components - 1;

	zel_generational_ptr* component_to_entity = level->components[component_types[index]]->component_to_entity;
	for (size_t component_index = 1; component_index < lowest_amount_components + 1; component_index++)
	{
		zel_entity_id entity = component_to_entity[component_index].id;
		collection.entities.push_back(entity);
		collection.first.push_back(zel_level_get_component<A>(level, entity));
		collection.second.push_back(zel_level_get_component<B>(level, entity));
		collection.third.push_back(zel_level_get_component<C>(level, entity));
		collection.fourth.push_back(zel_level_get_component<D>(level, entity));
	}

	return collection;
}