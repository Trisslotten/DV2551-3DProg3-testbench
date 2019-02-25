#include "Sampler2DVK.h"

#include <exception>
#include "VKRenderer.h"

void Sampler2DVK::finalize()
{
	if (vkCreateSampler(renderer->device, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create texture sampler!");
	}
}

Sampler2DVK::Sampler2DVK(VKRenderer * renderer)
{
	this->renderer = renderer;

	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;

	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

	samplerInfo.anisotropyEnable = VK_FALSE;
	samplerInfo.maxAnisotropy = 1;

	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;

	samplerInfo.unnormalizedCoordinates = VK_FALSE;

	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.mipLodBias = 0.0f;
	samplerInfo.minLod = 0.0f;
	samplerInfo.maxLod = 0.0f;
}

void Sampler2DVK::setMagFilter(FILTER filter)
{
	switch (filter)
	{
	case FILTER::LINEAR:
		samplerInfo.magFilter = VK_FILTER_LINEAR;
		break;
	case FILTER::POINT_SAMPLER:
		samplerInfo.magFilter = VK_FILTER_NEAREST;
		break;
	}
}

void Sampler2DVK::setMinFilter(FILTER filter)
{
	switch (filter)
	{
	case FILTER::LINEAR:
		samplerInfo.minFilter = VK_FILTER_LINEAR;
		break;
	case FILTER::POINT_SAMPLER:
		samplerInfo.minFilter = VK_FILTER_NEAREST;
		break;
	}
}

void Sampler2DVK::setWrap(WRAPPING s, WRAPPING t)
{
	switch (s)
	{
	case WRAPPING::CLAMP:
		samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		break;
	case WRAPPING::REPEAT:
		samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		break;
	}
	switch (t)
	{
	case WRAPPING::CLAMP:
		samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
		break;
	case WRAPPING::REPEAT:
		samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		break;
	}
}
