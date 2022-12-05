</br>
<div align="center">
  <img src="https://user-images.githubusercontent.com/63303990/150698103-7e908ff3-abf8-4b0f-ad54-07a76b6c45e2.png" alt="42MLX_Logo">
</div>
<div align="center">
  <sub>Written by <a href="https://portfolio.w2wizard.dev/">W2.Wizard</a> for the 42 Network</sub>
    <div align="center">
	</br>
	<img src="https://img.shields.io/github/license/codam-coding-college/MLX42" alt="License GPL2.0"> 
	<img src="https://svgshare.com/i/Zhy.svg" alt="Linux">
	<img src="https://svgshare.com/i/ZjP.svg" alt="MacOS">
	<img src="https://svgshare.com/i/ZhY.sv" alt="Windows">
	<img src="https://github.com/codam-coding-college/MLX42/actions/workflows/ci.yml/badge.svg" alt="Build">
	<img src="https://img.shields.io/github/forks/codam-coding-college/MLX42" alt="Forks">
    </div>
</div>

MLX42 is a performant, easy to use, cross-platform windowing library to create
graphical applications without having to work directly with the native Windowing 
Framework of the given operating system.

Additionally it provides primitive tools for drawing onto the window such as
displaying images from disk or creating a drawing surface to draw pixels on.

# Features

MLX42 comes with a plethora of feature that make using it an actual joy instead of a chore.

## Cross-Platform 🖥️

Run it on your grandma's WindowsXP, on your uncle's debian or on a hipster's MacOS!
No matter what the platform, if MLX42 can build on it, it will run on its native windowing system. 

This allows you to work on your graphics project no matter which machine it is on.

## Documentation 📄

Clean code? Actual documentation and open source ? This library has all kinds of crazy concepts which apparently were never done before!
No more guessing and searching how something functions or is supposed to work.

## Performance 🚀

