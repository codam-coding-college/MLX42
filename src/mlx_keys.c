/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_keys.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 21:06:45 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 12:30:30 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

// Wtf is this ... God has abandoned us!??
void	mlx_key_callback(GLFWwindow *window, ...)
{
	va_list				args;
	t_mlx_key_cbdata	callback_data;
	const t_mlx			*mlx = glfwGetWindowUserPointer(window);
	const t_mlx_key		key_hook = ((t_mlx_ctx *)mlx->context)->key_hook;

	va_start(args, window);
	callback_data = (t_mlx_key_cbdata){
		va_arg(args, int32_t),
		va_arg(args, int32_t),
		va_arg(args, int32_t),
		va_arg(args, int32_t),
	};
	key_hook.func(callback_data, key_hook.param);
	va_end(args);
}

void	mlx_key_hook(t_mlx *mlx, t_mlx_keyfunc func, void *param)
{
	t_mlx_ctx	*mlxctx;

	if (!mlx || !func)
	{
		mlx_error(MLX_NULLARG);
		return ;
	}
	mlxctx = mlx->context;
	mlxctx->key_hook.func = func;
	mlxctx->key_hook.param = param;
	glfwSetKeyCallback(mlx->window, (GLFWkeyfun)mlx_key_callback);
}

bool	mlx_is_key_down(t_mlx *mlx, t_keys key)
{
	return (glfwGetKey(mlx->window, key) == GLFW_PRESS);
}
