/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_putpixel.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 03:30:13 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/23 12:36:54 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

// Simply for convenience and avoiding code duplication.
static void	mlx_draw_pixel(uint8_t *pixel, uint32_t color)
{
	*(pixel + 0) = (uint8_t)((color >> 24) & 0xFF);
	*(pixel + 1) = (uint8_t)((color >> 16) & 0xFF);
	*(pixel + 2) = (uint8_t)((color >> 8) & 0xFF);
	*(pixel + 3) = (uint8_t)((color >> 0) & 0xFF);
}

void	mlx_xpm_putpixel(t_xpm *xpm, int32_t x, int32_t y, uint32_t color)
{
	uint8_t	*pixelstart;

	pixelstart = &xpm->texture.pixels[(y * xpm->texture.width + x) * \
	sizeof(int32_t)];
	mlx_draw_pixel(pixelstart, color);
}

void	mlx_putpixel(t_mlx_image *image, int32_t x, int32_t y, uint32_t color)
{
	uint8_t	*pixelstart;

	if (!image)
	{
		mlx_error(MLX_NULLARG);
		return ;
	}
	pixelstart = &image->pixels[(y * image->width + x) * sizeof(int32_t)];
	mlx_draw_pixel(pixelstart, color);
}
