<!----------------------------------------------------------------------------
Copyright @ 2021-2022 Codam Coding College. All rights reserved.
See copyright and license notice in the root project for more information.
----------------------------------------------------------------------------->

# Basics

Before starting please read the [index page](./index.md).
Starting with MLX42 is very straightforward. Here we will make a simple program that will use a makefile and compile
MLX42.

## Makefile Example

If you're curious as to how to configure a makefile with MLX42 here is a Makefile example from a project.
Use this as a guide on how to compile MLX42 and use it in your application.

First of all we need a makefile that can compile our program, below you can see a sample makefile:

```makefile
NAME	:= Game
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./lib/MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
```

## Main

Below is a simple main into starting a window. MLX42 has several nice features that allow you to predefine how it should behave during runtime such as `MLX_HEADLESS` running it without opening a window or `MLX_STRETCH_IMAGE` which stretches the window content with the window size.

The exact structure `mlx_init()` is basically a handle that stores important information
regarding the window and looks as follows:

```c
/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame and the current frame.
 */
typedef struct mlx
{
	void*		window;
	void*		context;
	int32_t		width;
	int32_t		height;
	double		delta_time;
}	mlx_t;
```

Between initializations you can do everything that is required such as drawing your image or opening files.
Once `mlx_loop()` is reached the program remains open until a shutdown is somehow requested, e.g: closing the window.

Because we want programs to be interactive and do stuff it's very useful to hook into the looping process of `mlx_loop()`.
In order to achieve this we use [hooks](./Hooks.md).

`NOTE: Compile MLX42 with DEBUG=1 to see assertions and to add debug flags. This can help you find critical mistakes during development!`

```c
// Written by Bruh

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int32_t	main(void)
{

	// MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();

	/* Do stuff */

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
```
