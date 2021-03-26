#include <zel_io.h>
#include <zel_logging.h>
#include <fstream>
#include <Windows.h>

static char local_path[MAX_PATH];

void zel_io_initialization()
{
	GetModuleFileNameA(NULL, local_path, MAX_PATH);
	char* chr_pointer = strrchr(local_path, '\\');
	char filename_length = chr_pointer - local_path;
	for (size_t i = 1; i < filename_length; i++)
	{
		chr_pointer[i] = -51;
	}
	chr_pointer[1] = '\0';
}

char* zel_get_absolute_path(const char* relative_path)
{
	char* file_path = new char[MAX_PATH];
	strcpy_s(file_path, MAX_PATH, local_path);
	strcat_s(file_path, MAX_PATH, relative_path);
	return file_path;
}

char* zel_load_file_in_memory(const char* path_to_file, uint64_t* buffer_length)
{
	FILE* file_to_open;
	uint64_t file_length;

	char file_path[MAX_PATH];
	strcpy_s(file_path, local_path);
	strcat_s(file_path, path_to_file);

	errno_t result = fopen_s(&file_to_open, file_path, "rb");
	if (!result)
	{
		zel_print("Could not open file. %s", file_path);
		fclose(file_to_open);
		return nullptr;
	}

	fseek(file_to_open, 0L, SEEK_END);
	file_length = ftell(file_to_open);
	rewind(file_to_open);

	char* file_data = new char[file_length + 1];

	fread(file_data, file_length, 1, file_to_open);
	fclose(file_to_open);

	file_data[file_length] = '\0';

	(*buffer_length) = file_length;

	return file_data;
}