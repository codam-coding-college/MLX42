<!----------------------------------------------------------------------------
Copyright @ 2021-2022 Codam Coding College. All rights reserved.
See copyright and license notice in the root project for more information.
----------------------------------------------------------------------------->

# Shaders

In computer graphics, a shader is a type of computer program used for shading in 3D/2D scenes (the production of appropriate levels of light, darkness, and color in a rendered image). MLX42 exposes the shaders and compiles them into the library for portability.

```glsl

// Example of shader code, GLSL is similar to C but not quite.

#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
uniform mat4 ProjMatrix;

void main()
{
	gl_Position = ProjMatrix * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}

```

## Beware

Shaders aren't really meant to be used by students but are more there for the convenience of developers. (though some advanced students might make some use of them)

# Compilation

Shaders are converted into a `.c` appropriate format and then compiled into the library and referenced via a `extern` global variable appropriately named `vert_shader` & `frag_shader`. The reason this is done is to keep the final game/executable portable, that is being able to use it at any given location within a filesystem, while still being easy to work on the shaders instead of having to mess with it in the `.c` files directly. 

