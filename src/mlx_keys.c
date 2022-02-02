/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_keys.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 21:06:45 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/02 12:29:41 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	*g_param_cb = NULL;

void	mlx_key_callback(GLFWwindow *window, int key, int scancode, int action)
{
	const t_mlx			*mlx = glfwGetWindowUserPointer(window);
	const t_mlx_keyfunc	hook = ((t_mlx_ctx *)mlx->context)->key_hook;

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

bool	mlx_is_key_down(t_mlx *mlx, t_keys key)
{
	return (glfwGetKey(mlx->window, key) == GLFW_PRESS);
}
