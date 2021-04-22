#pragma once
#include <zel_base.h>
#include <zel_component_builtin.h>

//zel_PLATFORM_texture.cpp
uint32_t zel_load_render_texture(const char* path_to_texture, int32_t* width, int32_t* height);

//zel_texture.cpp
zel_texture_t zel_texture_load(const char* path_to_texture);