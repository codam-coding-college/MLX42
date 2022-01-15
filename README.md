# MLX42

Project still WIP!

My own recreation of the MiniLibX library used by 42, using glfw &amp; glad, running on OpenGL 3.3.
The goal of MLX42 is to replace the outdated and stale MiniLibX library.

## Differences to MiniLibX
#### No Images
Instead of having separate "Images" (textures) theres only a single buffer used to draw the pixels.

#### Custom XPM (XPM42) format
A custom simple to use XPM-like format which is has some minor differences to the XPM3 format.

#### Cross-Platform
The main idea of MLX42 is to be a cross-platform graphics interface, in 42 everything runs (currently) on MacOS but its
very useful to be able to work remotley on different machines. With MiniLibX this is not possible.

#### Misc
 - Yes, MLX42 adheres 99.98% to the latest norme. 
 - 100% Documented, making it very beginner friendly and easy to use.
 - Running with OpenGL 3.3
 
## Installation

In the very end a library is generated, compile your program with this library!

### For MacOS:
1. Install GLFW

You can either install via ```Homebrew```:
```bash
➜  ~ brew update
➜  ~ brew install glfw
```
Or download the binaries directly [here.](https://github.com/glfw/glfw/releases/download/3.3.6/glfw-3.3.6.zip)

Make sure the binary is located (usually at) ```/usr/local/lib``` & the header is at ```/usr/local/include/GLFW```
if those directories do not exist, create them and move the installed dylib and header to their respective locations.

In case of installation via ```Homebrew``` glfw will be located at ```/opt/homebrew/Cellar/glfw/3.3.6```

2. Download MLX42 & Build
```bash 
➜  ~ git clone https://github.com/W2Codam/MLX42.git
➜  ~ make
```
3. Create a ```main.c``` file, include ```MLX42/MLX42.h```, compile with ```-lglfw```.
4. Run.

Incase of any security warnings or MacOS telling you it can't verify the author/developer. Go to ```Settings > Security & Privacy```
There will be a popup at the bottom telling you that an application tried to run, click the option to let it run.

### For Linux:

NOTE: This will not run with Windows Subsystem for Linux (WSL)!!!

1. Download GLFW: [Click Me!](https://github.com/glfw/glfw/releases/download/3.3.6/glfw-3.3.6.zip)
2. Extract GLFW, and to install, run the following commands:
```bash 
➜  ~ sudo apt update
➜  ~ sudo apt install build-essential
➜  ~ sudo apt install cmake
➜  ~ sudo apt install xorg-dev
```
NOTE: For arch-linux you might also have to do ```sudo apt-get install glfw-x11``` if available.

3. Naviagte to the extracted GLFW directory and run:
```bash 
➜  ~ cmake -G "Unix Makefiles"
➜  ~ make
➜  ~ sudo make install
➜  ~ sudo apt-get install libx11-dev libglu1-mesa-dev freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libgl1-mesa-glx libgl1-mesa-dev libglfw3-dev libglfw3
```
4. Download MLX42 & Build
```bash 
➜  ~ git clone https://github.com/W2Codam/MLX42.git
➜  ~ make
```
5. Create a ```main.c``` file, include ```MLX42/MLX42.h```, compile with:
 - ```-ldl -lglfw -lGL -lX11 -lpthread -lXrandr -lXi```, make sure to also do ```-I <include_path>```. At the very least ```-ldl -lglfw``` are required.
6. Run.

The systems below have not been tested yet.

### For Windows:
- Switch to MacOS or Linux, as there is no CMake or way to compile for it yet.

## Example

```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/15 15:42:00 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/01/16 00:05:27 by w2wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define WIDTH 800
#define HEIGHT 600

int32_t    create_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void    hook(void *param)
{
    if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
        mlx_quit(param);

    for (int32_t x = 0; x < WIDTH; x++)
        for (int32_t y = 0; y < HEIGHT; y++)
            mlx_putpixel(param, x, y, create_rgba(\
            rand() % 255, rand() % 255, rand() % 255, rand() % 255));
}

int32_t    main(int32_t argc, char const *argv[])
{
    t_mlx    *mlx;

    (void) argc;
    (void) argv;
    mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
    if (!mlx)
        exit(EXIT_FAILURE);
    mlx_loop_hook(mlx, &hook, mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}
```