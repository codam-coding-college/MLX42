/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_texture.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/17 01:02:24 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/04/13 00:37:53 by w2wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Public =//

mlx_image_t* mlx_texture_area_to_image(mlx_t* mlx, mlx_texture_t* texture, uint32_t xy[2], uint32_t wh[2])
{
	MLX_ASSERT(!mlx);
	MLX_ASSERT(!texture);
	MLX_ASSERT(!xy);
	MLX_ASSERT(!wh);

	if (xy[0] > texture->width || xy[1] > texture->height || \
		wh[0] > texture->width || wh[1] > texture->height)
		return ((void*)mlx_error(MLX_INVAREA));

	mlx_image_t* image;
	if (!(image = mlx_new_image(mlx, wh[0], wh[1])))
		return ((void*)mlx_error(MLX_MEMFAIL));

	uint8_t* pixelx;
	uint8_t* pixeli;
	for (uint32_t y = 0; y < wh[1]; y++)
	{
		pixelx = &texture->pixels[((xy[1] + y) * texture->width + xy[0]) * BPP];
		pixeli = &image->pixels[y * wh[0] * BPP];
		memmove(pixeli, pixelx, wh[0] * BPP);
	}
	return (image);
}

mlx_image_t* mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture)
{
	MLX_ASSERT(!mlx);
	MLX_ASSERT(!texture);

	mlx_image_t* img;
	const int32_t xy[] = {0, 0};
	const uint32_t wh[] = {texture->width, texture->height};

	if (!(img = mlx_texture_area_to_image(mlx, texture, (uint32_t*)xy, (uint32_t*)wh)))
		return ((void*)mlx_error(MLX_MEMFAIL));
	return (img);
}

bool mlx_draw_texture(mlx_image_t* image, mlx_texture_t* texture, int32_t x, int32_t y)
{
	MLX_ASSERT(!image);
	MLX_ASSERT(!texture);
	MLX_ASSERT(x < 0);
	MLX_ASSERT(y < 0);	

	if (texture->width > image->width || texture->height > image->height)
		return (mlx_error(MLX_TEXTOBIG));

	uint8_t* pixelx;
	uint8_t* pixeli;
	for (uint32_t i = 0; i < texture->height; i++)
	{
		pixelx = &texture->pixels[(i * texture->width) * texture->bytes_per_pixel];
		pixeli = &image->pixels[((i + y) * image->width + x) * texture->bytes_per_pixel];
		memmove(pixeli, pixelx, texture->width * texture->bytes_per_pixel);
	}
	return (true);
}

void mlx_delete_texture(mlx_texture_t* texture)
{
	MLX_ASSERT(!texture);

	mlx_freen(2, texture->pixels, texture);
}
