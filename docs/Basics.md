# How to start with MLX42

Starting off MLX is very straight forward, once you followed the installation instructions on the README.

`NOTE: Compile MLX42 with DEBUG=1 to see assertions and to add debug flags.`

In this section we will go over basic window creation and making an image move, which could serve as a basis for making a
very simple 2D game!

## Making a simple window

To make a window there are two components, initialization and the loop.

Initialization leads to the creation of the mlx handle which contains relevant information regarding the graphics interface.

```c
typedef struct mlx
{
    void*	window;     // Window pointer, only really relevant to MLX itself.
    void*	context;    // Abstracted data only relevant to MLX & OpenGL.
    int32_t	width;      // The current width of the window, gets updated on resize.
    int32_t	height;     // The current height of the window, gets updated on resize.
    double	delta_time; // The time it took to draw the last frame, useful to interpolations.
}   mlx_t;
```

### Inner workings

Internally `mlx_init()` does a whole bunch of stuff, mainly it creates the OpenGL window hints, creates a window context and also compiles the shaders. It also declares the vertexattribute layout (Describes what kind of data vertices store) in the case of MLX only the `vertex position` and `uv` coordinates matter. Vertex color information is just redundant in this case. Finally it also creates the vertex buffer object and array.

The reason the window pointer exists outside of the context object is mainly for convenience of the developer of MLX, most other stuff like the `VBO`, `VAO` & `Shaderprogram` are stored in the context object.

### Example

```c
#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#define WIDTH 256
#define HEIGHT 256

int32_t	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
```

## Making an image

To learn more about images go to the [image](https://github.com/W2Codam/MLX42/wiki/Images) section.

```c
#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#define WIDTH 256
#define HEIGHT 256

static mlx_image_t *g_img;

int32_t	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
        g_img = mlx_new_image(mlx, 128, 128);   // Creates a new image.
        mlx_image_to_window(mlx, g_img, 0, 0);  // Adds an image to the render queue.
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img); // Once the application request an exit, cleanup.
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
```

## Putting a single pixel


```c
#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#define WIDTH 256
#define HEIGHT 256

static mlx_image_t *g_img;

int32_t	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
        g_img = mlx_new_image(mlx, 128, 128);    // Creates a new image.
        mlx_image_to_window(mlx, g_img, 0, 0);   // Adds an image to the render queue.
        mlx_put_pixel(g_img, 64, 64, 0xFFFFFFFF); // Single white pixel in the middle.
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img); // Once the application request an exit, cleanup.
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
```

## Makefile Example

If you're curious as to how to configure a makefile with MLX42 here is a Makefile example from a project. Use this as a guide on how to compile MLX42 and use it in your application.

```make
# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/18 19:27:43 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/02/23 12:46:32 by lde-la-h      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# //= Variables =//

NAME	= FDF
CFLAGS	= -w -Wunreachable-code -Ofast
LIBMLX	= ./lib/MLX42
LIBFT	= ./lib/libft

HEADERS	= -I ./include -I $(LIBMLX)/include -I $(LIBFT)
LIBS	= -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/ $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a
SRCS	= $(shell find ./src -iname "*.c")
OBJS	= ${SRCS:.c=.o}

BOLD	= \033[1m
BLACK	= \033[30;1m
RED	= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
BLUE	= \033[34;1m
MAGENTA	= \033[35;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

# //= Recipes =//

all: libft libmlx $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

libmlx:
	@$(MAKE) -C $(LIBMLX)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBMLX) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
```