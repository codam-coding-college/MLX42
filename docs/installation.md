<!----------------------------------------------------------------------------
Copyright @ 2021-2022 Codam Coding College. All rights reserved.
See copyright and license notice in the root project for more information.
----------------------------------------------------------------------------->

# Installation

When building MLX42 you can pass CMake build options to customise you're installation.

These options for MLX42 are... `cmake -DDEBUG=1 -DGLFW_FETCH=0` ...

- `Debug`: Enables assertion macros and compiles with -g in order for debugging with lldb.
- `GLFW_FETCH`: Fetches GLFW if it can't be found on the system at all, allows you to then install it with `sudo make install` under the `build/_deps` folder.
