#include "VertexBufferVK.h"
#include "VKRenderer.h"
#include <math.h>

VertexBufferVK::VertexBufferVK(size_t size, VertexBuffer::DATA_USAGE usage, VkDevice device, VkPhysicalDevice pdevice)
{
	totalSize = size;
	this->usage = usage;
	//this->_renderer = renderer;
	this->_device = device;
	this->_physicalDevice = pdevice;

	bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(_device, &bufferInfo, nullptr, &_handle) != VK_SUCCESS) {
		throw std::runtime_error("failed to create vertex buffer!");
	}
	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(_device, _handle, &memRequirements);
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(_physicalDevice, &memProperties);
	uint32_t typeFilter = memRequirements.memoryTypeBits;
	uint32_t choice = 0;
	VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			choice = i;
			break;
		}
	}
	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = choice;
	if (vkAllocateMemory(_device, &allocInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate vertex buffer memory!");
	}

	if (vkBindBufferMemory(_device, _handle, vertexBufferMemory, 0) != VK_SUCCESS) { // offset);
		throw std::runtime_error("failed to bind vertex buffer!");
	}
}

VertexBufferVK::~VertexBufferVK()
{
	vkDestroyBuffer(_device, _handle, nullptr);
	vkFreeMemory(_device, vertexBufferMemory, nullptr);
}

void VertexBufferVK::setData(const void * data, size_t size, size_t offset)
{
	
	
	void* gpuData;
	vkBindBufferMemory(_device, _handle, vertexBufferMemory, 0);// offset);
	if (vkMapMemory(_device, vertexBufferMemory, offset, size, 0, &gpuData) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to map vertex data!");
	}
	memcpy(gpuData, data, (size_t)bufferInfo.size);
	vkUnmapMemory(_device, vertexBufferMemory);
}

void VertexBufferVK::bind(size_t offset, size_t size, unsigned int location)
{

	//attributeDescriptions[0].offset = offset;
}

void VertexBufferVK::unbind()
{

}

size_t VertexBufferVK::getSize()
{
	return size_t();
}
