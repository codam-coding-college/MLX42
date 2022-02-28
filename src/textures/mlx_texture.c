/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_texture.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 01:02:24 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/23 13:14:14 by lde-la-h      ########   odam.nl         */
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
		return ((void *)mlx_error(MLX_NULLARG));
	bpp = texture->bytes_per_pixel;
	if (xy[0] > (int32_t)texture->width || xy[1] > (int32_t)texture->height)
		return ((void *)mlx_error(MLX_INVAREA));
	image = mlx_new_image(mlx, wh[0], wh[1]);
	if (!image)
		return ((void *)mlx_error(MLX_MEMFAIL));
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
		return ((void *)mlx_error(MLX_NULLARG));
	img = mlx_texture_area_to_image(mlx, texture, (int32_t *)xy, \
	(uint32_t *)wh);
	if (!img)
		return ((void *)mlx_error(MLX_MEMFAIL));
	return (img);
}

bool	mlx_draw_texture(t_mlx_image *image, t_mlx_texture *texture, int32_t x, \
int32_t y)
{
	uint32_t	i;
	uint32_t	j;
	uint8_t		*pixel;

	if (!texture || !image)
		return (mlx_error(MLX_NULLARG));
	if (texture->width > image->width || \
		texture->height > image->height)
		return (mlx_error(MLX_TEXTOBIG));
	i = 0;
	while (i < texture->height)
	{
		j = 0;
		while (++j < texture->width)
		{
			pixel = &texture->pixels[(i * texture->width + j) * \
			texture->bytes_per_pixel];
			mlx_putpixel(image, x + j, y + i, *pixel << 24 | \
			*(pixel + 1) << 16 | *(pixel + 2) << 8 | *(pixel + 3));
			j++;
		}
		i++;
	}
	return (true);
}

void	mlx_delete_texture(t_mlx_texture *texture)
{
	if (!texture)
	{
		mlx_error(MLX_NULLARG);
		return ;
	}
	mlx_freen(2, texture->pixels, texture);
}
