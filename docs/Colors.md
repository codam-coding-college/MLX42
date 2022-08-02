<!----------------------------------------------------------------------------
Copyright @ 2021-2022 Codam Coding College. All rights reserved.
See copyright and license notice in the root project for more information.
----------------------------------------------------------------------------->

# Colors
Colors are a fundamental concept in graphics programming. A common color model is RGBA, which MLX uses for storing and displaying images.

## Composition
Colors are commonly represented as `4-byte` integers. This 4-byte integer is a grouping of four individual channels: red, green, blue and alpha, with alpha representing transparency. Additionally, colors are usually shown in hexadecimal to make each channel value identifiable:

Channel | Description   | RGBA representation
:------:|:-------------:|:-------------------:
`R`     | Red Channel   | `0xFF000000`
`G`     | Blue Channel  | `0x00FF0000`
`B`     | Green Channel | `0x0000FF00`
`A`     | Alpha Channel | `0x000000FF`

Combining these four channel values into one will result in a non-transparent, white color.

## Encoding & Decoding

In order to set each channel's byte we can use bit-shifting operations.

A function that combines four individual channel bytes into a single integer using bit-shifting looks like this:

```c
// 'Encodes' four individual bytes into an int.
int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
```

We can also do the reverse to retrieve each individual byte again:

```c
// Get the red channel.
int get_r(int rgba)
{
    // Move 3 bytes to the right and mask out the first byte.
    return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
int get_g(int rgba)
{
    // Move 2 bytes to the right and mask out the first byte.
    return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
int get_b(int rgba)
{
    // Move 1 byte to the right and mask out the first byte.
    return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
int get_a(int rgba)
{
    // Move 0 bytes to the right and mask out the first byte.
    return (rgba & 0xFF);
}
```

## Example

In this small example we will create a white image:

```c
#include "MLX42/MLX42.h"

// Bytes Per Pixel. Since each pixel is represented as an integer, it will be four bytes for four channels.
#define BPP sizeof(int32_t)

int32_t	main(void)
{
    // Init mlx with a canvas size of 256x256 and the ability to resize the window.
    mlx_t* mlx = mlx_init(256, 256, "MLX42", true);
    
    if (!mlx) exit(EXIT_FAILURE);

    // Create a 128x128 image.
    mlx_image_t* img = mlx_new_image(mlx, 128, 128);

    // Set the channels of each pixel in our image to the maximum byte value of 255. 
    memset(img->pixels, 255, img->width * img->height * BPP);

    // Draw the image at coordinate (0, 0).
    mlx_image_to_window(mlx, img, 0, 0);

    // Run the main loop and terminate on quit.  
    mlx_loop(mlx);
    mlx_terminate(mlx);

    return (EXIT_SUCCESS);
}

```