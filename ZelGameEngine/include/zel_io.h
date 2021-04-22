#pragma once
#include <zel_base.h>

void zel_io_initialization();
char* zel_io_get_absolute_path(const char* relative_path);
char* zel_io_load_file_in_memory(const char* path_to_file, uint64_t* buffer_length);