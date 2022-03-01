/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_window_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 08:24:33 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/03/01 12:32:28 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

static void	mlx_close_callback(GLFWwindow *window)
{
	const t_mlx			*mlx = glfwGetWindowUserPointer(window);
	const t_mlx_close	close_hook = ((t_mlx_ctx *)mlx->context)->close_hook;

	close_hook.func(close_hook.param);
}

//= Public =//

void	mlx_close_hook(t_mlx *mlx, t_mlx_closefunc func, void *param)
{
	t_mlx_ctx	*mlxctx;

	if (!mlx || !func)
	{
		mlx_error(MLX_NULLARG);
		return ;
	}
	mlxctx = mlx->context;
	mlxctx->close_hook.func = func;
	mlxctx->close_hook.param = param;
	glfwSetWindowCloseCallback(mlx->window, mlx_close_callback);
}

void	mlx_resize_hook(t_mlx *mlx, t_mlx_resizefunc func, void *param)
{
	t_mlx_ctx	*mlxctx;

	if (!func)
	{
		mlx_error(MLX_NULLARG);
		return ;
	}
	mlxctx = mlx->context;
	mlxctx->resize_hook.func = func;
	mlxctx->resize_hook.param = param;
}
