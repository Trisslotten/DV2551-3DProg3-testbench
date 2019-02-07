#pragma once
#include "Renderer.h"
#include <vulkan.hpp>

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"vulkan-1.lib")

class VKRenderer// : public Renderer (commented for testing)
{
private:
	VkInstance instance;
	VkPhysicalDevice device;
	void createInstance();
	void pickPhysicalDevice();
public:
	VKRenderer();
	int initialize(unsigned int width = 640, unsigned int height = 480);
	void setWinTitle(const char* title);
	int shutdown();
};