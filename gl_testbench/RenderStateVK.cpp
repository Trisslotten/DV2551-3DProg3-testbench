#include "RenderStateVK.h"
#include "VKRenderer.h"

RenderStateVK::RenderStateVK() {}
RenderStateVK::~RenderStateVK() {}

void RenderStateVK::setWireFrame(bool wireFrame) {
	_wireframe = wireFrame;
}
void RenderStateVK::set() {
	//???
}

void RenderStateVK::setGlobalWireFrame(bool* global) {
	globalWireFrame = global;
}