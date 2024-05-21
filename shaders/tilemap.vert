#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec2 objectOffset;
layout (location = 3) in vec2 atlasOffset;
out vec2 TexCoord;
uniform mat4 projection;
void main() {
    gl_Position = projection * vec4(position + objectOffset, 0.0, 1.0);
    TexCoord = (texCoord + atlasOffset / 10.0) / 3.0;// Размер текстурного атласа 30x30px, тайлы 10x10px
}
