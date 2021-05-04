#pragma once
#include <zel_base.h>

#define PROFILING 1

extern uint8_t zel_engine_running;

extern uint8_t zel_major_version;
extern uint8_t zel_minor_version;
extern uint32_t zel_build_number;
extern const char* application_name;
extern const uint16_t game_resolution_x;
extern const uint16_t game_resolution_y;
extern uint16_t draw_resolution_x;
extern uint16_t draw_resolution_y;
extern uint16_t screen_resolution_x;
extern uint16_t screen_resolution_y;