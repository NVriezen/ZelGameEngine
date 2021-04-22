#include <zel_material.h>
#include <glad\glad.h>

void zel_get_material_uniforms(zel_material_t* material)
{
	uint32_t* shader_pointer = (uint32_t*)zel_resources_get_from_id(material->shader_resource);
	GLint shader_id = (*shader_pointer);

	/// For getting all uniforms in a shader
	GLint uniforms_count = 0;
	GLint uniforms_name_length = 0;
	glGetProgramiv(shader_id, GL_ACTIVE_UNIFORMS, &uniforms_count);
	glGetProgramiv(shader_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniforms_name_length);
	printf("Active Uniforms: %d\n", uniforms_count);

	for (size_t i = 0; i < uniforms_count; i++)
	{
		char* uniform_name = new char[uniforms_name_length];
		GLsizei uniform_name_length = 0;
		GLsizei uniform_size = 0;
		GLenum uniform_type = 0;
		glGetActiveUniform(shader_id, (GLuint)i, uniforms_name_length, &uniform_name_length, &uniform_size, &uniform_type, uniform_name);

		printf("Uniform #%d Type: %u Name: %s\n", i, uniform_type, uniform_name);

		//check if name equals any of the names in general uniforms array
		//if so, set the correct variable in new material
		//if not, add to map of user defined uniforms
		material->custom_uniforms.insert({ uniform_name, i });
	}
}