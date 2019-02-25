#include "MaterialVK.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <vulkan.h>

void MaterialVK::expandShader(std::string & shader, ShaderType type)
{
	auto elem = shaderDefines.find(type);
	if (elem != shaderDefines.end())
	{
		for (auto define : elem->second)
		{
			shader = define + "\n" + shader;
		}
	}
	shader = "#version 450\n" + shader;
}

void MaterialVK::setShader(const std::string & shaderFileName, ShaderType type)
{
	auto elem = shaderFileNames.find(type);
	if (elem != shaderFileNames.end())
		removeShader(type);

	shaderFileNames[type] = shaderFileName;
}

void MaterialVK::removeShader(ShaderType type)
{
}

void MaterialVK::setDiffuse(Color c)
{
	color = c;
}

static std::vector<char> readBinFile(const std::string& filename)
{
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open())
	{
		//throw std::runtime_error("failed to open file!");
		return std::vector<char>();
	}
	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}

VkShaderModule MaterialVK::createShaderModule(const std::vector<char>& code)
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(renderer->device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create shader module!");
	}

	return shaderModule;
}

// TODO: error checking
int MaterialVK::compileMaterial(std::string & errString)
{
	for (auto elem : shaderFileNames)
	{
		std::ifstream file(elem.second);
		std::string shaderText((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

		expandShader(shaderText, elem.first);

		file.close();

		std::ofstream temp("../assets/vulkan/temp.glsl");
		temp << shaderText;
		temp.close();

		std::string compiledFilename = elem.second + ".spv";
		remove(compiledFilename.c_str());

		std::string command = "..\\assets\\vulkan\\glslangValidator.exe -V ../assets/vulkan/temp.glsl -S ";
		if (elem.first == ShaderType::VS)
			command += "vert";
		if (elem.first == ShaderType::PS)
			command += "frag";
		command += " -o " + compiledFilename;

		system(command.c_str());

		auto spv = readBinFile(compiledFilename);
		if (spv.size() == 0)
		{
			errString = "Could not compile shader: '" + elem.second + "'";
			return -1;
		}
		remove(compiledFilename.c_str());

		VkShaderModule shaderModule = createShaderModule(spv);

		VkPipelineShaderStageCreateInfo shaderStageInfo = {};
		shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		if (elem.first == ShaderType::VS)
			shaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		if (elem.first == ShaderType::PS)
			shaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		shaderStageInfo.module = shaderModule;
		shaderStageInfo.pName = "main";

		shaderStageInfos[(int)elem.first] = shaderStageInfo;
	}
	return 0;
}

void MaterialVK::addConstantBuffer(std::string name, unsigned int location)
{
	constantBuffers[location] = renderer->makeConstantBuffer(name, location);
}

void MaterialVK::updateConstantBuffer(const void * data, size_t size, unsigned int location)
{
	constantBuffers[location]->setData(data, size, this, location);
}

int MaterialVK::enable()
{
	// bind Constant buffer here
	return 0;
}

void MaterialVK::disable()
{
}
