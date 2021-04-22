#include <zel_rendering_utils.h>
#include <zel_render_api.h>

void zel_scale_fit_screen(uint16_t screen_width, uint16_t screen_height, uint16_t game_width, uint16_t game_height)
{
	float target_aspect_ratio = (float)game_width / (float)game_height;

	uint16_t fitted_screen_width = screen_width - (screen_width % game_width);
	uint16_t fitted_screen_height = screen_height - (screen_height % game_height);

	uint16_t width = fitted_screen_width;
	uint16_t height = (uint16_t)(width / target_aspect_ratio + 0.5f);

	if (height > fitted_screen_height)
	{
		height = fitted_screen_height;
		width = (int)(height * target_aspect_ratio + 0.5f);
	}

	uint16_t viewport_offset_x = (screen_width * 0.5f) - (width * 0.5f);
	uint16_t viewport_offset_y = (screen_height * 0.5f) - (height * 0.5f);

	draw_resolution_x = width;
	draw_resolution_y = height;

	zel_set_viewport(viewport_offset_x, viewport_offset_y, width, height);
}

void zel_screen_swap_blit(uint16_t screen_width, uint16_t screen_height, uint16_t game_width, uint16_t game_height)
{
	float target_aspect_ratio = (float)game_width / (float)game_height;

	uint16_t fitted_screen_width = screen_width - (screen_width % game_width);
	uint16_t fitted_screen_height = screen_height - (screen_height % game_height);

	uint16_t width = fitted_screen_width;
	uint16_t height = (uint16_t)(width / target_aspect_ratio + 0.5f);

	if (height > fitted_screen_height)
	{
		height = fitted_screen_height;
		width = (int)(height * target_aspect_ratio + 0.5f);
	}

	uint16_t viewport_offset_x = (screen_width * 0.5f) - (width * 0.5f);
	uint16_t viewport_offset_y = (screen_height * 0.5f) - (height * 0.5f);

	draw_resolution_x = width;
	draw_resolution_y = height;

	//zel_set_viewport(viewport_offset_x, viewport_offset_y, width, height);
	zel_blit_framebuffer_color_depth_nearest(viewport_offset_x, viewport_offset_y, width, height);
}