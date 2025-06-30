#version 330 core

// Base quad vertices (normalized 0-1)
layout (location = 0) in vec2 position;

// Instance data
layout (location = 2) in vec2 instancePos;
layout (location = 3) in vec2 instanceSize;
layout (location = 4) in vec4 instanceColor;

// For batched rendering, we use combined matrix since instances handle transforms
uniform mat4 projection;

out vec4 vertexColor;

void main()
{
    // Transform normalized quad to world position
    vec2 worldPos = instancePos + position * instanceSize;
    
    gl_Position = projection * vec4(worldPos, 0.0, 1.0);
    vertexColor = instanceColor;
}