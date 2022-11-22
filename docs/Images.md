<!----------------------------------------------------------------------------
Copyright @ 2021-2022 Codam Coding College. All rights reserved.
See copyright and license notice in the root project for more information.
----------------------------------------------------------------------------->

# Images

Images are like a canvas for a painting, they are used to display pixel information onto the window and work with something called instances.
Instances are copies of the canvas and let you display an image multiple times throughout the window. The idea behind it is that you already 
have the pixel information in memory and you can simply create duplicates everywhere.

Each instance has an X, Y and Z parameter to determine their position and depth.
A change in the image's buffer results in a change for all currently displayed instances.

An image on its own is very simple:
```c
/**
 * An image with an individual buffer that can be rendered.
 * Any value can be modified except the width/height and context.
 * 
 * @param width The width of the image.
 * @param height The height of the image.
 * @param pixels The literal pixel data.
 * @param instances An instance carries the X, Y, Z location data.
 * @param count The element count of the instances array.
 * @param enabled If true the image is drawn onto the screen, else it's not.
 * @param context Abstracted OpenGL data.
 */
typedef struct mlx_image
{
	const uint32_t	width;
	const uint32_t	height;
	uint8_t*		pixels;
	mlx_instance_t*	instances;
	int32_t			count;
	bool			enabled;
	void*			context;
}	mlx_image_t;
```

To display the image all that is needed is to call the `mlx_image_to_window` function to create a new copy/instance:
```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "MLX42/MLX42.h"
#define WIDTH 5120
#define HEIGHT 2880

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(void)
{
	// Start mlx
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();

	// Create a new image
	mlx_image_t* img = mlx_new_image(mlx, 512, 512);
	if (!img)
		error();

	// Set every pixel to white
	memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));

	// Display an instance of the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

	mlx_loop(mlx);

	// Optional, terminate will clean up any left overs, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
```

After we have put an instance of an image onto the window we can simply change the position of the image at any time
we want it to be moved:
```c
// Modify the x & y position of an already existing instance.
img->instances[0].x += 5;
img->instances[0].y += 5;
```

## Transparency
In regards to transparency, aka the `z` value, use `mlx_set_instance_depth` to set the z/depth value of the image.
The z value determines the depth of the image, as in, is it in the foreground or background.

If two instances are on the same z layer and are transparent, the transparency breaks and the instances cut off each other.
To prevent this by default any new instances put onto window will be on their own layer.

## Internals
A noticeable feature of MLX42 is that it partly takes care of the rendering for you, that is, after you created your image you just display it 
and after that feel free to modify it without having to re-put it onto the window. In short MLX takes care of updating your images at all times.

Internally this is done via a render queue, anytime the `mlx_image_to_window` function is used, a new entry is added to a linked list.
Every frame MLX will iterate over this linked list and execute a drawcall to draw that image onto the window.

## Common functions

```c
// Creates a whole new image.
mlx_image_t* mlx_new_image(mlx_t* mlx, uint16_t width, uint16_t height)
```

```c
// Creates a new instance/copy of an already existing image.
void mlx_image_to_window(mlx_image_t* img, int32_t x, int32_t y)
```

```c
// Deletes an image and removes it from the render queue.
void mlx_delete_image(mlx* mlx, mlx_image_t* image)
```
