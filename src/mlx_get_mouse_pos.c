/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_get_mouse_pos.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 23:20:13 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/01 23:36:44 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void	mlx_get_mouse_pos(t_MLX *mlx, t_IVec2 *pos_out)
{
	double	pos[2];

	glfwGetCursorPos(mlx->window, &pos[0], &pos[0]);
	pos_out->x = (int32_t)pos[0];
	pos_out->y = (int32_t)pos[1];
}
