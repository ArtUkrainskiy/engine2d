#version 330 core
out vec4 color;
uniform vec2 cursorPos;
uniform float time;
uniform vec4 col;
out vec4 fragColor;
void main()
{

    vec2 m_coord = cursorPos;
    //    vec2 m_coord = vec2(400, 300);

    float col = distance(gl_FragCoord.xy, m_coord) * 0.005;
    if (col > .95){
        col = .95;
    }

    if (col < .33){
        col = .33;
    }

    //    vec3 calc = vec3(1.000,0.458,0.313) - col * 0.002;
    fragColor = vec4(0, 0, 0, col);

}