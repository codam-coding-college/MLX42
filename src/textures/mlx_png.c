/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_png.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 23:11:29 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/25 15:17:12 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

t_mlx_texture	*mlx_load_png(const char *path)
{
	uint32_t		error;
	t_mlx_texture	*image;

	image = malloc(sizeof(t_mlx_texture));
	if (!image)
		return ((void *)mlx_error(MLX_MEMFAIL));
	error = lodepng_decode32_file(&image->pixels, &image->width, \
	&image->height, path);
	if (error)
	{
		free(image);
		fprintf(stderr, "MLX42: LodePNG: %s\n", lodepng_error_text(error));
		return ((void *)mlx_error(MLX_INVPNG));
	}
	image->bytes_per_pixel = sizeof(int32_t);
	return (image);
}
