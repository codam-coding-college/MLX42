/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_cursor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 20:10:54 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/29 18:02:28 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void* mlx_create_cursor(mlx_t* mlx, mlx_texture_t* image)
{
	MLX_ASSERT(!mlx || !image);

	GLFWcursor* cursor;
	if ((cursor = glfwCreateCursor((GLFWimage*)image, 0, 0)))
	{
		glfwSetCursor(mlx->window, cursor);
		return (cursor);
	}
	return ((void *)mlx_error(MLX_MEMFAIL));
}

void mlx_set_cursor(mlx_t* mlx, void* cursor)
{
	MLX_ASSERT(!mlx || !cursor);
	glfwSetCursor(mlx->window, cursor);
}

void mlx_set_cursor_mode(mlx_t* mlx, mouse_mode_t mode)
{
	MLX_ASSERT(!mlx);
	glfwSetInputMode(mlx->window, GLFW_CURSOR, mode);
}
