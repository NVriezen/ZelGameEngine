#pragma once
#include <zel_base.h>
#include <zel_types.h>
#include <unordered_map>

#include <glm/glm/glm.hpp>

struct zel_transform_t
{
	vector3 position;
	vector3 rotation;
	vector3 scale;
};

struct zel_mesh_t
{
	uint16_t VAO;
	uint16_t VBO;
	uint16_t EBO;
};

struct zel_material_t 
{
	uint32_t shader_resource;

	////general uniforms on every shader
	//uint32_t view;
	//uint32_t projection;
	//uint32_t model;

	std::unordered_map<std::string, uint32_t> custom_uniforms; //make this a map of user defined uniforms
};

struct zel_texture_t
{
	uint16_t render_id;
	uint16_t render_unit;
	uint16_t width;
	uint16_t height;
};

struct zel_camera_t 
{
	zel_transform_t transform;
	vector3 forward;
	vector3 up;
	glm::mat4 view;
	glm::mat4 projection;
	uint32_t framebuffer_id;
};