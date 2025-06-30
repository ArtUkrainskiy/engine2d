#version 330 core

out vec4 FragColor;

void main()
{
    // Цвет фона (голубой)
    vec4 backgroundColor = vec4(63./255., 90./255., 180./255., 1.0);
    // Цвет сетки (белый)
    vec4 gridColor = vec4(1.0, 1.0, 1.0, 1.0);

    vec4 grid10x10Color = mix(gridColor, backgroundColor, 0.9);
    vec4 grid50x50Color = mix(gridColor, backgroundColor, 0.7);
    vec4 gridCrossColor = mix(gridColor, backgroundColor, 0.5);

    // Определяем координаты текущего пикселя
    vec2 uv = gl_FragCoord.xy;

    // Рисуем фон
    FragColor = backgroundColor;

    // Рисуем сетку 10x10
    if (mod(uv.x, 10.0) < 1.0 || mod(uv.y, 10.0) < 1.0) {
        FragColor = grid10x10Color;
    }

    // Рисуем сетку 50x50
    if (mod(uv.x, 50.0) < 1.0 || mod(uv.y, 50.0) < 1.0) {
        FragColor = grid50x50Color;
    }

    // Рисуем прерывистую линию (+)
    if ((mod(abs(uv.x + 5.0), 50.0) < 11.0 && mod(abs(uv.x + 5.0), 50.0) >= 0.0 && mod(abs(uv.y), 50.0) < 1.0) ||
    (mod(abs(uv.y + 5.0), 50.0) < 11.0 && mod(abs(uv.y + 5.0), 50.0) >= 0.0 && mod(abs(uv.x), 50.0) < 1.0)) {
        FragColor = gridCrossColor;
    }
}
