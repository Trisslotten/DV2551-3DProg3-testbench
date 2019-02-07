#include "VKRenderer.h"

VKRenderer* vkr;
int main() {
	vkr = new VKRenderer();
	vkr->initialize();
	system("pause");
	return 0;
}