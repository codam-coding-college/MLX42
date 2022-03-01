/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:43:22 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 17:59:21 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	mlx_free_imagedata(void	*content)
{
	t_mlx_image		*img;

	img = content;
	mlx_freen(3, img->context, img->pixels, img->instances);
}

void	mlx_close_window(t_mlx *mlx)
{
	if (!mlx)
	{
		mlx_error(MLX_NULLARG);
		return ;
	}
	glfwSetWindowShouldClose(mlx->window, true);
}

/**
 * All of glfw & glads resources are cleaned up by the terminate function.
 * Now its time to cleanup our own mess.
 */
void	mlx_terminate(t_mlx *mlx)
{
	t_mlx_ctx	*mlxctx;

	if (!mlx)
	{
		mlx_error(MLX_NULLARG);
		return ;
	}
	glfwTerminate();
	mlxctx = mlx->context;
	mlx_lstclear((t_mlx_list **)(&mlxctx->hooks), &free);
	mlx_lstclear((t_mlx_list **)(&mlxctx->render_queue), &free);
	mlx_lstclear((t_mlx_list **)(&mlxctx->images), &mlx_free_imagedata);
	mlx_freen(2, mlxctx, mlx);
}
