#include <zel_texture.h>
#include <zel_io.h>
#include <zel_logging.h>
#include <glad\glad.h>
#include <stb_image.h>

//zel_texture_t zel_texture_load(const char* path_to_texture)
//{
//	uint32_t resource_id = zel_resources_load(path_to_texture);
//	if (resource_id != 0)
//	{
//		zel_texture_t new_texture = zel_resources_get_texture(resource_id);
//		return new_texture;
//	}
//
//	int32_t* width;
//	int32_t* height;
//
//	int32_t channels;
//	stbi_set_flip_vertically_on_load(true);
//	char* texture_path = zel_io_get_absolute_path(path_to_texture);
//	uint8_t* data = stbi_load(texture_path, width, height, &channels, 0); //TODO: investigate if it works on consoles. If not, replace with stdbi_load_from_file or other.
//	if (!data)
//	{
//		zel_print("Could not load image.");
//	}
//	delete[] texture_path;
//
//	uint32_t texture;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*width), (*height), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//	//glGenerateMipmap(GL_TEXTURE_2D);
//
//	glActiveTexture(GL_TEXTURE0 + texture_unit);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	++texture_unit;
//
//	stbi_image_free(data);
//
//	zel_texture_t new_texture;
//	new_texture.render_id = texture;
//	new_texture.width = (*width);
//	new_texture.height = (*height);
//
//	zel_resources_add_texture(new_texture);
//
//	return new_texture;
//}

uint8_t texture_unit = 1;
uint32_t zel_load_render_texture(const char* path_to_texture, int32_t* width, int32_t* height)
{
	int32_t channels;
	stbi_set_flip_vertically_on_load(true);
	char* texture_path = zel_io_get_absolute_path(path_to_texture);
	uint8_t* data = stbi_load(texture_path, width, height, &channels, 0); //TODO: investigate if it works on consoles. If not, replace with stdbi_load_from_file or other.
	if (!data)
	{
		zel_print("Could not load image.");
	}
	delete[] texture_path;

	uint32_t texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*width), (*height), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//glGenerateMipmap(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0 + texture_unit);
	glBindTexture(GL_TEXTURE_2D, texture);
	++texture_unit;

	stbi_image_free(data);

	return texture;
}