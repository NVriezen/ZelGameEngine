#include <zel_texture.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

zel_texture_t zel_texture_load(const char* path_to_texture)
{
	int32_t width;
	int32_t height;
	uint32_t texture = zel_load_render_texture(path_to_texture, &width, &height);

	zel_texture_t new_texture;
	new_texture.render_id = texture;
	new_texture.width = (uint16_t)width;
	new_texture.height = (uint16_t)height;

	return new_texture;
}