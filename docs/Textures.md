<!----------------------------------------------------------------------------
Copyright @ 2021-2022 Codam Coding College. All rights reserved.
See copyright and license notice in the root project for more information.
----------------------------------------------------------------------------->

# Textures

Textures are disk loaded images stored in memory and hold a buffer of pixel data along with information 
about the image such as width, height, and bytes per pixel.

Textures on their own are not displayed to the screen but have to be displayed using [Images](./Images.md).
To do so you can use the `mlx_texture_to_image` function that creates an image large enough to store the 
texture which then can be displayed.

## Textures vs Images

There might be a bit of confusion at first between what an image and a texture is.

Textures:
* Can be interpreted as a painter's "color palette".
* Created by loading an image file FROM disk.
* Simply contain the pixels, width, height and bytes per pixel information.
* Do not get displayed on the window directly.

Images:
* Can be interpreted as a painter's "canvas".
* Can be created FROM a texture or an empty buffer!
* Carries more information besides what the image buffer is such as instance count.
* Also holds pixel data but is shared among its instances, it is not loaded from disk but stored in memory.

## Example

To summarize, in order to display a sprite image onto our window we would first load the texture from 
disk into our memory and store the information in a `mlx_texture_t*`. After that we create a new `mlx_image_t*` 
based on the information given by the texture and then we can display our image onto the window.

Below is a small code example of how this would be achieved:

```C
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "MLX42/MLX42.h"
#define WIDTH 512
#define HEIGHT 512

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

	// Try to load the file
	mlx_texture_t* texture = mlx_load_png("./temp/sus.png");
	if (!texture)
        error();
	
	// Convert texture to a displayable image
	mlx_image_t* img = mlx_texture_to_image(mlx, texture);
	if (!img)
        error();

	// Display the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

	mlx_loop(mlx);

	// Optional, terminate will clean up any left overs, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_delete_texture(texture);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
```
