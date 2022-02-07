/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_terminate.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:43:22 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/08 00:26:09 by w2wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void		mlx_delete_xpm(t_xpm **xpm)
{
	mlx_freen(2, (*xpm)->pixels, *xpm);
	*xpm = NULL;
}

static void	mlx_free_imagedata(void	*content)
{
	t_mlx_image		*img;

	img = content;
	mlx_freen(3, img->context, img->pixels, img->instances);
}

/**
 * All of glfw & glads resources are cleaned up by the terminate function.
 * Now its time to cleanup our own mess.
 */
void	mlx_terminate(t_mlx *mlx)
{
	t_mlx_ctx	*mlxctx;

	mlxctx = mlx->context;
	glfwTerminate();
	mlx_lstclear((t_mlx_list **)(&mlxctx->hooks), &free);
	mlx_lstclear((t_mlx_list **)(&mlxctx->render_queue), &free);
	mlx_lstclear((t_mlx_list **)(&mlxctx->images), &mlx_free_imagedata);
	mlx_freen(2, mlxctx, mlx);
}
