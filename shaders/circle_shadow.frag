#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

bool lineIntersectsCircle(vec2 linePoint1, vec2 linePoint2, vec2 circleCenter, float circleRadius) {
    // Находим вектор направления прямой
    vec2 lineDirection = normalize(linePoint2 - linePoint1);

    // Находим вектор от одной из точек прямой до центра окружности
    vec2 lineToCenter = circleCenter - linePoint1;

    // Находим проекцию вектора lineToCenter на вектор направления прямой
    float projection = dot(lineToCenter, lineDirection);

    // Если проекция меньше нуля, ближайшая точка на прямой находится перед linePoint1
    // Если проекция больше длины прямой, ближайшая точка на прямой находится за linePoint2
    if (projection < 0.0 || projection > length(linePoint2 - linePoint1)) {
        // Прямая находится за краями вектора, значит ближайшая точка лежит на одном из концов
        // Проверяем расстояние от центра окружности до ближайшего конца прямой
        float distanceToLinePoint1 = distance(circleCenter, linePoint1);
        float distanceToLinePoint2 = distance(circleCenter, linePoint2);
        return distanceToLinePoint1 < circleRadius || distanceToLinePoint2 < circleRadius;
    }

    // Находим ближайшую точку на прямой к центру окружности
    vec2 closestPoint = linePoint1 + lineDirection * projection;

    // Проверяем расстояние от ближайшей точки до центра окружности
    return distance(closestPoint, circleCenter) < circleRadius;
}


void main() {
    vec2 m_coord = u_mouse;
    // vec2 m_coord = u_resolution / 2.;

    vec2 circle = u_resolution/2.;
    float radius = 10.;
    float fade = 5.;
    float color = 0.;

    if (lineIntersectsCircle(gl_FragCoord.xy, m_coord, circle, radius)){

    } else {
        color = distance(gl_FragCoord.xy, m_coord);
        vec3 calc = vec3(1.000, 0.458, 0.313) - color * 0.002;
        gl_FragColor = vec4(calc.xyz, 1);
    }
    // vec2 st = gl_FragCoord.xy/u_resolution;
    // gl_FragColor = vec4(st.x,st.y,0.0,1.0) * color;
}
