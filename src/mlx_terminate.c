/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_terminate.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:43:22 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/01 17:46:17 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void	mlx_terminate(t_MLX *mlx)
{
	mlx_lstclear(mlx->hooks, &free);
	free(mlx);
	glDeleteProgram(mlx->shaderprogram);
	glfwTerminate();
}
