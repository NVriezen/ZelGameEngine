#include <zel_shader.h>
#include <string>

zel_resource_id zel_shader_load(const char* path_to_vertex, const char* path_to_fragment)
{
	std::string combined_path = path_to_vertex;
	combined_path += path_to_fragment;

	zel_resource_id shader_resource = zel_resources_get_loaded(combined_path.c_str());

	if (shader_resource != 0)
	{
		return shader_resource;
	}

	zel_shader_t* new_shader = new zel_shader_t;
	(*new_shader) = zel_shader_create(path_to_vertex, path_to_fragment);
	shader_resource = zel_resources_add(combined_path.c_str(), new_shader, zel_shader_destroy);

	return shader_resource;
}