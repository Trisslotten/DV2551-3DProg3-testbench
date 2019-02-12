#include "VertexBufferVK.h"

#include <math.h>

VertexBufferVK::VertexBufferVK(size_t size, VertexBuffer::DATA_USAGE usage, VKRenderer* renderer)
{
	totalSize = size;
	this->usage = usage;
	this->_renderer = renderer;

	bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(_renderer->device, &bufferInfo, nullptr, &_handle) != VK_SUCCESS) {
		throw std::runtime_error("failed to create vertex buffer!");
	}
	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(_renderer->device, _handle, &memRequirements);
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(_renderer->physicalDevice, &memProperties);
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
	if (vkAllocateMemory(_renderer->device, &allocInfo, nullptr, &vertexBufferMemory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate vertex buffer memory!");
	}
}

VertexBufferVK::~VertexBufferVK()
{
	vkDestroyBuffer(_renderer->device, _handle, nullptr);
	vkDestroyBuffer(_renderer->device, _handle, nullptr);
	vkFreeMemory(_renderer->device, vertexBufferMemory, nullptr);
}

void VertexBufferVK::setData(const void * data, size_t size, size_t offset)
{
	vkBindBufferMemory(_renderer->device, _handle, vertexBufferMemory, offset);
	vkMapMemory(_renderer->device, vertexBufferMemory, offset, bufferInfo.size, 0, (void**)&data);
}

void VertexBufferVK::bind(size_t offset, size_t size, unsigned int location)
{
	bindingDescription.binding = 0;
	bindingDescription.stride = size;
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	
	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = location;

	attributeDescriptions[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	attributeDescriptions[0].offset = offset;
}

void VertexBufferVK::unbind()
{

}

size_t VertexBufferVK::getSize()
{
	return size_t();
}