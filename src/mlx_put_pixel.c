/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_put_pixel.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 03:30:13 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/03 13:09:57 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void mlx_draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void mlx_xpm_putpixel(xpm_t* xpm, int32_t x, int32_t y, uint32_t color)
{
	uint8_t* pixelstart = &xpm->texture.pixels[(y * xpm->texture.width + x) * BPP];
	mlx_draw_pixel(pixelstart, color);
}

//= Public =//

void mlx_put_pixel(mlx_image_t* image, int32_t x, int32_t y, uint32_t color)
{
	if (!image)
	{
		mlx_error(MLX_NULLARG);
		return ;
	}
	uint8_t* pixelstart = &image->pixels[(y * image->width + x) * BPP];
	mlx_draw_pixel(pixelstart, color);
}
