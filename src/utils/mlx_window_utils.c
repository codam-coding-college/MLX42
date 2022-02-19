/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_window_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 08:24:33 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/19 21:40:07 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	*g_size_param_cb = NULL;
static void	*g_close_param_cb = NULL;

void	mlx_resize_callback(GLFWwindow *window, int32_t width, int32_t height)
{
	const t_mlx				*mlx = glfwGetWindowUserPointer(window);
	const t_mlx_resizefunc	hook = ((t_mlx_ctx *)mlx->context)->resize_hook;

	hook(width, height, g_size_param_cb);
}

void	mlx_resize_hook(t_mlx *mlx, t_mlx_resizefunc func, void *param)
{
	g_size_param_cb = param;
	if (!func)
	{
		mlx_log(MLX_WARNING, MLX_NULL_ARG);
		return ;
	}
	((t_mlx_ctx *)mlx->context)->resize_hook = func;
	glfwSetWindowSizeCallback(mlx->window, mlx_resize_callback);
}

void	mlx_close_callback(GLFWwindow *window)
{
	const t_mlx				*mlx = glfwGetWindowUserPointer(window);
	const t_mlx_closefunc	hook = ((t_mlx_ctx *)mlx->context)->close_hook;

	hook(g_close_param_cb);
}

void	mlx_close_hook(t_mlx *mlx, t_mlx_closefunc func, void *param)
{
	g_close_param_cb = param;
	if (!func)
	{
		mlx_log(MLX_WARNING, MLX_NULL_ARG);
		return ;
	}
	((t_mlx_ctx *)mlx->context)->close_hook = func;
	glfwSetWindowCloseCallback(mlx->window, mlx_close_callback);
}
