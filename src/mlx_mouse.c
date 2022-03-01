/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_mouse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 23:20:13 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 12:31:34 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	mlx_scroll_cb(GLFWwindow *window, double xoffset, double yoffset)
{
	const t_mlx			*mlx = glfwGetWindowUserPointer(window);
	const t_mlx_scroll	scroll_hook = ((t_mlx_ctx *)mlx->context)->scroll_hook;

	scroll_hook.func(xoffset, yoffset, scroll_hook.param);
}

void	mlx_scroll_hook(t_mlx *mlx, t_mlx_scrollfunc func, void *param)
{
	t_mlx_ctx	*mlxctx;

	if (!mlx || !func)
	{
		mlx_error(MLX_NULLARG);
		return ;
	}
	mlxctx = mlx->context;
	mlxctx->scroll_hook.func = func;
	mlxctx->scroll_hook.param = param;
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
