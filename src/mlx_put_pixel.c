/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_put_pixel.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 03:30:13 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/05 13:02:22 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void	mlx_putpixel(t_MLX *MLX, int32_t X, int32_t Y, int32_t Color)
{
	uint8_t	*pixelstart;

	pixelstart = &MLX->pixels[(Y * MLX->width + X) * sizeof(int32_t)];
	*(pixelstart + 0) = (uint8_t)((Color >> 24) & 0xFF);
	*(pixelstart + 1) = (uint8_t)((Color >> 16) & 0xFF);
	*(pixelstart + 2) = (uint8_t)((Color >> 8) & 0xFF);
	*(pixelstart + 3) = (uint8_t)((Color >> 0) & 0xFF);
}
