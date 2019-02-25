//#version 450
#extension GL_ARB_separate_shader_objects : enable


layout(location = POSITION) in vec4 pos;
layout(location = NORMAL) in vec4 normal;
layout(location = TEXTCOORD) in vec2 uv;

layout(binding = TRANSLATION) uniform TRANSLATION_NAME {
	vec4 translate;
} trans;

layout(location = 0) out vec2 v_uv;

void main() {
    vec4 pos = vec4(pos.xy + trans.translate.xy, pos.z, 1.0f);
    pos.y *= -1;
	v_uv = uv;
    gl_Position = pos;//vec4(pos.xy + trans.translate.xy, pos.z, 1.0f);
}