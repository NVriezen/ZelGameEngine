#include <zel_shader.h>
#include <zel_io.h>
#include <zel_logging.h>
#include <glad/glad.h>

void zel_shader_use(const uint32_t shader_pointer)
{
	glUseProgram(shader_pointer);
}

void zel_shader_destroy(void* shader_pointer)
{
	zel_print("Shader pointer: %d\n", shader_pointer);
	zel_shader_t* shader = (zel_shader_t*)shader_pointer;
	zel_print("Shader pointer (casted): %d | Shader ID: %d\n", shader, (*shader));
	glDeleteProgram((*shader));
	//delete (zel_shader_t*)shader_pointer;
	delete shader;
	zel_print("[SHOULD BE DELETED] Shader pointer (casted): %d | Shader ID: %d\n"/*, shader, (*shader)*/);
}

uint32_t zel_shader_create(const char* path_to_vertex, const char* path_to_fragment)
{
	uint32_t vertex_shader;
	uint32_t fragment_shader;

	int succes;
	char infoLog[512];
	uint64_t file_length;

	//create vertex shader
	char* vertex_source = zel_io_load_file_in_memory(path_to_vertex, &file_length);
	if (vertex_source == nullptr)
	{
		zel_print("[Zel Shader (Windows)] Could not open vertex shader.\n");
		return -1;
	}

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		zel_print(infoLog);
	}

	delete[] vertex_source;

	//create fragment shader
	char* fragment_source = zel_io_load_file_in_memory(path_to_fragment, &file_length);
	if (fragment_source == nullptr)
	{
		zel_print("[Zel Shader (Windows)] Could not open vertex shader.\n");
		return -1;
	}

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source, NULL);
	glCompileShader(fragment_shader);


	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &succes);
	if (!succes)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		zel_print(infoLog);
	}

	delete[] fragment_source;

	// create the shader program
	uint32_t shader = glCreateProgram();
	glAttachShader(shader, vertex_shader);
	glAttachShader(shader, fragment_shader);
	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &succes);
	if (!succes)
	{
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		zel_print(infoLog);
	}

	// delete the seperate shaders
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	zel_print("Shader ID: %d\n", shader);

	return shader;
}