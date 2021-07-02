#pragma once
#include <zel_base.h>
#include <zel_ecs.h>
#include <zel_level.h>
#include <zel_component_base.h>
#include <zel_component_class.h>
#include <vector>
#include <string>

template <typename A, typename B, typename C, typename D>
struct zel_component_collection4
{
	uint32_t length;
	std::vector<A*> first;
	std::vector<B*> second;
	std::vector<C*> third;
	std::vector<D*> fourth;
	std::vector<zel_entity_id> entities;
};

template <typename A, typename B, typename C>
struct zel_component_collection3
{
	uint32_t length;
	std::vector<A*> first;
	std::vector<B*> second;
	std::vector<C*> third;
	std::vector<zel_entity_id> entities;
};

template <typename A, typename B>
struct zel_component_collection2
{
	uint32_t length;
	std::vector<A*> first;
	std::vector<B*> second;
	std::vector<zel_entity_id> entities;
};

template <typename A>
struct zel_component_collection
{
	uint32_t length;
	std::vector<A>* first;
	std::vector<zel_entity_id> entities;
};

template <typename A>
zel_component_collection<A> zel_component_collection_create(zel_level_t* level)
{
	std::string component_name = std::string(typeid(A).name());
	ZelComponent<A>* component_container = (ZelComponent<A>*)level->components[component_name];

	zel_component_collection<A> collection;
	collection.first = &component_container->components;

	zel_generational_ptr* component_to_entity = level->components[component_name]->component_to_entity;
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
zel_component_collection2<A, B> zel_component_collection_create(zel_level_t* level)
{
	std::string component_names[] = { std::string(typeid(A).name()), std::string(typeid(B).name()) };

	uint32_t lowest_amount_components = -1;
	uint8_t index = 0;
	for (uint8_t i = 0; i < 2; i++)
	{
		uint32_t amount = level->components[component_names[i]]->total_components();
		if (amount < lowest_amount_components)
		{
			lowest_amount_components = amount;
			index = i;
		}
	}

	zel_component_collection2<A, B> collection;
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
zel_component_collection3<A, B, C> zel_component_collection_create(zel_level_t* level)
{
	std::string component_names[] = { std::string(typeid(A).name()), std::string(typeid(B).name()), std::string(typeid(C).name()) };

	uint32_t lowest_amount_components = -1;
	uint8_t index = 0;
	for (uint8_t i = 0; i < 3; i++)
	{
		uint32_t amount = level->components[component_names[i]]->total_components();
		if (amount < lowest_amount_components)
		{
			lowest_amount_components = amount;
			index = i;
		}
	}

	zel_component_collection3<A, B, C> collection;
	collection.length = lowest_amount_components - 1;

	zel_generational_ptr* component_to_entity = level->components[component_names[index]]->component_to_entity;
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
zel_component_collection4<A, B, C, D> zel_component_collection_create(zel_level_t* level)
{
	std::string component_names[] = { std::string(typeid(A).name()), std::string(typeid(B).name()), std::string(typeid(C).name()), std::string(typeid(D).name()) };

	uint32_t lowest_amount_components = -1;
	uint8_t index = 0;
	for (uint8_t i = 0; i < 4; i++)
	{
		uint32_t amount = level->components[component_names[i]]->total_components();
		if (amount < lowest_amount_components)
		{
			lowest_amount_components = amount;
			index = i;
		}
	}

	zel_component_collection4<A, B, C, D> collection;
	collection.length = lowest_amount_components - 1;

	zel_generational_ptr* component_to_entity = level->components[component_names[index]]->component_to_entity;
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