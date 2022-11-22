/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_window.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2wizard <w2wizzard@gmail.com>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 01:14:59 by W2wizard      #+#    #+#                 */
/*   Updated: 2022/11/22 09:06:54 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

/**
 * Recalculate the view projection matrix, used by images for screen pos
 * Reference: https://bit.ly/3KuHOu1 (Matrix View Projection)
 */
void mlx_update_matrix(const mlx_t* mlx, int32_t width, int32_t height)
{
	const mlx_ctx_t* mlxctx = mlx->context;
	const float depth = mlxctx->zdepth;

	/**
	 * In case the setting to stretch the image is set, we maintain the width and height but not
	 * the depth.
	 */
	width = mlx_settings[MLX_STRETCH_IMAGE] ? mlxctx->initialWidth : mlx->width;
	height = mlx_settings[MLX_STRETCH_IMAGE] ? mlxctx->initialHeight : mlx->height;

	const float matrix[16] = {
		2.f / width, 0, 0, 0,
		0, 2.f / -(height), 0, 0,
		0, 0, -2.f / (depth - -depth), 0,
		-1, -(height / -height),
		-((depth + -depth) / (depth - -depth)), 1
	};

	glUniformMatrix4fv(glGetUniformLocation(mlxctx->shaderprogram, "ProjMatrix"), 1, GL_FALSE, matrix);
}

static void mlx_resize_callback(GLFWwindow* window, int32_t width, int32_t height)
{
	const mlx_t* mlx = glfwGetWindowUserPointer(window);
	const mlx_ctx_t* mlxctx = mlx->context;

	if (mlxctx->resize_hook.func)
		mlxctx->resize_hook.func(width, height, mlxctx->resize_hook.param);
}

static void mlx_close_callback(GLFWwindow* window)
{
	const mlx_t* mlx = glfwGetWindowUserPointer(window);
	const mlx_close_t close_hook = ((mlx_ctx_t*)mlx->context)->close_hook;

	close_hook.func(close_hook.param);
}

//= Public =//

void mlx_close_hook(mlx_t* mlx, mlx_closefunc func, void* param)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(func);

	mlx_ctx_t* mlxctx = mlx->context;
	mlxctx->close_hook.func = func;
	mlxctx->close_hook.param = param;
	glfwSetWindowCloseCallback(mlx->window, mlx_close_callback);
}

void mlx_resize_hook(mlx_t* mlx, mlx_resizefunc func, void* param)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(func);

	mlx_ctx_t* mlxctx = mlx->context;
	mlxctx->resize_hook.func = func;
	mlxctx->resize_hook.param = param;
	glfwSetWindowSizeCallback(mlx->window, mlx_resize_callback);
}

void mlx_set_icon(mlx_t* mlx, mlx_texture_t* image)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(image);

	glfwSetWindowIcon(mlx->window, 1, (const GLFWimage*)image);
}

void mlx_set_window_pos(mlx_t* mlx, int32_t xpos, int32_t ypos)
{
	MLX_NONNULL(mlx);

	glfwSetWindowPos(mlx->window, xpos, ypos);
}

void mlx_get_window_pos(mlx_t* mlx, int32_t* xpos, int32_t* ypos)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(xpos);
	MLX_NONNULL(ypos);

	glfwGetWindowPos(mlx->window, xpos, ypos);
}

void mlx_set_window_size(mlx_t* mlx, int32_t new_width, int32_t new_height)
{
	MLX_NONNULL(mlx);

	mlx->width = new_width;
	mlx->height = new_height;
	glfwSetWindowSize(mlx->window, new_width, new_height);
}

void mlx_set_window_limit(mlx_t* mlx, int32_t min_w, int32_t min_h, int32_t max_w, int32_t max_h)
{
	MLX_NONNULL(mlx);

	glfwSetWindowSizeLimits(mlx->window, min_w, min_h, max_w, max_h);
}

void mlx_set_window_title(mlx_t* mlx, const char* title)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(title);

	glfwSetWindowTitle(mlx->window, title);
}
