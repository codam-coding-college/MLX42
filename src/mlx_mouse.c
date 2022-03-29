/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_mouse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 23:20:13 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/29 02:50:06 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

static void mlx_scroll_cb(GLFWwindow* window, double xoffset, double yoffset)
{
	const mlx_t* mlx = glfwGetWindowUserPointer(window);
	const mlx_scroll_t scroll_hook = ((mlx_ctx_t*)mlx->context)->scroll_hook;

	scroll_hook.func(xoffset, yoffset, scroll_hook.param);
}

//= Public =//

void mlx_scroll_hook(mlx_t* mlx, mlx_scrollfunc func, void* param)
{
	MLX_ASSERT(!mlx || !func);

	mlx_ctx_t* mlxctx = mlx->context;
	mlxctx->scroll_hook.func = func;
	mlxctx->scroll_hook.param = param;
	glfwSetScrollCallback(mlx->window, mlx_scroll_cb);
}

bool mlx_is_mouse_down(mlx_t* mlx, mouse_key_t key)
{
	MLX_ASSERT(!mlx);
	return (glfwGetMouseButton(mlx->window, key) == GLFW_PRESS);
}

void mlx_set_mouse_pos(mlx_t* mlx, int32_t x, int32_t y)
{
	MLX_ASSERT(!mlx);
	glfwSetCursorPos(mlx->window, (double)x, (double)y);
}

void mlx_get_mouse_pos(mlx_t* mlx, int32_t* x_out, int32_t* y_out)
{
	double	x, y;

	MLX_ASSERT(!mlx || !x_out || !y_out);
	glfwGetCursorPos(mlx->window, &x, &y);
	*x_out = (int32_t)x;
	*y_out = (int32_t)y;
}
