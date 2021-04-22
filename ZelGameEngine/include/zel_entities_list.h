#pragma once
#include <zel_base.h>

struct zel_level_t;

template <typename... T>
struct zel_entities_list
{
	zel_entities_list(zel_level_t* level)
		: _level(level)
	{

	}

	struct iterator
	{
		iterator(zel_level_t* level, zel_index entity_index)
			: _level(level), _entity_index(entity_index)
		{
		};

		zel_entity_id operator*() const
		{
			//give back entityid
			return ZEL_CREATE_ID(_level->entities[_entity_index], _entity_index);
		}

		const bool operator==(const iterator& other)
		{
			bool out_of_range = _entity_index == _level->entities.size();
			if (out_of_range)
			{
				return out_of_range;
			}

			return (other._entity_index == _entity_index) && (_level->entities[other._entity_index] == _level->entities[_entity_index]);
		}

		const bool operator!=(const iterator& other)
		{
			bool is_not_size = _entity_index != _level->entities.size();
			if (!is_not_size)
			{
				return false;
			}

			return (other._entity_index != _entity_index) || (_level->entities[other._entity_index] != _level->entities[_entity_index]);
		}

		bool valid_index()
		{
			auto c = _level->empty_entities_spots._Get_container();
			uint32_t e_index = _entity_index;
			auto it = std::find_if(c.begin(), c.end(), [e_index](uint32_t index) { return index == e_index; });
			bool is_end = it == c.end();
			return is_end && zel_level_has_components<T...>(_level, ZEL_CREATE_ID(_level->entities[_entity_index], _entity_index));
		}

		iterator& operator++()
		{
			//PROFILE_FUNCTION();

			do
			{
				_entity_index++;
			} while (_entity_index < _level->entities.size() && !valid_index());
			return *this;
		}

		iterator operator++(int)
		{
			++*this;
			return *this;
		}

		zel_index _entity_index;
		zel_level_t* _level = nullptr;
	};

	bool valid_index(uint32_t entity_index)
	{
		auto c = _level->empty_entities_spots._Get_container();
		auto it = std::find_if(c.begin(), c.end(), [entity_index](uint32_t index) { return index == entity_index; });
		return it == c.end() && zel_level_has_components<T...>(_level, ZEL_CREATE_ID(_level->entities[entity_index], entity_index));
	}

	const iterator begin()
	{
		//PROFILE_FUNCTION();

		uint32_t first_entity_index = 1;

		auto c = _level->empty_entities_spots._Get_container();
		while (first_entity_index < _level->entities.size() && !valid_index(first_entity_index))
		{
			first_entity_index++;
		}
		return iterator(_level, first_entity_index);
	}

	const iterator end()
	{
		return iterator(_level, _level->entities.size());
	}

	zel_level_t* _level;
};