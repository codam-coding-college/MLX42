/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_terminate.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:43:22 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/05 02:27:22 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void	mlx_terminate(t_MLX *mlx)
{
	mlx_lstclear((t_mlx_list **)(&mlx->hooks), &free);
	free(mlx);
	glDeleteProgram(((t_mlx_ctx *)mlx->context)->shaderprogram);
	glfwTerminate();
}
