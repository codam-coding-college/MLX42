/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_mouse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 23:20:13 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/02 12:29:45 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	*g_param_cb = NULL;

static void	mlx_scroll_cb(GLFWwindow *window, double xoffset, double yoffset)
{
	const t_mlx				*mlx = glfwGetWindowUserPointer(window);
	const t_mlx_scrollfunc	hook = ((t_mlx_ctx *)mlx->context)->scroll_hook;

	hook(xoffset, yoffset, g_param_cb);
}

void	mlx_scroll_hook(t_mlx *mlx, t_mlx_scrollfunc func, void *param)
{
	g_param_cb = param;
	if (!func)
	{
		mlx_log(MLX_WARNING, MLX_NULL_ARG);
		return ;
	}
	((t_mlx_ctx *)mlx->context)->scroll_hook = func;
	glfwSetScrollCallback(mlx->window, mlx_scroll_cb);
}

bool	mlx_is_mouse_down(t_mlx *mlx, t_mouse_key key)
{
	return (glfwGetMouseButton(mlx->window, key) == GLFW_PRESS);
}

void	mlx_set_mouse_pos(t_mlx *mlx, int32_t x, int32_t y)
{
	glfwSetCursorPos(mlx->window, (double)x, (double)y);
}

void	mlx_get_mouse_pos(t_mlx *mlx, int32_t *x_out, int32_t *y_out)
{
	double	pos[2];

	glfwGetCursorPos(mlx->window, &pos[0], &pos[1]);
	*x_out = (int32_t)pos[0];
	*y_out = (int32_t)pos[1];
}
