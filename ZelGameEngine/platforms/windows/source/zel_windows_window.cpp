#include <zel_window.h>
#define GLFW_INCLUDE_NONE
#include <GLFW\glfw3.h>
#include <glad\glad.h> // for opengl stuff
#include <zel_base.h>
#include <zel_logging.h>
#include <zel_rendering_utils.h>

// GLFW Callbacks
void error_callback(int error, const char* description);
void window_close_callback(GLFWwindow* window_closing);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

uint8_t zel_window_create(zel_window_t* window)
{
	if (!glfwInit())
	{
		// initialization failed!
		zel_print("Failed to initialize GLFW\n");
		return 1;
	}

	zel_print("Zel Game Engine V0.0.10 by NVriezen 2021\n");
	glfwSetErrorCallback(error_callback);

	// create window with minimal OpenGL 2.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* glfw_window = glfwCreateWindow(480, 270, "Zel Template Game", NULL, NULL);
	if (!glfw_window)
	{
		// window or openGL context creation failed
		// update drivers or check hardware
		zel_print("Failed to open window.\n Please check your drivers or hardware.\n");
		glfwTerminate();
		return 2;
	}

	glfwMakeContextCurrent(glfw_window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		zel_print("Failed to initialize GLAD\n");
		return 3;
	}

	// some callbacks
	glfwSetWindowCloseCallback(glfw_window, window_close_callback);
	glfwSetKeyCallback(glfw_window, key_callback);
	glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);

	glfwSwapInterval(0);

	(*window) = (zel_window_t)glfw_window;

	return 0;
}

void zel_window_destroy(zel_window_t window)
{
	glfwDestroyWindow((GLFWwindow*)window);
}

void zel_window_update(zel_window_t window)
{
	glfwSwapBuffers((GLFWwindow*)window);
	glfwPollEvents();
}

void zel_window_terminate()
{
	glfwTerminate();
}

// GLFW Callbacks
void error_callback(int error, const char* description)
{
	zel_print("Error: %s\n", description);
	zel_engine_running = 1;
}

void window_close_callback(GLFWwindow* window_closing)
{
	zel_print("User wants to close the window.\n");
	zel_engine_running = 1;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	zel_scale_fit_screen(width, height, 480, 270);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	//zel_button_callback(key, scancode, action, mods);
}