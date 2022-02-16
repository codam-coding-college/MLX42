/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_png.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 23:11:29 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/17 00:03:55 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

/**
 * Decode/load a PNG file onto a buffer.
 * 
 * NOTE: BPP will always be 4 due using decode32.
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
	error = lodepng_decode32_file(&(image->pixels), \
	((uint32_t *)&image->width), ((uint32_t *)&image->height), path);
	if (error)
	{
		free(image);
		return ((void *)mlx_log(MLX_ERROR, lodepng_error_text(error)));
	}
	image->bytes_per_pixel = sizeof(int32_t);
	return (image);
}
