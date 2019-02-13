#version 450
#define POSITION 0
#define NORMAL 1
#define TEXTCOORD 2
#define TRANSLATION 5
#define TRANSLATION_NAME TranslationBlock
#define DIFFUSE_TINT 6
#define DIFFUSE_TINT_NAME DiffuseColor

//#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(1, 0, 0, 1.0);
}