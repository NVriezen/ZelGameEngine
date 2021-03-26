#pragma once
#include <zel_base.h>

typedef void* zel_window_t;

uint8_t zel_window_create(zel_window_t* window);
void zel_window_destroy(zel_window_t window);
void zel_window_update(zel_window_t window);
void zel_window_terminate();