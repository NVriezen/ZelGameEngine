#pragma once
#include <zel_base.h>
#include <zel_platform_base.h>
#include <zel_level.h>

typedef uint16_t zel_key;

bool zel_input_get_key_press(zel_key button);
bool zel_input_get_key_release(zel_key button);
bool zel_input_get_key_hold(zel_key button);
void zel_input_update();