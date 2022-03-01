/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_texture.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 01:02:24 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 23:08:45 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

mlx_image_t* mlx_texture_area_to_image(mlx_t* mlx, mlx_texture_t* texture, int32_t xy[2], uint32_t wh[2])
{
	uint32_t y = 0;
	uint8_t* pixelx;
	uint8_t* pixeli;
	mlx_image_t* image;

	if (!mlx || !texture || !xy || !wh)
		return ((void*)mlx_error(MLX_NULLARG));
	if (xy[0] > (int32_t)texture->width || xy[1] > (int32_t)texture->height)
		return ((void*)mlx_error(MLX_INVAREA));
	if (!(image = mlx_new_image(mlx, wh[0], wh[1])))
		return ((void*)mlx_error(MLX_MEMFAIL));

	uint32_t bpp = texture->bytes_per_pixel;
	while (y < wh[1])
	{
		pixelx = &texture->pixels[((xy[1] + y) * texture->width + xy[0]) * bpp];
		pixeli = &image->pixels[y * wh[0] * bpp];
		memmove(pixeli, pixelx, wh[0] * bpp);
		y++;
	}
	return (image);
}

mlx_image_t* mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture)
{
	mlx_image_t* img;
	const int32_t xy[] = {0, 0};
	const uint32_t wh[] = {texture->width, texture->height};

	if (!mlx || !texture)
		return ((void*)mlx_error(MLX_NULLARG));
	if (!(img = mlx_texture_area_to_image(mlx, texture, (int32_t *)xy, (uint32_t *)wh)))
		return ((void*)mlx_error(MLX_MEMFAIL));
	return (img);
}

bool mlx_draw_texture(mlx_image_t* image, mlx_texture_t* texture, int32_t x, int32_t y)
{
	uint32_t j = 0;
	uint32_t i = 0;
	uint8_t* pixel;

	if (!texture || !image)
		return (mlx_error(MLX_NULLARG));
	if (texture->width > image->width || texture->height > image->height)
		return (mlx_error(MLX_TEXTOBIG));

	// TODO: Remove second while loop, use memmove/cpy, less messy.
	while (i < texture->height)
	{
		j = 0;
		while (j < texture->width)
		{
			pixel = &texture->pixels[(i * texture->width + j) * texture->bytes_per_pixel];
			mlx_putpixel(image, x + j, y + i, *pixel << 24 | *(pixel + 1) << 16 | *(pixel + 2) << 8 | *(pixel + 3));
			j++;
		}
		i++;
	}
	return (true);
}

void mlx_delete_texture(mlx_texture_t* texture)
{
	if (!texture)
	{
		mlx_error(MLX_NULLARG);
		return;
	}
	mlx_freen(2, texture->pixels, texture);
}
