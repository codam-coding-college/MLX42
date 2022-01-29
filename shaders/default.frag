
#version 330 core

in vec2 TexCoord;
out vec4 FragColor;  
uniform sampler2D outTexture;

void main()
{
	// Hack for now, this is not ideal...
    vec4 texColor = texture(outTexture, TexCoord);
    if(texColor.a < 0.01f)
        discard;
    FragColor = texColor;
}
