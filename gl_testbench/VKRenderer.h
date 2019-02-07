#pragma once
#include "Renderer.h"

#include <SDL.h>
#include <SDL_vulkan.h>
#undef main //?????????????? -> https://stackoverflow.com/questions/6847360/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc
#include <vulkan.h>

#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")
#pragma comment(lib,"vulkan-1.lib")

class VKRenderer// : public Renderer (commented for testing)
{
private:
	SDL_Window *window;

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