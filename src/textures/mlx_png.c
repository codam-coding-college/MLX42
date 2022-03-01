/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_png.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 23:11:29 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 23:05:02 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

mlx_texture_t* mlx_load_png(const char* path)
{
	uint32_t error;
	mlx_texture_t* image;

	if (!(image = malloc(sizeof(t_mlx_texture));)))
		return ((void*)mlx_error(MLX_MEMFAIL));

	image->bytes_per_pixel = sizeof(int32_t);
	if ((error = lodepng_decode32_file(&image->pixels, &image->width, &image->height, path)))
	{
		free(image);

		// Explicitly print error on purpose
		fprintf(stderr, "MLX42: LodePNG: %s\n", lodepng_error_text(error));
		return ((void *)mlx_error(MLX_INVPNG));
	}
	return (image);
}
