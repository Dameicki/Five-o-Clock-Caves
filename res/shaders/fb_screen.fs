#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float brightness;
uniform float contrast;

void main()
{
    vec3 col = texture(screenTexture, TexCoords).rgb;
    col.rgb= (col.rgb - 0.5) * (1.0 + contrast) + 0.5;
    vec3 bright= vec3(brightness,brightness,brightness);
    FragColor = vec4((col+bright), 1.0);
} 