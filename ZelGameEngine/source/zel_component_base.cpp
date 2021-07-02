#include <zel_component_base.h>
#include <zel_logging.h>

zel_entity_id ZelComponentBase::get_entity(zel_component_id component)
{
	zel_index component_index = ZEL_GET_INDEX(component);
	zel_generation component_generation = ZEL_GET_GENERATION(component);
	zel_generational_ptr entity_pointer = component_to_entity[component_index];
	if (entity_pointer.generation != component_generation)
	{
		return 0;
	}

	return entity_pointer.id;
}

bool ZelComponentBase::has_component(zel_entity_id entity)
{
	zel_index entity_index = ZEL_GET_INDEX(entity);
	zel_generation entity_generation = ZEL_GET_GENERATION(entity);
	zel_generational_ptr component_pointer = entity_to_component[entity_index];
	
	return component_pointer.generation == entity_generation;
}

uint32_t ZelComponentBase::total_components()
{
	return last_component;
}