/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_put_pixel.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 03:30:13 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/04/28 14:03:26 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void mlx_draw_pixel(uint8_t* pixel, uint32_t color)
{
	*((uint32_t *)pixel) = color;
}

//= Public =//

void mlx_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	MLX_ASSERT(!image);
	MLX_ASSERT(x > image->width);
	MLX_ASSERT(y > image->height);

	uint8_t* pixelstart = &image->pixels[(y * image->width + x) * BPP];
	mlx_draw_pixel(pixelstart, color);
}
