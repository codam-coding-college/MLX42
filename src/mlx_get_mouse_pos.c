/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_get_mouse_pos.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 23:20:13 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/05 16:06:46 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void	mlx_get_mouse_pos(t_mlx *mlx, t_IVec2 *pos_out)
{
	double	pos[2];

	glfwGetCursorPos(mlx->window, &pos[0], &pos[1]);
	pos_out->x = (int32_t)pos[0];
	pos_out->y = (int32_t)pos[1];
}
