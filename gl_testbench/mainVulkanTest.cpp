#include "VKRenderer.h"

#include "MaterialVK.h"

VKRenderer* vkr;
int main() {
	vkr = new VKRenderer();
	vkr->setClearColor(0.0f, 0.1f, 0.1f, 1.0f);
	vkr->initialize(800, 600);

	
	auto vkm = new MaterialVK(vkr);
	vkm->setShader("../assets/vulkan/shader.frag", Material::ShaderType::PS);
	vkm->compileMaterial(std::string());


	SDL_Event windowEvent;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
			if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
		}
		vkr->frame();
		vkr->present();
	}
	vkr->shutdown();
	delete vkr;
	system("pause");
	return 0;
}