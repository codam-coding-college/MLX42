# Images, how do they work?

Images are pretty much pixel buffers that keep track of how many copies/instances it has on the window, each instance is simply an X Y Z coordinate resulting in a plane that then displays the contents of the pixel buffer.

A change in the buffer results in a change for all currently displayed instances.

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
 * @param enabled If true the image is drawn onto the screen, else its not.
 * @param context Abstracted OpenGL data.
 */
typedef struct mlx_image
{
	const uint32_t	width;
	const uint32_t	height;
	uint8_t*        pixels;
	mlx_instance_t* instances;
	int32_t		count;
	bool		enabled;
	void*           context;
}	mlx_image_t;

```

It holds the `width`, `height` and `pixels`. However images can have instances, that is, copies of itself that share the same pixel buffer.
This makes it easy to make for instance, a row of trees. They all hold the same pixel information, just different locations. Additionally the entire image can be toggled for rendering via the `enabled` boolean.

All that is needed is to call the `mlx_image_to_window` function to create a new copy/instance. However its also possible to move the location of individual image instances quite easily:

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

Keep in mind that after roughly 10K images that are being put on the window, they start to not appear anymore.

## Internals

A noticeable feature of MLX42 is that it partly takes care of the rendering for you, that is, after you created your image you just display it and after that feel free to modify it without having re-put it onto the window. In short MLX takes care of updating your images at all times.

Internally this is via a render queue, anytime the `mlx_image_to_window` function is used, a new entry is added into a linked list.
Every frame MLX will iterate over this linked list and execute a drawcall to draw that image onto the window.

## Functions

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

MLX42 works similarly to minilibx in regards to how images are drawn onto the window.

## Example

Example will create a new image and randomize its pixels every frame.

```c
#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 256
#define HEIGHT 256

static mlx_image_t	*g_img;

void	hook(void* param)
{
	mlx_t* mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_P))
		mlx_delete_image(mlx, g_img);
	for (int x = 0; x < g_img->width; x++)
		for(int y= 0; y < g_img->height; y++)
			mlx_put_pixel(g_img, x, y, rand() % RAND_MAX);
}

int32_t	main(void)
{
	mlx_t*    mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, 128, 128);
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

```