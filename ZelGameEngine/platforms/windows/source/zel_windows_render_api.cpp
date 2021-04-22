#include <zel_render_api.h>
#include <glad\glad.h>
#include <zel_logging.h>
#include <zel_rendering_utils.h>

#include <zel_math.h>

uint32_t zel_framebuffer_create(uint16_t width, uint16_t height)
{
	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	//Color buffer
	GLuint color_buffer_texture;
	glGenTextures(1, &color_buffer_texture);
	glBindTexture(GL_TEXTURE_2D, color_buffer_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_buffer_texture, 0);

	//Depth buffer
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		zel_print("Something went wrong while creating a framebuffer.\n");
	}

	return fbo;
}

void zel_framebuffer_bind_default()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	zel_screen_swap_blit(screen_resolution_x, screen_resolution_y, game_resolution_x, game_resolution_y);
}

void zel_framebuffer_bind(uint32_t framebuffer_id)
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_id);
}

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

void zel_blit_framebuffer_color_depth_nearest(uint16_t offset_x, uint16_t offset_y, uint16_t width, uint16_t height)
{
	glBlitFramebuffer(0, 0, game_resolution_x, game_resolution_y, offset_x, offset_y, offset_x + width, offset_y + height, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
}

void zel_render_elements(uint32_t type, uint32_t count, uint32_t var_type, const void* stride)
{
	glDrawElements(type, count, var_type, stride);
}

void zel_use_program(uint16_t shader_program)
{
	glUseProgram(shader_program);
}

void zel_destroy_program(uint16_t shader_program)
{
	glDeleteProgram(shader_program);
}

void zel_set_uniform_matrix4fv(uint32_t uniform_location, uint8_t count, uint8_t b, glm::mat4 matrix)
{
	glUniformMatrix4fv(uniform_location, count, b, glm::value_ptr(matrix));
}

void zel_set_uniform_1i(uint32_t uniform_location, uint32_t value)
{
	glUniform1i(uniform_location, value);
}