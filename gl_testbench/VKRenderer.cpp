#include "VKRenderer.h"
#include <iostream>

VKRenderer::VKRenderer() {

}

int VKRenderer::initialize(unsigned int width, unsigned int height) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "%s", SDL_GetError());
		exit(-1);
	}
	window = SDL_CreateWindow("Vulkan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_VULKAN);

	this->createInstance();
	this->pickPhysicalDevice();
	this->createSurface();

	//create window etc.

	return 1; //change?
}

void VKRenderer::createSurface() {
	if (!SDL_Vulkan_CreateSurface(window, instance, &surface)) {
		throw std::runtime_error("failed to create vulkan surface from SDL!");
	}

	//do more?

	printf("Created VkSurface from STL\n");
}

void VKRenderer::createInstance() {
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Vulkan Renderer";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	
	unsigned int count;
	if (!SDL_Vulkan_GetInstanceExtensions(window, &count, nullptr)) {
		throw std::runtime_error("failed to get SDL Vulkan Extensions!");
	}

	std::vector<const char*> extensions = {
		VK_EXT_DEBUG_REPORT_EXTENSION_NAME // Sample additional extension
	};
	size_t additional_extension_count = extensions.size();
	extensions.resize(additional_extension_count + count);

	if (!SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data() + additional_extension_count)) {
		throw std::runtime_error("failed to get SDL Vulkan Extensions!");
	}


	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	printf("Loaded Vulkan Extensions:\n");
	for (const char* ext : extensions) {
		printf("%s\n", ext);
	}

	//validation layers?

	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
	printf("Created VKInstance! \n");
}

bool isDeviceSuitable(VkPhysicalDevice device) {
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
	//add requirements
	return true;
}

void VKRenderer::pickPhysicalDevice() {
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	//count devices
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}
	
	//list devices
	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
	for (const auto& device : devices) {
		if (isDeviceSuitable(device)) {
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
	printf("Picked device with name: %s. \n", deviceProperties.deviceName);
}

int VKRenderer::shutdown() {
	vkDestroyInstance(instance, nullptr);
	
	//destroy sdl window here
	SDL_Quit();

	return 0;
}