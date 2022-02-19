/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_window_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 08:24:33 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/19 08:28:01 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	*g_param_cb = NULL;

void	mlx_resize_callback(GLFWwindow *window, int32_t key, int32_t scancode)
{
	const t_mlx				*mlx = glfwGetWindowUserPointer(window);
	const t_mlx_resizefunc	hook = ((t_mlx_ctx *)mlx->context)->resize_hook;

	(void) scancode;
	hook(key, action, g_param_cb);
}

/**
 * I suppose this is fine, due to norme I can't have a callback with more
 * than 4 arguments (wtf?), apparently I can also just cast this to the
 * desired function and its fine.
 */
void	mlx_key_hook(t_mlx *mlx, t_mlx_keyfunc func, void *param)
{
	g_param_cb = param;
	if (!func)
	{
		mlx_log(MLX_WARNING, MLX_NULL_ARG);
		return ;
	}
	((t_mlx_ctx *)mlx->context)->key_hook = func;
	glfwSetKeyCallback(mlx->window, (GLFWkeyfun)mlx_key_callback);
}
