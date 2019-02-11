#include "VKRenderer.h"

VKRenderer* vkr;
int main() {
	vkr = new VKRenderer();
	vkr->initialize(800, 600);
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