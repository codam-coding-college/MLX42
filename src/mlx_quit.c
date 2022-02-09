/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_quit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 23:17:43 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/09 10:43:46 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void	mlx_quit(t_mlx *mlx)
{
	if (!mlx)
	{
		mlx_log(MLX_WARNING, MLX_NULL_ARG);
		return ;
	}
	glfwSetWindowShouldClose(mlx->window, true);
}
