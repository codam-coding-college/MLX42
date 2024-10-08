# Web

MLX42 supports compilation towards [WASM](https://webassembly.org/). What this means is you can run any application written in C directly in the browser!
This overcomes a lot of issues with for instance showing projects towards others or have an environment where building natively just won't work.

In this README you will learn how to compile your project towards Webassembly and later deploy it on github!

## Pre-requisites

- [Emscripten](https://emscripten.org/), you can install this via brew or read the instructions they provide for [Windows or Linux](https://emscripten.org/docs/getting_started/downloads.html)

## Building

Once you made sure you have emscripten installed (check if `emcc` and `emcake` work).

Run:
```bash
emcmake cmake -B build && cmake --build build --parallel
```

## Modifications

You're only required to do a few modifications to your `main.c`.
For this we will use the demo main provided in the root [readme](../README.md).

Add the following headers at the top:
```c
#include <emscripten/html5.h>
#include <emscripten/emscripten.h>
```

Modify your main:
```c
// Invoked instead of mlx_loop directly.
void emscripten_main_loop() {
    mlx_loop(mlx);
}

int32_t	main(int argc, char **argv)
{
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

    // This function will set up the main loop
    emscripten_set_main_loop(emscripten_main_loop, 0, true);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
```

Thats actually it! It may or may not be necessary to modify your own source code depending on what you do but that's most often not the case.
It is that easy to just re-deploy your own app into webassembly.

## Building

```bash
# Compile C into JS/WASM
emcc -O3 -I include -I mlx -pthread main.c \
    -o ./web/demo.js \
    ./build/libmlx42.a \
    -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 -s WASM=1 \
    -s NO_EXIT_RUNTIME=1 -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
    -s ALLOW_MEMORY_GROWTH

# Navigate into the web folder (if you're running this directly from this repo)
cd web

# Launch local webserver, this is required to make the service worker function.
python3 -m http.server 8000
```

Once the server is up and running all you need to do now is go to [localhost](http://localhost:8000/index.html)
