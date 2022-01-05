/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_quit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 23:17:43 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/05 16:06:46 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void	mlx_quit(t_mlx *mlx)
{
	glfwSetWindowShouldClose(mlx->window, true);
}
