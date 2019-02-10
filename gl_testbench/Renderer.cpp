#include "OpenGL/OpenGLRenderer.h"
#include "Renderer.h"
#include "VKRenderer.h"


Renderer* Renderer::makeRenderer(BACKEND option)
{
	if (option == BACKEND::GL45)
		return new OpenGLRenderer();
	if (option == BACKEND::VULKAN)
		return new VKRenderer();
}

