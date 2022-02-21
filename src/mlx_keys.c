/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_keys.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 21:06:45 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/21 11:10:42 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	*g_param_cb = NULL;

void	mlx_key_callback(GLFWwindow *window, ...)
{
	va_list				args;
	t_mlx_key_cbdata	callback_data;
	const t_mlx			*mlx = glfwGetWindowUserPointer(window);
	const t_mlx_keyfunc	hook = ((t_mlx_ctx *)mlx->context)->key_hook;

	va_start(args, window);
	callback_data.key = va_arg(args, int32_t);
	callback_data.os_key = va_arg(args, int32_t);
	callback_data.action = va_arg(args, int32_t);
	callback_data.modifier = va_arg(args, int32_t);
	hook(callback_data, g_param_cb);
	va_end(args);
}

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

bool	mlx_is_key_down(t_mlx *mlx, t_keys key)
{
	return (glfwGetKey(mlx->window, key) == GLFW_PRESS);
}
