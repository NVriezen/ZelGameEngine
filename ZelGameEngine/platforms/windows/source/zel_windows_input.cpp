#include <zel_input.h>
#include <zel_windows_input.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//Raw
uint32_t* current_input;
uint32_t* previous_input;
//float* ranges;

GLFWwindow* main_window;

void zel_windows_input_init(zel_window_t* window)
{
	main_window = (GLFWwindow*)window;

	current_input = new uint32_t[(GLFW_KEY_LAST >> 5) + 1]{ 0 };
	previous_input = new uint32_t[(GLFW_KEY_LAST >> 5) + 1]{ 0 };
}

bool zel_input_get_key_press(zel_key button)
{
	uint8_t index1 = button >> 5; //same as (button / 32)
	uint8_t index = button % 32;
	return (current_input[index1] & (1 << index)) & ~(previous_input[index1] & (1 << index));
}

bool zel_input_get_key_release(zel_key button)
{
	uint8_t index1 = button >> 5; //same as (button / 32)
	uint8_t index = button % 32;
	return ~(current_input[index1] & (1 << index)) & (previous_input[index1] & (1 << index));
}

bool zel_input_get_key_hold(zel_key button)
{
	uint8_t index1 = button >> 5; //same as (button / 32)
	uint8_t index = button % 32;
	return (current_input[index1] & (1 << index)) & (previous_input[index1] & (1 << index));
}

void zel_input_update()
{
	for (size_t i = 0; i < ((GLFW_KEY_LAST >> 5) + 1); i++)
	{
		previous_input[i] = current_input[i];
	}
}

void zel_input_windows_key_callback(int key, int scancode, int action, int mods)
{
	uint8_t index1 = key >> 5; //same as (button / 32)
	uint8_t index = key % 32;

	previous_input[index1] |= current_input[index1] & (1 << index);

	current_input[index1] = current_input[index1] & ~(1 << index);
	current_input[index1] = current_input[index1] | (action << index);
}