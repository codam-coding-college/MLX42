/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_terminate.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:43:22 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/02 12:08:01 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	mlx_delete_images(void	*content)
{
	(void) content;
	/*
	t_mlx_image		*img;

	img = content;
	glDeleteTextures(1, &((t_mlx_image_ctx *)img->context)->texture);
	free(img->context);
	free(img->pixels);
	free(img->instances);
	*/
}

// TODO: Delete images!
void	mlx_terminate(t_mlx *mlx)
{
	t_mlx_ctx	*mlxctx;

	mlxctx = mlx->context;
	glDeleteProgram(mlxctx->shaderprogram);
	glDeleteBuffers(1, &(mlxctx->vbo));
	glfwTerminate();
	mlx_lstclear((t_mlx_list **)(&mlxctx->hooks), &free);
	mlx_lstclear((t_mlx_list **)(&mlxctx->images), &mlx_delete_images);
	free(mlxctx);
	free(mlx);
}
