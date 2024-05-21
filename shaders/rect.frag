#version 330 core
out vec4 color;
uniform vec2 cursorPos;
uniform float time;
uniform vec4 col;
void main()
{
    gl_FragColor = col;
}