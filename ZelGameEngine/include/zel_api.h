#pragma once
#include <zel_base.h>

#include <zel_engine_settings.h>
#include <zel_logging.h>
#include <zel_profiling_timer.h>
#include <zel_types.h>

// Input
#include <zel_input.h>

// Rendering
#include <zel_render_api.h>
#include <zel_rendering_utils.h>
#include <zel_renderer_general.h>
#include <zel_shader.h>
#include <zel_material.h>
#include <zel_texture.h>

// ECS
#include <zel_ecs.h>
#include <zel_level.h>
#include <zel_component_base.h>
#include <zel_component_class.h>
#include <zel_resources.h>
#include <zel_entity_collection.h>
#include <zel_component_collection.h>
#include <zel_duo_collection.h>

// Standard ECS Components
#include <zel_component_builtin.h>

// Platform specific definitions
#include <zel_platform_entry.h>
#include <zel_platform_utils.h>
#include <zel_window.h>
#include <zel_io.h>