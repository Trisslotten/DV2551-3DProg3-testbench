#pragma once
#include "ConstantBuffer.h"
#include "../include/vulkan/vulkan.h"

class ConstantBufferVK : public ConstantBuffer
{
public:
	ConstantBufferVK(std::string NAME, unsigned int location);
	ConstantBufferVK(std::string NAME, unsigned int location, VkDevice device, VkPhysicalDevice pdevice);
	~ConstantBufferVK();
	void setData(const void* data, size_t size, Material* m, unsigned int location);
	void bind(Material*);
	VkBufferCreateInfo bufferInfo;
	VkDescriptorSetLayoutBinding uboLayoutBinding;
private:
	bool init = false;
	VkBuffer _handle;
	std::string name;
	uint32_t location;
	uint32_t handle;
	uint32_t index;
	void* buff = nullptr;
	void* lastMat;
	VkDevice _device;
	VkPhysicalDevice _physicalDevice;
	VkDeviceMemory cBufferMemory;
};
