#pragma once

#include "Sampler2D.h"
#include <vulkan.h>


class VKRenderer;

class Sampler2DVK : public Sampler2D
{
	friend class VKRenderer;
	VKRenderer* renderer;

	VkSampler textureSampler;

	VkSamplerCreateInfo samplerInfo = {};

	void finalize();
public:

	Sampler2DVK(VKRenderer* renderer);

	// Inherited via Sampler2D
	virtual void setMagFilter(FILTER filter) override;
	virtual void setMinFilter(FILTER filter) override;
	virtual void setWrap(WRAPPING s, WRAPPING t) override;
};