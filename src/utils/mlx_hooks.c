/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_hooks.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 07:52:41 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/02 00:04:14 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

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
