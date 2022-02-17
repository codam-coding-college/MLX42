/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_png.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 23:11:29 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/17 11:04:19 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

/**
 * Decode/load a PNG file onto a buffer. BPP will always be 4.
 * 
 * @note: Yes, we're using a lib, not going to re-invent the wheel here.
 * 
 * @param path Path to the PNG file.
 * @return If successful the texture data is returned, else NULL.
 */
t_mlx_texture	*mlx_decode_png(const char *path)
{
	uint32_t		error;
	t_mlx_texture	*image;

	image = malloc(sizeof(t_mlx_texture));
	if (!image)
		return ((void *)mlx_log(MLX_ERROR, MLX_MEMORY_FAIL));
	error = lodepng_decode32_file(&image->pixels, &image->width, \
	&image->height, path);
	if (error)
	{
		free(image);
		return ((void *)mlx_log(MLX_ERROR, lodepng_error_text(error)));
	}
	image->bytes_per_pixel = sizeof(int32_t);
	return (image);
}
