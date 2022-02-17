/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_texture_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 01:02:24 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/17 10:46:00 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

t_mlx_image	*mlx_texture_area_to_image(t_mlx *mlx, t_mlx_texture *texture, \
int32_t xy[2], uint32_t wh[2])
{
	uint32_t	y;
	uint32_t	bpp;
	uint8_t		*pixelx;
	uint8_t		*pixeli;
	t_mlx_image	*image;

	y = 0;
	if (!mlx || !texture || !xy || !wh)
		return ((void *)mlx_log(MLX_WARNING, MLX_NULL_ARG));
	bpp = texture->bytes_per_pixel;
	if (xy[0] > (int32_t)texture->width || xy[1] > (int32_t)texture->height)
		return ((void *)mlx_log(MLX_WARNING, MLX_INVALID_ARG));
	image = mlx_new_image(mlx, wh[0], wh[1]);
	if (!image)
		return ((void *)mlx_log(MLX_ERROR, MLX_MEMORY_FAIL));
	while (y < wh[1])
	{
		pixelx = &texture->pixels[((xy[1] + y) * texture->width + xy[0]) * bpp];
		pixeli = &image->pixels[y * wh[0] * bpp];
		memmove(pixeli, pixelx, wh[0] * bpp);
		y++;
	}
	return (image);
}

t_mlx_image	*mlx_texture_to_image(t_mlx *mlx, t_mlx_texture *texture)
{
	t_mlx_image		*img;
	const int32_t	xy[] = {0, 0};
	const uint32_t	wh[] = {texture->width, texture->height};

	if (!mlx || !texture)
		return ((void *)mlx_log(MLX_WARNING, MLX_NULL_ARG));
	img = mlx_texture_area_to_image(mlx, texture, (int32_t *)xy, (uint32_t *)wh);
	if (!img)
		return ((void *)mlx_log(MLX_ERROR, MLX_MEMORY_FAIL));
	return (img);
}
