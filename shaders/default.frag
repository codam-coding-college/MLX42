#version 330 core

in vec2 TexCoord;
flat in int TexIndex;

out vec4 FragColor;

uniform sampler2D Textures[16];

void main()
{
    vec4 outColor = vec4(1.0, 0.0, 0.0, 1.0);
    if (TexIndex >= 0 && TexIndex < 16)
    {
        outColor = texture(Textures[TexIndex], TexCoord);
    }
    FragColor = outColor;
}
