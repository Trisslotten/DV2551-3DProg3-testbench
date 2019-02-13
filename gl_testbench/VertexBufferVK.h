#pragma once
#include "VertexBuffer.h"
#include "../include/vulkan/vulkan.h"
#include <array>

class VertexBufferVK :
	public VertexBuffer
{
public:
	VertexBufferVK(size_t size, VertexBuffer::DATA_USAGE usage, VkDevice device, VkPhysicalDevice pdevice);
	VertexBufferVK(size_t size, VertexBuffer::DATA_USAGE usage);
	~VertexBufferVK();

	void setData(const void* data, size_t size, size_t offset);
	void bind(size_t offset, size_t size, unsigned int location);
	void unbind();
	size_t getSize();

	DATA_USAGE usage;
	VkVertexInputBindingDescription bindingDescription;
	VkBufferCreateInfo bufferInfo;
	VkVertexInputAttributeDescription attributeDescription;
	//static GLuint usageMapping[3];
	VkBuffer _handle;
private:
	size_t totalSize;
	//VKRenderer* _renderer;
	VkDevice _device;
	VkPhysicalDevice _physicalDevice;
	
	VkDeviceMemory vertexBufferMemory;
};