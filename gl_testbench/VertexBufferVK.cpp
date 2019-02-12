#include "VertexBufferVK.h"

#include <math.h>

VertexBufferVK::VertexBufferVK(size_t size, VertexBuffer::DATA_USAGE usage, VKRenderer* renderer)
{
	totalSize = size;
	this->usage = usage;
	this->_renderer = renderer;

	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(renderer->device, &bufferInfo, nullptr, &_handle) != VK_SUCCESS) {
		throw std::runtime_error("failed to create vertex buffer!");
	}
}

VertexBufferVK::~VertexBufferVK()
{
	vkDestroyBuffer(device, _handle, nullptr);
}

uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);
}

void VertexBufferVK::setData(const void * data, size_t size, size_t offset)
{
	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(device, _handle, &memRequirements);

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