MLX42 features a few simple technique to improve the rendering performance such as batched rendering.
Compared to [other](https://github.com/42Paris/minilibx-linux) su libraries, MLX42 is roughly 30-50% faster in rendering.

## OpenGL, GLFW && CMake 📙
MLX42 uses the latest and greates versions of OpenGL 4.6, GLFW 3.3 && CMake 3.25.
Granted OpenGL is old, all this library really do is render simple quads with textures.

However with CMake the build system should just work with whatever setup you have on your system

- OpenGL 4.6 for the rendering
- GLFW 3.3 for the native window management.
- CMake 3.25 for the build system.

---

## Installation

A library file is generated in the `build` folder. Compile your program with this library!

### General compilation.

Overall the building of this project is as follows for ALL systems. As long as CMake can make sense of it.

1. Download MLX42
	```bash 
	➜  ~ git clone https://github.com/codam-coding-college/MLX42.git
	```

2. Run `cmake -B build` to build the library. No need to have GLFW installed, CMake will fetch it.

3. Compile your program with the library.
	```bash
	➜  ~ gcc main.c libmlx42.a -I include -framework Cocoa -framework OpenGL -framework IOKit
	```

4. Run!

### MacOS Security:

When running your program in MacOS it may complain, because with Macs you just gotta think different.
In case of any security warnings or MacOS telling you it can't verify the author/developer, go to ```Settings > Security & Privacy```.

There will be a pop-up at the bottom telling you that an application tried to run, click the option to let it run.

----

### For Linux:

1. Install the necessary packages:

For Debian like (Ubuntu, Mint, Pop OS...):
```bash 
➜  ~ sudo apt update
➜  ~ sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev
```

For Arch-linux (Manjaro, Endeavor, Garuda):
```bash
➜  ~ sudo pacman -S glfw-x11
```
OR (if you use sway/wlroots compositor or other wayland compositor)

```bash
➜  ~ sudo pacman -S glfw-wayland
```

2. [Download and build MLX42](#download-and-build---mlx42) 

3. Create a ```main.c``` file, include ```MLX42/MLX42.h```, compile with ```-ldl -lglfw (or -lglfw3) -pthread -lm```, make sure to also do ```-I <include_path>```.
 
4. Run.

----

### For Windows (with Windows Subsystem for Linux 2 (WSL2))

1. Set these variables in your `.zshrc` or `.bashrc`:
```bash
export DISPLAY=$(ip route list default | awk '{print $3}'):0
export LIBGL_ALWAYS_INDIRECT=0
```
(If the DISPLAY export command is failing, see this [StackOverflow](https://stackoverflow.com/a/61110604) post for alternatives)

2. Download and install an XServer application with extended configuration (XMing does not qualify)
VcXsrv works: https://sourceforge.net/projects/vcxsrv/

3. Open Windows Defender Firewall, and follow these steps:
- Go to 'Allow an app or feature through Windows Defender Firewall'
- Change Settings
- Find the installed XServer, for VcXsrv that's 'VcXsrv windows server'
- Enable communication over Private **and** Public network
Optionally you might be able to provide these settings on first launch of the XServer application,
and they might not even show up in the list until the first time you start the app.

4. Start the XLaunch application (for VcXsrv) and provide these configuration settings:
- Leave Display number on auto
- Start no client
- **UNTICK** `Native opengl` option
- **TICK** `Disable access control`
- Finish starting the server

5. Probably all the other steps for Linux apply, just clone, build and run.

----

### For Windows:

1. Download & Install [MinGW](https://sourceforge.net/projects/mingw/)

2. Simply click continue, select whatever your choice is. 
   Once reaching the MinGW Installation Manager select:
    - mingw32-base
    - mingw32-gcc-g++ 

3. Apply by going to `Installation > Apply Changes`, after it's done, you may close the window.

4. Download & Install [CMake](https://cmake.org/download/). 
	- Use the installer and select all default options.

5. For Windows we need to install an additional component to **make** the **make** command available. 

	- Using the [chocolatey package manager](https://chocolatey.org/)
		```bash 
		➜  ~ choco install make
		```
	
	-  Using [GnuWin](https://sourceforge.net/projects/gnuwin32/files/make/3.81/make-3.81.exe/download) (download & install)

6. If you used all default options, add these paths to your SYSTEM Environment variables:
  - C:\MinGW\bin
  - C:\Program Files\CMake\bin
  - C:\Program Files (x86)\GnuWin32\bin

7. Download the [GLFW source package](https://www.glfw.org/download.html) and extract it somewhere.

8. Open the terminal and type `cmake-gui`, select the downloaded/extracted
   source folder, select any place you want the build output to be.

9. Click on configure once and select the `MinGW Makefiles`, then finish.

10. Set the CMAKE_INSTALL_PREFIX to `C:/GLFW`

11. Click on configure again, and then generate.

12. Go to the build directory and do:
 - `make`
 - `make install`

13. Go to the directory you assigned in Step 10. Copy the GLFW folder in the include folder to `C:\MinGW\include` & copy the .a file in the lib folder to `C:\MinGW\lib`.

14. [Download and build MLX42](#download-and-build---mlx42) 

15. Compile your program with these flags:
 - `-lglfw3`
 - `-lopengl32`
 - `-lgdi32`
 
 In the end you should have something like:
```bash
➜  ~ gcc main.c <Additional .c Files> libmlx42.a -lglfw3 -lopengl32 -lgdi32
```

15. Run.

## Download and build - MLX42

```bash 
➜  ~ git clone https://github.com/codam-coding-college/MLX42.git
➜  ~ cd MLX42
➜  ~ make
```

The output library file is called `libmlx42.a`.

## Example

![MLX42](https://user-images.githubusercontent.com/63303990/150696516-95b3cd7b-2740-43c5-bdcd-112193d59e14.gif)

```c
// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include "MLX42/MLX42.h"
#define WIDTH 256
#define HEIGHT 256

mlx_image_t	*g_img;

void	hook(void *param)
{
	const mlx_t	*mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		g_img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		g_img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		g_img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		g_img->instances[0].x += 5;
}

int32_t	main(void)
{
	mlx_t	*mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		return(EXIT_FAILURE);

	g_img = mlx_new_image(mlx, 128, 128);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	mlx_image_to_window(mlx, g_img, 0, 0);

	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

```
