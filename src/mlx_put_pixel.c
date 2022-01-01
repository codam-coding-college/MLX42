/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_put_pixel.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 03:30:13 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/01 17:42:29 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void	mlx_putpixel(t_MLX *MLX, int32_t X, int32_t Y, int32_t Color)
{
	float	convert[4];

	mlx_argb_to_float(Color, convert);
	glUniform4f(glGetUniformLocation(MLX->shaderprogram, "inColor"), \
	convert[1], convert[2], convert[3], convert[0]);
	glEnable(GL_SCISSOR_TEST);
	glScissor(X, Y, 100, 100);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_SCISSOR_TEST);
}
