#version 330 core

// Base quad vertices (normalized 0-1)
layout (location = 0) in vec2 position;

// Instance data - mat4 takes 4 attribute locations (1-4)
layout (location = 1) in mat4 instanceTransform;
layout (location = 5) in vec4 instanceColor;

// Camera matrices
uniform mat4 projection;
uniform mat4 view;

out vec4 vertexColor;

void main()
{
    // Transform unit quad using instance transform matrix
    gl_Position = projection * view * instanceTransform * vec4(position, 0.0, 1.0);
    vertexColor = instanceColor;
}