#pragma once
#include <zel_base.h>

void zel_init_io();
char* zel_get_absolute_path(const char* relative_path);
char* zel_load_file_in_memory(const char* path_to_file, uint64_t* buffer_length);