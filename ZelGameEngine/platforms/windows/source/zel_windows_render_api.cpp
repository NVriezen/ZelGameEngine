#include <zel_render_api.h>
#include <glad\glad.h>

#include <zel_math.h>

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

void zel_render_elements(uint32_t type, uint32_t count, uint32_t var_type, uint32_t stride)
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void zel_use_program(uint16_t shader_program)
{
	glUseProgram(shader_program);
}

void zel_set_uniform_matrix4fv(uint32_t uniform_location, uint8_t count, uint8_t b, glm::mat4 matrix)
{
	glUniformMatrix4fv(uniform_location, count, b, glm::value_ptr(matrix));
}

void zel_set_uniform_1i(uint32_t uniform_location, uint32_t value)
{
	glUniform1i(uniform_location, value);
}