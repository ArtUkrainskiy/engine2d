#version 330 core
layout (location = 0) in vec2 position;

// Separate transformation matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Optional uniforms for compatibility
uniform vec2 cursorPos;
uniform float time;

void main()
{
    gl_Position = projection * view * model * vec4(position, 0.0, 1.0);
}
