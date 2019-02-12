#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding=0) buffer pos { vec4 position_in[]; };

vec3 colors[3] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

layout(location = 0) out vec3 fragColor;

void main() {
	fragColor = colors[gl_VertexIndex];
	gl_Position = position_in[gl_VertexIndex];
	
}
