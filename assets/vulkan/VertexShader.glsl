//#version 450
#extension GL_ARB_separate_shader_objects : enable


layout(location = POSITION) in vec4 pos;
layout(location = NORMAL) in vec4 normal;
layout(location = TEXTCOORD) in vec2 uv;

//layout(location = 0) out vec3 fragColor;

void main() {
    gl_Position = vec4(pos.xyz, 1.0);
}