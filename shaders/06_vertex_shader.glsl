#version 330 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;
void main() {
    gl_Position = projectionTransform * viewTransform * modelTransform * vec4(aPosition, 1.0);
    TexCoord = aTexCoord;
}