#version 330 core

in vec2 TexCoord;
flat in int TexIndex;

out vec4 FragColor;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;
uniform sampler2D Texture4;
uniform sampler2D Texture5;
uniform sampler2D Texture6;
uniform sampler2D Texture7;
uniform sampler2D Texture8;
uniform sampler2D Texture9;
uniform sampler2D Texture10;
uniform sampler2D Texture11;
uniform sampler2D Texture12;
uniform sampler2D Texture13;
uniform sampler2D Texture14;
uniform sampler2D Texture15;

void main()
{
    vec4 outColor = vec4(1.0, 0.0, 0.0, 1.0);
    switch (int(TexIndex)) {
        case 0: outColor = texture(Texture0, TexCoord); break;
        case 1: outColor = texture(Texture1, TexCoord); break;
        case 2: outColor = texture(Texture2, TexCoord); break;
        case 3: outColor = texture(Texture3, TexCoord); break;
        case 4: outColor = texture(Texture4, TexCoord); break;
        case 5: outColor = texture(Texture5, TexCoord); break;
        case 6: outColor = texture(Texture6, TexCoord); break;
        case 7: outColor = texture(Texture7, TexCoord); break;
        case 8: outColor = texture(Texture8, TexCoord); break;
        case 9: outColor = texture(Texture9, TexCoord); break;
        case 10: outColor = texture(Texture10, TexCoord); break;
        case 11: outColor = texture(Texture11, TexCoord); break;
        case 12: outColor = texture(Texture12, TexCoord); break;
        case 13: outColor = texture(Texture13, TexCoord); break;
        case 14: outColor = texture(Texture14, TexCoord); break;
        case 15: outColor = texture(Texture15, TexCoord); break;
        default: outColor = vec4(1.0, 0.0, 0.0, 1.0); break;
    }
    FragColor = outColor;
}
