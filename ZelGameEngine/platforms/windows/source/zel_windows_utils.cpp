#include <zel_platform_utils.h>
#define GLFW_INCLUDE_NONE
#include <GLFW\glfw3.h>
#include <glad\glad.h> // for opengl stuff

double zel_get_time()
{
	return glfwGetTime();
}