#include "VKRenderer.h"

VKRenderer* vkr;
int main() {
	vkr = new VKRenderer();
	vkr->initialize(800, 600);
	system("pause");
	return 0;
}