#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
uniform vec2 lineDir; // This should be set to the normalized direction vector of the line
uniform float lineWidth; // The width of the line

void main()
{
    vec2 direction = normalize(lineDir);
    float projectionDistance = dot(TexCoords, direction);

    float distToCenterLine = distance(vec2(projectionDistance, 0.0), TexCoords);
    float alpha = 1.0 - smoothstep(lineWidth / 2.0 - 0.1, lineWidth / 2.0, distToCenterLine);

    if (distance(vec2(projectionDistance, 0.0), TexCoords) > lineWidth / 2.0)
        discard;

    FragColor = vec4(1.0, 0.0, 0.0, alpha); // red color with computed alpha
}
