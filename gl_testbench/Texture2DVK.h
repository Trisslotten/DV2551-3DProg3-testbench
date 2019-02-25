#pragma once

#include "Texture2D.h"
#include <vulkan.h>

class VKRenderer;

class Texture2DVK : public Texture2D
{
	friend class VKRenderer;
	VKRenderer* renderer;

	unsigned int width, height;

	VkImage textureImage;
	VkDeviceMemory textureImageMemory;

	VkImageView textureImageView;


	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	VkImageView createImageView(VkImage image, VkFormat format);

	void createTextureImageView();


public:

	Texture2DVK(VKRenderer* renderer) : renderer(renderer)
	{ 
	}

	// Inherited via Texture2D
	virtual int loadFromFile(std::string filename) override;
	virtual void bind(unsigned int slot) override;
};