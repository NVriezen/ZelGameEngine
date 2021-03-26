#pragma once
#include <zel_base.h>

#define ZEL_CAPACITY_GENERATION 0xFF
#define ZEL_CAPACITY_ENTITIES 0xFFFFFF
#define ZEL_MAX_ENTITIES 0xFFFF
#define ZEL_GENERATION_BIT 24

#define ZEL_GET_GENERATION(id) ((id & 0xFF000000) >> ZEL_GENERATION_BIT)
#define ZEL_GET_INDEX(id) (id & ZEL_CAPACITY_ENTITIES)
#define ZEL_CREATE_ID(generation, index) (generation << ZEL_GENERATION_BIT) | index

// The upper 8 bits is the generation
// The lower 24 bits is the actual index in the array
typedef uint32_t zel_ecs_id;
typedef zel_ecs_id zel_component_id; 
typedef zel_ecs_id zel_entity_id;

typedef uint32_t zel_index;
typedef uint8_t  zel_generation;

struct zel_generational_ptr
{
	zel_ecs_id id;
	zel_generation generation;
};