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

A recreation of the MiniLibX library used by 42, using GLFW & glad, running on OpenGL.
The goal of MLX42 is to replace the outdated and stale MiniLibX library.

For information and documentation about MLX42 check the wiki.

## Differences to MiniLibX

#### Cross-Platform
The main idea of MLX42 is to be a cross-platform graphics interface. In 42 everything runs (currently) on MacOS, but it's
very useful to be able to work remotely on different machines. With MiniLibX this is not possible.

#### Documented
Almost all functions and types are fully documented giving you a clue as to how to approach and use the library.
No more guessing and searching how something functions or is supposed to work.

#### Custom XPM (XPM42) format
A custom simple to use XPM-like format which has some minor differences to the XPM3 format.

#### Almost identical usage to MiniLibX
Switching to MLX42 from MiniLibX is not a lot of work, most features present in MiniLibX are also present in MLX42, albeit with different prototypes.

---

## Installation

In the very end a library is generated, compile your program with this library!

### For MacOS:

1. Download MLX42
```bash 
➜  ~ git clone https://github.com/codam-coding-college/MLX42.git
```

### Via [Homebrew](https://brew.sh/) / [Homebrew42](https://github.com/kube/42homebrew) by building from source.

2. Install GLFW

Through brew:
```bash
➜  ~ brew update
➜  ~ brew install glfw
```

If you're studying at Codam you can simply link GLFW normally since its now installed on the macs.

3. [Download and build MLX42](#download-and-build---mlx42) 

4. Compile Program

With the normal brew version you can now simply compile the program with:
```bash
➜  ~ gcc main.c libmlx42.a -lglfw ...
```

You might have to specify the location explicitly:
```bash
➜  ~ gcc main.c libmlx42.a -lglfw -L /opt/homebrew/Cellar/glfw/3.3.6/lib/
```

However, with 42Homebrew you have additionally specify the location of the library like here:
```bash
➜  ~ gcc main.c libmlx42.a -I include -lglfw -L "/Users/$USER/.brew/opt/glfw/lib/"
```

Or, if studying at Codam, compile using the following flags:
```bash
➜  ~ gcc main.c libmlx42.a -I include -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
```

5. Run!

----

### Pre-compiled libraries (GLFW)

2. Download the binaries directly [here](https://www.glfw.org/download.html).

3. If possible move the contents of `lib` and `include` of GLFW to `/usr/local/lib` and `/usr/local/include` respectively.
   If not possible, move the lib file to the root of MLX42 and move the GLFW directory in include to the include of MLX42.
   NOTE: For the lib choose the appropriate `.a` & `.dylib` file depending on your architecture.

4. [Download and build MLX42](#download-and-build---mlx42) 

When compiling with the static library, directly you should compile your program like this:
```bash
➜  ~ gcc main.c libmlx42.a libglfw3.a ... -framework Cocoa -framework OpenGL -framework IOKit
```
Else, simply compile like this:
```bash
➜  ~ gcc main.c libmlx42.a -lglfw ...
```

5. Run

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
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 00:40:08 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/31 00:41:56 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 256
#define HEIGHT 256

mlx_image_t	*g_img;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
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

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 128, 128);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

```
