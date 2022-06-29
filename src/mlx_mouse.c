/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_mouse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 23:20:13 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/06/29 15:34:25 by lde-la-h      ########   odam.nl         */
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

static void mlx_mouse_cb(GLFWwindow* window, int32_t button, int32_t action, int32_t mods)
{
	const mlx_t* mlx = glfwGetWindowUserPointer(window);
	const mlx_mouse_t mouse_hook = ((mlx_ctx_t*)mlx->context)->mouse_hook;

	mouse_hook.func(button, action, mods, mouse_hook.param);
}

static void mlx_cursor_cb(GLFWwindow* window, double xpos, double ypos)
{
	const mlx_t* mlx = glfwGetWindowUserPointer(window);
	const mlx_cursor_t cursor_hook = ((mlx_ctx_t*)mlx->context)->cursor_hook;

	cursor_hook.func(xpos, ypos, cursor_hook.param);
}

//= Public =//

void mlx_scroll_hook(mlx_t* mlx, mlx_scrollfunc func, void* param)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(func);

	mlx_ctx_t* const mlxctx = mlx->context;
	mlxctx->scroll_hook.func = func;
	mlxctx->scroll_hook.param = param;
	glfwSetScrollCallback(mlx->window, mlx_scroll_cb);
}

void mlx_mouse_hook(mlx_t* mlx, mlx_mousefunc func, void* param)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(func);

	mlx_ctx_t* const mlxctx = mlx->context;
	mlxctx->mouse_hook.func = func;
	mlxctx->mouse_hook.param = param;
	glfwSetMouseButtonCallback(mlx->window, mlx_mouse_cb);
}

void mlx_cursor_hook(mlx_t* mlx, mlx_cursorfunc func, void* param)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(func);

	mlx_ctx_t* const mlxctx = mlx->context;
	mlxctx->cursor_hook.func = func;
	mlxctx->cursor_hook.param = param;
	glfwSetCursorPosCallback(mlx->window, mlx_cursor_cb);
}

bool mlx_is_mouse_down(mlx_t* mlx, mouse_key_t key)
{
	MLX_NONNULL(mlx);

	return (glfwGetMouseButton(mlx->window, key) == GLFW_PRESS);
}

void mlx_set_mouse_pos(mlx_t* mlx, int32_t x, int32_t y)
{
	MLX_NONNULL(mlx);

	glfwSetCursorPos(mlx->window, (double)x, (double)y);
}

void mlx_get_mouse_pos(mlx_t* mlx, int32_t* x_out, int32_t* y_out)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(x_out);
	MLX_NONNULL(y_out);

	double	x, y;
	glfwGetCursorPos(mlx->window, &x, &y);
	*x_out = (int32_t)x;
	*y_out = (int32_t)y;
}
