#pragma once
#include "VertexBuffer.h"
#include "../include/vulkan/vulkan.h"
#include "VKRenderer.h"
#include <array>

class VertexBufferVK :
	public VertexBuffer
{
public:
	VertexBufferVK(size_t size, VertexBuffer::DATA_USAGE usage, VKRenderer* renderer);
	VertexBufferVK(size_t size, VertexBuffer::DATA_USAGE usage);
	~VertexBufferVK();

	void setData(const void* data, size_t size, size_t offset);
	void bind(size_t offset, size_t size, unsigned int location);
	void unbind();
	size_t getSize();

	DATA_USAGE usage;
	VkVertexInputBindingDescription bindingDescription;
	VkBufferCreateInfo bufferInfo;
	std::array<VkVertexInputAttributeDescription, 1> attributeDescriptions = {};
	//static GLuint usageMapping[3];

private:
	size_t totalSize;
	VKRenderer* _renderer;
	VkBuffer _handle;
	VkDeviceMemory vertexBufferMemory;
};