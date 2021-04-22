#pragma once
#include <zel_base.h>
#include <zel_component_builtin.h>
#include <zel_render_api.h>
#include <zel_shader.h>
#include <string>

//zel_PLATFORM_material.cpp
void zel_get_material_uniforms(zel_material_t* material);

//zel_material.cpp
void zel_material_set_camera_uniforms(zel_material_t* material_to_set, glm::mat4 view_matrix, glm::mat4 projection_matrix);
void zel_material_set_model(zel_material_t* material_to_set, glm::mat4 model);
void zel_material_set_texture(zel_material_t* material_to_set, std::string uniform_name, uint32_t texture_unit);
//zel_material_t zel_material_create(const char* shader_path_vertex, const char* shader_path_fragment);
zel_material_t zel_material_create(zel_resource_id shader_resource);
void zel_material_destroy(zel_material_t* material_to_destroy);