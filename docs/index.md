<!----------------------------------------------------------------------------
Copyright @ 2021-2022 Codam Coding College. All rights reserved.
See copyright and license notice in the root project for more information.
----------------------------------------------------------------------------->

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

---

## Toc

* [Basics](./Basics.md)
* [Colors](./Colors.md)
* [Functions](./Functions.md)
* [Hooks](./Hooks.md)
* [Images](./Images.md)
* [Input](./Input.md)
* [Shaders](./Shaders.md)
* [Textures](./Textures.md)
* [XPM42](./XPM42.md)

---

## Support

Currently supported operating systems:
| Operating system 	| Version                                     	|
|------------------	|---------------------------------------------	|
| `Windows NT`      | Windows 7 - Windows 11                      	|
| `MacOS`           | Mojave - Monterey (Including Apple Silicon) 	|
| `Linux`           | Anything running X11 / Wayland              	|

## Initialization

The very first step for initialization is to execute the mlx_init function.
It is responsible for setting up the GLFW windowing library which 
creates a connection between your software and the display. It also loads the 
OpenGL function pointers, compiling the shaders and more.

It returns a mlx_t* which is a structure containing the current window instance.
With this instance you can manipulate, hook onto and control what happens inside 
your window instance. For example you would use it to send graphical instructions such as 
creating an image, which is used to display pixel data. You can also detect key
interactions such as checking if the W, A, S or D key is currently being pressed.

| Function          | Description                                                  |
|-------------------|--------------------------------------------------------------|
| `mlx_init()`      | Initialize and run a new window instance.                    |
| `mlx_loop()`      | Keep the window open as long as a shutdown is not requested. |
| `mlx_terminate()` | Destroy and clean up all images and mlx resources.            |

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

## Build options

When building MLX42 you can pass certain build options to cmake.

The options are passed as follows `cmake -DDEBUG=1 -DGLFW_FETCH=0`.

### Available options

* `DEBUG`: Enables assertion macros and compiles with -g in order for debugging with lldb.
* `GLFW_FETCH`: Fetches GLFW if it can't be found on the system at all, allows you to then install it with `sudo make install` under the `build/_deps` folder.

## Debugging

MLX was designed with ease of debugging in mind, therefore if the project is built with
**cmake -DDEBUG=1** it will keep in the assertion macros and notify you of any bad input
given to functions. Additionally it comes with its own runtime error checking via
**mlx_errno** and **mlx_strerror** to properly identify what went wrong during the runtime
of the library.

## Notes

Keep in mind that while technically MLX42
does support multiple window instances it currently has no functional support for
it. That is, no proper way of handling multiple windows.

---

## F.A.Q

Q: **_"It'S NoT In ThE SuBjeCt!"_**

A: So what? Subjects can change and so if something is not working correctly it should be replaced. Sure you can argue this point but you can also be the reason that it CAN be in the subject instead. Have an open mind :)

Q: **_"Ok, so, can I use it ?"_**

A: Officially, _no_. However, ask your head of studies first about using it, see what they think. Some students might be evangelical enthusiasts about what is stated in the subject and are technically in every right to fail you as long as this library is not endorsed, if you were to ask me (W2) then yes why not?

Q: **_"Is it faster?"_**

A: From my personal projects there was a considerable performance gain, especially when compiled with `-Ofast`. Projects such as FDF could rotate their maps mindblowingly smooth and even larger maps with a width and height of 1000+ points moved/rotated relatively smooth, so in short, yes.

Q: **_"Can I just drag and drop it into my old project and just not do anything?"_**

A: No. That's not how libraries work. Sure they target and do sort of the same thing but the functions each library provides are too different, even a little bit in terms of behavior. And no there is no easy way to convert from the "old" to the "new" it will be somewhat tedious work.

Q: **_"We should be able to deal with the fact that MiniLibX is not perfect, it is by design and makes us better programmers."_**

A: Struggle does bring out the best in most people but it is also not ideal in this case. I think so at least, that it's really expected that libraries that are publicly available should be usable, stable, easy to use and well documented. Nobody uses a library because it is annoying to work with and afterwards think to themselves they have learned something after they are done struggling. The only thing people learn from this is how to navigate around the shortcomings instead.

Q: **_"Why not use some other library? Why this one and not any other library."_**

A: It is your choice what to use! I wrote this in my free time in an attempt to introduce some good change and to improve the learning experience at 42. If you don't like my library at least let me know what it is so I can improve on it.

Q: **_"Do you hate MiniLibX? Is this some personal vendetta, do you work for the CIA ?"_**

A: No, I just want to improve 42, that's it.
