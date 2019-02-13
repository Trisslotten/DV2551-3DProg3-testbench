#include "ConstantBufferVK.h"

ConstantBufferVK::ConstantBufferVK(std::string NAME, unsigned int location)
{
}

ConstantBufferVK::ConstantBufferVK(std::string NAME, unsigned int location, VkDevice device, VkPhysicalDevice pdevice)
{
	this->_device = device;
	this->_physicalDevice = pdevice;
	this->name = NAME;
	this->location = location;

}

ConstantBufferVK::~ConstantBufferVK()
{
	vkDestroyBuffer(_device, _handle, nullptr);
	vkFreeMemory(_device, cBufferMemory, nullptr);
}

void ConstantBufferVK::setData(const void * data, size_t size, Material * m, unsigned int location)
{
	if (!init) {
		bufferInfo = {};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(_device, &bufferInfo, nullptr, &_handle) != VK_SUCCESS) {
			throw std::runtime_error("failed to create constant buffer!");
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
		if (vkAllocateMemory(_device, &allocInfo, nullptr, &cBufferMemory) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate constant buffer memory!");
		}
		init = true;
	}
	if (vkBindBufferMemory(_device, _handle, cBufferMemory, 0) != VK_SUCCESS) { // offset);
		throw std::runtime_error("failed to bind constant buffer!");
	}
	vkMapMemory(_device, cBufferMemory, 0, size, 0, (void**)&data);
}

void ConstantBufferVK::bind(Material *)
{
	uboLayoutBinding = {};
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	uboLayoutBinding.pImmutableSamplers = nullptr; // Optional
}
