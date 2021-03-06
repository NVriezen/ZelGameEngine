#pragma once
#include <zel_base.h>
#include <zel_math.h>

uint32_t zel_framebuffer_create(uint16_t width, uint16_t height);
void zel_framebuffer_bind_default();
void zel_framebuffer_bind(uint32_t framebuffer_id);

void zel_clear_depth();
void zel_clear_screen(float red, float green, float blue, float alpha);

void zel_set_viewport(uint16_t offset_x, uint16_t offset_y, uint16_t width, uint16_t height);
void zel_blit_framebuffer_color_depth_nearest(uint16_t offset_x, uint16_t offset_y, uint16_t width, uint16_t height);
void zel_render_elements(uint32_t type, uint32_t count, uint32_t var_type, const void* stride);
void zel_use_program(uint16_t shader_program);
void zel_destroy_program(uint16_t shader_program);
void zel_set_uniform_matrix4fv(uint32_t uniform_location, uint8_t count, uint8_t b, glm::mat4 matrix);
void zel_set_uniform_1i(uint32_t uniform_location, uint32_t value);