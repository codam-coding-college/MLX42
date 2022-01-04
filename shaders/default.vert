#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
uniform float u_time;
out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}

/*
attribute vec2 position;
uniform vec2 winhalfsize;
uniform vec2 imagepos;
uniform vec2 imagesize;
varying vec2 texcoord;
void main()
{
	texcoord = position / imagesize;
	vec2 pos = position - winhalfsize + imagepos;
	pos = pos / winhalfsize;
	gl_Position = vec4(pos, 0.0, 1.0);
}");
*/