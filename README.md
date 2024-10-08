</br>
<div align="center">
  <img src="https://user-images.githubusercontent.com/63303990/150698103-7e908ff3-abf8-4b0f-ad54-07a76b6c45e2.png" alt="42MLX_Logo">
</div>
<div align="center">
  <sub>Written by <a href="https://portfolio.w2wizard.dev/">W2.Wizard</a> for Codam</sub>
    <div align="center">
	</br>
	<img src="https://img.shields.io/github/license/codam-coding-college/MLX42" alt="License GPL2.0"> 
	<img src="https://github.com/codam-coding-college/MLX42/actions/workflows/ci.yml/badge.svg" alt="Build">
	<img src="https://img.shields.io/github/forks/codam-coding-college/MLX42" alt="Forks">
    </div>
</div>

MLX42 is a performant, easy to use, cross-platform, minimal windowing graphics library to create graphical applications without having to work directly with the native windowing framework of the given operating system.

It provides primitive tools to draw textures onto the window as well as modifying them at runtime as they get displayed on the window.

> [!IMPORTANT]
> At times it may seem like no updates have taken place for a long time. This is expected, the project / lib is considered completed and requires minimal updates. Bug fixes are still guaranteed and the project is still being actively maintained.

# Features ✨

MLX42 comes with a plethora of features that make using it actually a joy instead of a chore.

## Cross-Platform 🖥️

Run it on your grandma's WindowsXP, on your uncle's debian or on a hipster's MacOS!
No matter what the platform, if MLX42 can build on it, it will run on its native windowing system. 

This allows you to work on your project no matter which machine it is on.

## Documented 📚

MLX42 cares about good documentation, every function, usage and even some internal workings are documented!
No more guessing and searching how something functions or is supposed to work.

## Performance 🚀

It is built on OpenGL and uses batched rendering to speed up the rendering process compared to other libraries.

## Open source && Community driven 🌐
This project is being actively maintained by Codam as well as students from the 42 Network. This gives students the direct opportunity to learn more about the library itself as well as fix any potential bugs instead of merely accepting them.

