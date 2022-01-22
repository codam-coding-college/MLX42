# MLX42

Project still WIP!

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Linux](https://svgshare.com/i/Zhy.svg)](https://svgshare.com/i/Zhy.svg)
[![macOS](https://svgshare.com/i/ZjP.svg)](https://svgshare.com/i/ZjP.svg)
[![Windows](https://svgshare.com/i/ZhY.svg)](https://svgshare.com/i/ZhY.svg)

My own recreation of the MiniLibX library used by 42, using GLFW &amp; glad, running on OpenGL 3.3.
The goal of MLX42 is to replace the outdated and stale MiniLibX library.

## Differences to MiniLibX
#### No Images
Instead of having separate "Images" (textures) there's only a single buffer used to draw the pixels.

#### Custom XPM (XPM42) format
A custom simple to use XPM-like format which has some minor differences to the XPM3 format.

#### Cross-Platform
The main idea of MLX42 is to be a cross-platform graphics interface. In 42 everything runs (currently) on MacOS, but it's
very useful to be able to work remotely on different machines. With MiniLibX this is not possible.

#### Misc
 - Yes, MLX42 adheres 99.98% to the latest norme. 
 - 100% Documented, making it very beginner-friendly and easy to use.
 - Running with OpenGL 3.3.
 
## Installation

In the very end a library is generated, compile your program with this library!

### For MacOS:

1. Download MLX42
```bash 
➜  ~ git clone https://github.com/W2Codam/MLX42.git
```

### Via Homebrew / Homebrew42 by building from source.

2. Install GLFW
```bash
➜  ~ brew update
➜  ~ brew install glfw
```

3. Compile MLX42
```bash 
➜  ~ cd MLX42
➜  ~ make
```

4. Compile Program
With normal brew you can now simply compile the program with:
```bash
➜  ~ gcc main.c mlx42.a -lglfw ...
```

However, with 42Homebrew you have additionally specify the location of the library like here:
```bash
➜  ~ gcc main.c mlx42.a -I include -lglfw -L "/Users/$USER/.brew/opt/glfw/lib/"
```

### Pre-compiled libraries

1. Download the binaries directly [here.](https://www.glfw.org/download.html)

2. If possible move the contents of `lib` and `include` of GLFW to `/usr/local/lib` and `/usr/local/include` respectively.
   If not possible, move the lib file to the root of MLX42 and move the GLFW directory in include to the include of MLX42.
   NOTE: For the lib choose the appropriate `.a` & `.dylib` file depending on your architecture.

3. Compile MLX42
```bash 
➜  ~ cd MLX42
➜  ~ make
```

When compiling with the static library, directly you should compile your program like this:
```bash
➜  ~ gcc main.c mlx42.a libglfw3.a ... -framework Cocoa -framework OpenGL -framework IOKit
```
Else, simply compile like this:
```bash
➜  ~ gcc main.c mlx42.a -lglfw ...
```

4. Run

In case of any security warnings or MacOS telling you it can't verify the author/developer, go to ```Settings > Security & Privacy```.
There will be a pop-up at the bottom telling you that an application tried to run, click the option to let it run.

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

3. Navigate to the extracted GLFW directory and run:
```bash 
➜  ~ cmake -G "Unix Makefiles"
➜  ~ make
➜  ~ sudo make install
➜  ~ sudo apt-get install libx11-dev libglu1-mesa-dev freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libgl1-mesa-glx libgl1-mesa-dev libglfw3-dev libglfw3
```
4. Download MLX42 & Build
```bash 
➜  ~ git clone https://github.com/W2Codam/MLX42.git
➜  ~ cd MLX42
➜  ~ make
```
5. Create a ```main.c``` file, include ```MLX42/MLX42.h```, compile with:
 - ```-ldl -lglfw -lGL -lX11 -lpthread -lXrandr -lXi```, make sure to also do ```-I <include_path>```. At the very least ```-ldl -lglfw``` are required.
6. Run.

The systems below have not been tested yet.

### For Windows:

1. Download & Install MinGW: [Here!](https://sourceforge.net/projects/mingw/)

2. Simply click continue, select whatever your choice is. 
   Once reaching the MinGW Installation Manager select:
    - mingw32-base
    - mingw32-gcc-g++ 

3. Apply by going to `Installation > Apply Changes`, after it's done, you may close the window.

4. Download & Install CMake: [Here!](https://cmake.org/download/), use the installer. Simply select all default options.

5. Download & Install GnuWin: [Here!](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download?use_mirror=altushost-swe&download=)

6. If you used all default options, add these paths to your SYSTEM Environment variables:
  - C:\MinGW\bin
  - C:\Program Files\CMake\bin
  - C:\Program Files (x86)\GnuWin32\bin

7. Download GLFW: https://www.glfw.org/download.html

8. Open the terminal and type `cmake-gui`, select the downloaded/extracted
   source folder, select any place you want the build output to be.

9. Click on configure once and select the `MinGW Makefiles`, then finish.

10. Set the CMAKE_INSTALL_PREFIX to `C:/GLFW`

11. Click on configure again, and then generate.

12. Go to the build directory and do:
 - `make`
 - `make install`

13. Go to the directory you assigned in Step 10. Copy the GLFW folder in the include folder to the MLX include folder & copy the .a file in the lib folder to `C:\MinGW\lib`.

#### NOTE: As of now the build script for windows does not exist, compile by adding every c file manually.

14. Compile your program with these flags:
 - `-lglfw3`
 - `-lopengl32`
 - `-lgdi32`
 
 In the end you should have something like:
```bash
➜  ~ gcc main.c <Additional .c Files> mlx42.a -lglfw3 -lopengl32 -lgdi32
```

15. Run.

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

int32_t    main(void)
{
    t_mlx    *mlx;

    mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
    if (!mlx)
        exit(EXIT_FAILURE);
    mlx_loop_hook(mlx, &hook, mlx);
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
}
```
