#include <zel_material.h>

void zel_material_set_camera_uniforms(zel_material_t* material_to_set, glm::mat4 view_matrix, glm::mat4 projection_matrix)
{
	uint32_t* shader = (uint32_t*)zel_resources_get_from_id(material_to_set->shader_resource);
	zel_use_program((*shader));
	uint32_t view_location = material_to_set->custom_uniforms["ZEL_VIEW"];
	uint32_t projection_location = material_to_set->custom_uniforms["ZEL_PROJECTION"];
	zel_set_uniform_matrix4fv(view_location, 1, 0/*GL_FALSE*/, view_matrix);//glUniformMatrix4fv(material_to_set->view, 1, GL_FALSE, glm::value_ptr(camera_to_set->view));
	zel_set_uniform_matrix4fv(projection_location, 1, 0/*GL_FALSE*/, projection_matrix);//glUniformMatrix4fv(material_to_set->projection, 1, GL_FALSE, glm::value_ptr(camera_to_set->projection));
}

void zel_material_set_model(zel_material_t* material_to_set, glm::mat4 model)
{
	uint32_t model_location = material_to_set->custom_uniforms["ZEL_MODEL"];
	zel_set_uniform_matrix4fv(model_location, 1, 0/*GL_FALSE*/, model);//glUniformMatrix4fv(material_to_set->model, 1, GL_FALSE, glm::value_ptr(model));
}

void zel_material_set_texture(zel_material_t* material_to_set, std::string uniform_name, uint32_t texture_unit)
{
	uint32_t* shader = (uint32_t*)zel_resources_get_from_id(material_to_set->shader_resource);
	zel_use_program((*shader));
	uint32_t texture_location = material_to_set->custom_uniforms[uniform_name];
	zel_set_uniform_1i(texture_location, texture_unit);
}

//zel_material_t zel_material_create(const char* shader_path_vertex, const char* shader_path_fragment)
zel_material_t zel_material_create(zel_resource_id shader_resource)
{
	zel_material_t material;

	//load shader
	zel_resource_id shader_id = shader_resource;
	zel_resources_add_reference(shader_resource);
	material.shader_resource = shader_id;

	//get all uniforms
	zel_get_material_uniforms(&material);

	return material;
}

void zel_material_destroy(zel_material_t* material_to_destroy)
{
	zel_resources_unload(material_to_destroy->shader_resource);
	material_to_destroy->custom_uniforms.clear();
}