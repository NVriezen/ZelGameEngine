#include <zel_render_api.h>
#include <stdint.h>
#include <glad\glad.h>

void zel_clear_depth()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void zel_clear_screen(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

void zel_set_viewport(uint16_t offset_x, uint16_t offset_y, uint16_t width, uint16_t height)
{
	glViewport(offset_x, offset_y, width, height);
}