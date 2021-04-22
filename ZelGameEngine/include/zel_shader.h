#pragma once
#include <zel_base.h>
#include <zel_resources.h>

typedef uint32_t zel_shader_t;

zel_resource_id zel_shader_load(const char* path_to_vertex, const char* path_to_fragment);
zel_shader_t zel_shader_create(const char* path_to_vertex, const char* path_to_fragment);
void zel_shader_use(const uint32_t shader_pointer);
void zel_shader_destroy(void* shader_pointer);