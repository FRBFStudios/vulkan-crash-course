#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS

#include <vulkan/vulkan_raii.hpp>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
	void run()
	{
		initWindow();
		initVulkan();
		mainLoop();
		cleanup();
	}

private:
	GLFWwindow* window = nullptr;

	void initWindow()
	{
		glfwSetErrorCallback([](int error, const char* description)
			{
			std::cerr << "GLFW Error " << error
				  << ": " << description << '\n';
			}
		);

		if(!glfwInit()) {
			throw std::runtime_error("GLFW initialization failed");
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
		if(!window) {
			throw std::runtime_error("Window creation failed");
		}
	}

	void initVulkan()
	{

	}

	void mainLoop()
	{
		while(!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

	void cleanup()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
};

int main() {
	try
	{
		HelloTriangleApplication app;
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}