## Emscripten Compatibility 🚀
MLX42 introduces compatibility with [Emscripten](https://emscripten.org/), allowing MLX42 to run in web browsers through WebAssembly. This modification were made possible thanks to [@PepeLevi](https://github.com/PepeLevi/MLX42_emcc), credits to him for his fork and contributions.

### Highlights
- **Emscripten Support**: Compile MLX42 with Emscripten, enabling graphical applications to run in a web environment.
- **WebAssembly Compatibility**: Ensures that MLX42 can be utilized in modern web browsers, expanding its usability beyond traditional desktop environments.
- **Updated Documentation**: Provided guidance on how to build and run MLX42 projects using Emscripten.

---

## Installation 🏗️
### General compilation

Overall the building of this project is as follows for ALL systems. As long as CMake can make sense of it.

1. [Download and build MLX42](#download-and-build---mlx42) 

In case your system doesn't have [glfw](https://github.com/glfw/glfw) installed cmake will detect this and download it for you.
You can then run `sudo make install` in the `_deps` directory of glfw. If you're using a 42 Computer (MacOS, Linux), ask your favourite sysadmin to install it.
Same goes for CMake or any other dependencies you might need for your system.

However if you can't do either CMake will still be able to fetch GLFW and build it. You can then statically link it from the `_deps` folder.

> [!NOTE]
> For Codam, GLFW is already installed on the Macs.

> [!NOTE]
> During the linking stage, the flag to link GLFW can either be: -lglfw3 or -lglfw depending on your system.

1. Compile your program with the library:
	- For: [MacOS](#for-macos)
	- For: [Linux](#for-linux)
	- For: [Windows](#for-windows)

2. Profit!

### Installing to the system

To fully build the library and install it to your system run the following command:
```bash
cmake -B build && cmake --build build --parallel --config (Debug|Release|RelWithDebInfo|MinSizeRel) --target install
```

By default windows will place the installed lib into: `C:\Program Files (x86)\mlx42` and for MacOS / Linux it will be placed into `/usr/local/lib` and `/usr/local/include` respectively.

### Unit tests
MLX42 comes with some unit tests to ensure the integrity of the library, to build them run the following command:
```sh
cmake -DBUILD_TESTS=ON -B build && cmake --build build --parallel
```

Then simply run them with:
```sh
ctest --output-on-failure --test-dir build
```

----

## Download and build - MLX42

```bash 
git clone https://github.com/codam-coding-college/MLX42.git
cd MLX42
cmake -B build # build here refers to the outputfolder.
cmake --build build -j4 # or do make -C build -j4
```

The output library file is called `libmlx42.a` and is located in the `build` folder that you specified.

### Available Options

You can pass build [options](./docs/index.md#available-options) to cmake, e.g: `cmake -DDEBUG=1 -DGLFW_FETCH=0...`. These will for instance let you build it in DEBUG mode or alter any sort of behaviour at build-time.

You can find an example makefile in the documentation [here](https://github.com/codam-coding-college/MLX42/blob/master/docs/Basics.md).

----

## For MacOS:

### Installing the dependencies

If your system has neither GLFW nor CMake its highly recommended you use brew to install those missing dependencies.

For 42 Campuses you can use: [42Homebrew](https://github.com/kube/42homebrew)

Otherwise with homebrew:
```bash
brew install glfw
brew install cmake
```
If you are using Apple Silicon (M1 chip or later), note that the Homebrew install path is different.
You may want to update your shell configuration file. For Zsh users (default shell on newer macOS versions):
```bash
nano ~/.zshrc
export LIBRARY_PATH=/opt/homebrew/lib
```
Restart your shell session or restart your terminal for the changes to take effect.

For MacOS you need to use the following flags to compile your program with the library
in order to link the program with the correct frameworks:
```bash
-framework Cocoa -framework OpenGL -framework IOKit
```

Normally if you simply installed / built `glfw` from source or already have it installed
the compilation should be:
```bash
gcc main.c ... libmlx42.a -Iinclude -lglfw
```

#### Via [Homebrew](https://brew.sh/) / [42Homebrew](https://github.com/kube/42homebrew)
```bash
# Homebrew
gcc main.c ... libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"

# 42Homebrew
gcc main.c ... libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
```

#### MacOS Security:

When running your program in MacOS it may complain, because with Macs you just gotta think differently.
In case of any security warnings or MacOS telling you it can't verify the author/developer, go to ```Settings > Security & Privacy```.

There will be a pop-up at the bottom telling you that an application tried to run, click the option to let it run.

----

## For Linux:

1. Install the necessary packages:

For Debian like (Ubuntu, Mint, Pop OS...):
```bash 
sudo apt update
sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev
```

For Arch-linux (Manjaro, Endeavor, Garuda):
```bash
sudo pacman -S glfw-x11
```
OR (if you use sway/wlroots compositor or other wayland compositor)

```bash
sudo pacman -S glfw-wayland
```

2. [Download and build MLX42](#download-and-build---mlx42) 

3. Compile your program with the library:

```bash
gcc main.c ... libmlx42.a -Iinclude -ldl -lglfw -pthread -lm
```
4. Profit!

----

## For Windows (with Windows Subsystem for Linux 2 (WSL2))

> [!IMPORTANT]
> Before starting with all these steps, [read this](https://learn.microsoft.com/en-us/windows/wsl/tutorials/gui-apps)

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

## For Windows Native:

> [!IMPORTANT]
> Be aware that Visual Studio (2022) is required for this. Developing on Windows can be somewhat frustrating.

We highly recommend you simply use [WSL2](#for-windows-with-windows-subsystem-for-linux-2-wsl2) to make this as painless as possible.
However if you insist on building for windows natively then all you need in terms of dependencies is:

- [CMake](https://cmake.org/download/)
- [GLFW](https://www.glfw.org/download.html)

Once you have all the dependencies correctly installed `CMake` will generate
the visual studio project files. Simply build it and once you have a `.lib` file
move them to your actual project and install them as you would with any other library.

Just in case here's a [video](https://youtu.be/or1dAmUO8k0?t=494) showing you how this can be done. Conveniently this video also covers how you can link `glfw`.

Of course it's up to you to make sure that the code you write is portable. Things that exist on `Unix` don't necessarily exist on `Win32`.

## Example

![MLX42](docs/assets/demo.gif)

```c
// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(void)
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

```
