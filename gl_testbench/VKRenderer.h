#pragma once
#include "Renderer.h"
#include <vulkan.hpp>

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"vulkan-1.lib")

class VKRenderer : public Renderer 
{
private:
	VkPhysicalDevice device;
};