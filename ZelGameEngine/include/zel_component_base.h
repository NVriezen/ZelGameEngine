#pragma once
#include <zel_base.h>
#include <zel_ecs.h>

class ZelComponentBase
{
public:
	virtual void destroy(zel_entity_id entity) = 0;

	zel_entity_id get_entity(zel_component_id component);
	bool has_component(zel_entity_id entity);

protected:
	zel_generational_ptr component_to_entity[ZEL_MAX_ENTITIES]; // replace with std::vector and make it as big as the actual data vector
	zel_generational_ptr entity_to_component[ZEL_MAX_ENTITIES]; // replace with std::vector and make it as big as the biggest entity_id requesting a component
	uint32_t last_component = 0;
};