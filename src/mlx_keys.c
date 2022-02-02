/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_keys.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 21:06:45 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/02 10:13:02 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

/**
 * HACK: Questionable way of intercepting and adding additional custom params 
 * to the glfw mouse key callback function.
 * 
 * TODO: Use glfwSetWindowPointer!
 */

static void				*g_param_cb = NULL;
static t_mlx_keyfunc	g_mlx_key_cb = NULL;

void	mlx_key_callback(GLFWwindow *window, int key, int scancode, int action)
{
	(void) window;
	(void) scancode;
	g_mlx_key_cb(key, action, g_param_cb);
}

/**
 * I suppose this is fine, due to norme I can't have a callback with more
 * than 4 arguments (wtf?), apparently I can also just cast this to the
 * desired function and its fine.
 */
void	mlx_key_hook(t_mlx *mlx, t_mlx_keyfunc func, void *param)
{
	g_param_cb = param;
	g_mlx_key_cb = func;
	glfwSetKeyCallback(mlx->window, (GLFWkeyfun)mlx_key_callback);
}

bool	mlx_is_key_down(t_mlx *mlx, t_keys key)
{
	return (glfwGetKey(mlx->window, key) == GLFW_PRESS);
}
