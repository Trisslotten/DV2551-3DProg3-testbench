#pragma once


#include "VKRenderer.h"
#include "Material.h"
#include <string>

class VKMaterial : public Material
{
	VKRenderer* renderer;

	void expandShader(std::string& shader, ShaderType type);
	VkShaderModule createShaderModule(const std::vector<char>& code);

public:

	VKMaterial(VKRenderer* renderer) : renderer(renderer)
	{}

	virtual void setShader(const std::string & shaderFileName, ShaderType type) override;
	virtual void removeShader(ShaderType type) override;
	virtual void setDiffuse(Color c) override;
	virtual int compileMaterial(std::string & errString) override;
	virtual void addConstantBuffer(std::string name, unsigned int location) override;
	virtual void updateConstantBuffer(const void * data, size_t size, unsigned int location) override;
	virtual int enable() override;
	virtual void disable() override;
};