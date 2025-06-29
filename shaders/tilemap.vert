#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec2 objectOffset;
layout (location = 3) in vec2 atlasOffset;

out vec2 TexCoord;

// Separate transformation matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    // Apply object offset first, then transform through matrices
    vec2 offsetPosition = position + objectOffset;
    gl_Position = projection * view * model * vec4(offsetPosition, 0.0, 1.0);
    TexCoord = (texCoord + atlasOffset / 10.0) / 3.0; // Размер текстурного атласа 30x30px, тайлы 10x10px
}
