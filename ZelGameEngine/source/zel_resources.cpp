#include <zel_resources.h>
#include <zel_level.h>

#include <zel_shader.h>
#include <zel_render_api.h>

zel_level_t* resource_level;

void zel_resources_destroy(zel_resource_t* resource)
{
	void* resource_pointer = resource->pointer;
	resource->destructor(resource_pointer);
}

void zel_resources_init()
{
	resource_level = zel_level_create("resources");
	zel_level_register_component_with_destroy<zel_resource_t>(resource_level, zel_resources_destroy);
}

//Hide this one from api?
zel_resource_id zel_resources_add(const char* path, void* pointer_to_resource, resource_destructor destructor_function)
{
	for (zel_entity_id entity : zel_entities_list<zel_resource_t>(resource_level))
	{
		zel_resource_t* resource = zel_level_get_component<zel_resource_t>(resource_level, entity);
		if (resource->path == path)
		{
			return entity;
		}
	}

	zel_resource_t resource;
	resource.path = path;
	resource.pointer = pointer_to_resource;
	resource.destructor = destructor_function;
	resource.counter = 1;

	zel_entity_id resource_entity = zel_level_create_entity(resource_level);
	zel_level_add_component<zel_resource_t>(resource_level, resource_entity, resource);

	return resource_entity;
}

zel_resource_id zel_resources_get_loaded(const char* path)
{
	for (zel_entity_id entity : zel_entities_list<zel_resource_t>(resource_level))
	{
		zel_resource_t* resource = zel_level_get_component<zel_resource_t>(resource_level, entity);
		if (resource->path == path)
		{
			resource->counter += 1;
			return entity;
		}
	}

	return 0;
}

void* zel_resources_get_from_id(zel_resource_id resource_id)
{
	zel_resource_t* resource = zel_level_get_component<zel_resource_t>(resource_level, resource_id);
	return resource->pointer;
}

void zel_resources_unload(zel_resource_id resource_id)
{
	zel_resource_t* resource = zel_level_get_component<zel_resource_t>(resource_level, resource_id);
	
	//Fix this line, this is just temporary fix
	if (resource == nullptr)
		return;

	if (resource->counter != 1)
	{
		--resource->counter;
		return;
	}

	//void* resource_pointer = resource->pointer;
	//resource->destructor(resource_pointer);
	zel_level_destroy_entity(resource_level, resource_id);
}

void zel_resources_add_reference(zel_resource_id resource_id)
{
	zel_resource_t* resource = zel_level_get_component<zel_resource_t>(resource_level, resource_id);
	++resource->counter;
}
