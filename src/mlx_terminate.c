/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_terminate.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:43:22 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/21 18:24:41 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

// TODO: Delete images!
void	mlx_terminate(t_mlx *mlx)
{
	t_mlx_ctx	*context;

	context = mlx->context;
	mlx_lstclear((t_mlx_list **)(&mlx->hooks), &free);
	glDeleteProgram(context->shaderprogram);
	//glDeleteTextures(1, &(context->texture));
	glDeleteBuffers(1, &(context->vbo));
	free(mlx);
	glfwTerminate();
}
