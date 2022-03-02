/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_window.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2wizard <w2wizzard@gmail.com>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 01:14:59 by W2wizard      #+#    #+#                 */
/*   Updated: 2022/03/02 00:35:48 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

/**
 * Recalculate the view projection matrix, used by images for screen pos
 * Reference: https://bit.ly/3KuHOu1 (Matrix View Projection)
 */
static void mlx_update_matrix(const mlx_t* mlx, int32_t width, int32_t height)
{
	const float matrix[16] = {
		2.f / width, 0, 0, 0,
		0, 2.f / -(height), 0, 0,
		0, 0, -2.f / (1000.f - -1000.f), 0,
		-1, -(height / -height),
		-((1000.f + -1000.f) / (1000.f - -1000.f)), 1
	};

	glUniformMatrix4fv(glGetUniformLocation(((mlx_ctx_t*)mlx->context)->shaderprogram, "ProjMatrix"), 1, GL_FALSE, matrix);
}

void mlx_on_resize(GLFWwindow* window, int32_t width, int32_t height)
{
	const mlx_t* mlx = glfwGetWindowUserPointer(window);
	const mlx_ctx_t* mlxctx = mlx->context;

	if (mlxctx->resize_hook.func)
		mlxctx->resize_hook.func(width, height, mlxctx->resize_hook.param);
	if (width > 1 || height > 1)
		mlx_update_matrix(mlx, width, height);
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
	if (!mlx || !func)
	{
		mlx_error(MLX_NULLARG);
		return ;
	}
	mlx_ctx_t* mlxctx = mlx->context;
	mlxctx->close_hook.func = func;
	mlxctx->close_hook.param = param;
	glfwSetWindowCloseCallback(mlx->window, mlx_close_callback);
}

void	mlx_resize_hook(mlx_t *mlx, mlx_resizefunc func, void *param)
{
	if (!mlx || !func)
	{
		mlx_error(MLX_NULLARG);
		return ;
	}
	mlx_ctx_t* mlxctx = mlx->context;
	mlxctx->resize_hook.func = func;
	mlxctx->resize_hook.param = param;
	//NOTE: Callback is set just above because MLX needs to hook onto it.
}

void	mlx_set_icon(t_mlx *mlx, t_xpm *image)
{
	glfwSetWindowIcon(mlx->window, 1, (const GLFWimage *)image);
}

void	mlx_set_window_pos(t_mlx *mlx, int32_t xpos, int32_t ypos)
{
	glfwSetWindowPos(mlx->window, xpos, ypos);
}

void	mlx_get_window_pos(t_mlx *mlx, int32_t *xpos, int32_t *ypos)
{
	glfwGetWindowPos(mlx->window, xpos, ypos);
}

void	mlx_set_window_size(t_mlx *mlx, int32_t new_width, int32_t new_height)
{
	mlx->width = new_width;
	mlx->height = new_height;
	glfwSetWindowSize(mlx->window, new_width, new_height);
}

void	mlx_set_window_limit(t_mlx *mlx, int32_t min_wh[2], int32_t max_wh[2])
{
	glfwSetWindowSizeLimits(mlx->window, min_wh[0], min_wh[1], max_wh[0], max_wh[1]);
}
