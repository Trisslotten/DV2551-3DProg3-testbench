//#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 outColor;

#ifdef DIFFUSE_SLOT
layout(binding = DIFFUSE_SLOT) uniform sampler2D myTex;
#endif

layout(binding = DIFFUSE_TINT) uniform DIFFUSE_TINT_NAME
{
	vec4 diffuseTint;
} tint;

layout(location = 0) in vec2 v_uv;

void main() {

#ifdef DIFFUSE_SLOT
	vec4 col = texture(myTex, v_uv);
#else
	vec4 col = vec4(1.0, 1.0, 1.0, 1.0);
#endif

	outColor = col * vec4(tint.diffuseTint.rgb, 1.0);
}