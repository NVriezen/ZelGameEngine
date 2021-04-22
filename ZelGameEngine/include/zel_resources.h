#pragma once
#include <zel_base.h>

typedef uint32_t zel_resource_id;
typedef void(*resource_destructor)(void*);

struct zel_resource_t
{
	void* pointer;
	uint32_t counter;
	resource_destructor destructor;
	const char* path;
};

void zel_resources_init();
zel_resource_id zel_resources_add(const char* path, void* pointer_to_resource, resource_destructor destructor_function);
zel_resource_id zel_resources_get_loaded(const char* path);
void* zel_resources_get_from_id(zel_resource_id resource_id);
void zel_resources_unload(zel_resource_id resource_id);
void zel_resources_add_reference(zel_resource_id resource_id);
