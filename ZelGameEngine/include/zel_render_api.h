#pragma once
#include <zel_base.h>

void zel_clear_depth();
void zel_clear_screen(float red, float green, float blue, float alpha);
void zel_set_viewport(uint16_t offset_x, uint16_t offset_y, uint16_t width, uint16_t height);