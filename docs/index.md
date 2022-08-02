<!--
-----------------------------------------------------------------------------
Copyright @ 2021-2022 Codam Coding College. All rights reserved.
See copyright and license notice in the root project for more information.
-----------------------------------------------------------------------------
-->

</br>
<div align="center">
  <img src="./assets/logo.png" alt="42MLX_Logo">
</div>
<div align="center" style="margin-top: 8px;">
  <sub>Written by <a href="https://portfolio.w2wizard.dev/">W2.Wizard</a> for the 42 Network</sub>
</div>
</br>

<div align="center">
    <h1>Welcome to the MLX42 documentation</h1>
</div>

# Introduction

MLX42 is a performant, easy to use, cross-platform windowing library to create
graphical applications without having to work directly with the native Windowing 
Framework of the given operating system.

Additionally it provides primitive tools for drawing onto the window such as
displaying images from disk or creating a drawing surface to draw pixels on.

## Support

Currently supported operating systems:
| Operating system 	| Version                                     	|
|------------------	|---------------------------------------------	|
| `Windows NT`      | Windows 7 - Windows 11                      	|
| `MacOS`           | Mojave - Monterey (Including Apple Silicon) 	|
| `Linux`           | Anything running X11 / Wayland              	|

## Initialization

The very first step for initialization is to execute the mlx_init function.
It is responsible to setup the GLFW windowing library which 
creates a connection between your software and the display. It also loads the 
OpenGL function pointers, compiling the shaders and more.

It returns a mlx_t* which is a structure containing the current window instance.
With this instance you can manipulate, hook onto and control what happens inside 
your window instance. For example you would use it to send graphical orders such as 
creating an image, which is used to display pixel data. You can also detect key
interactions such as checking if the W, A, S or D key is currently being pressed.

| Function          | Description                                                  |
|-------------------|--------------------------------------------------------------|
| `mlx_init()`      | Initialize and run a new window instance.                    |
| `mlx_loop()`      | Keep the window open as long as a shutdown is not requested. |
| `mlx_terminate()` | Destroy and cleanup all images and mlx resources.            |

If mlx_init() fails to set up the connection to the graphical system, it will
return NULL, otherwise a non-null pointer is returned as a handle for the window.

## Linking

In order to use the functions in MLX, you'll need to link it with your application.

To do this, simply add the following arguments at the linking stage:
| Operating System | Flags                                                         |
|------------------|---------------------------------------------------------------|
| `Windows NT`     | -lglfw3 -lopengl32 -lgdi32                                    |
| `MacOS`          | -lglfw(3) -framework Cocoa -framework OpenGL -framework IOKit |
| `Linux`          | -ldl -lglfw(3) -pthread -lm                                   |

**NOTE: For some UNIX systems the flag for glfw might be with or without a 3 at the end.**

## Debugging

MLX was designed with ease of debugging in mind, therefor if the project is build with
**make DEBUG=1** it will keep in the assertion macros and notify you of any bad input 
given to functions. Additionally it comes with its own runtime error checking via
**mlx_errno** and **mlx_strerror** to properly identify what went wrong during the runtime 
of the library.

## Notes

Keep in mind while technically MLX42
does support multiple window instances it currently has no functional support for
it. That is, no proper way of handling multiple windows.

