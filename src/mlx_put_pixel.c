/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_put_pixel.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 03:30:13 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/05 02:25:06 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

// TODO: Introduce shader func utilites to easily change params...
void	mlx_putpixel(t_MLX *MLX, int32_t X, int32_t Y, int32_t Color)
{
	(void)MLX;
	(void)X;
	(void)Y;
	(void)Color;
	/*
	t_FVec4	output;

	mlx_rgba_to_float(Color, &output);
	glUniform4f(glGetUniformLocation(MLX->shaderprogram, "inColor"), \
	output.x, output.y, output.z, output.w);
	glEnable(GL_SCISSOR_TEST);
	glScissor(X, Y, 100, 100);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_SCISSOR_TEST);
	*/
}
