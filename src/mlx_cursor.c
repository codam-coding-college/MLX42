/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_cursor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 20:10:54 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/02 00:27:44 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void* mlx_create_cursor(mlx_t* mlx, mlx_texture_t* image)
{
	//TODO: Reimplement
	/*
	const GLFWimage cursorimg = {
		image->width,
		image->height,
		image->pixels,
	}
	GLFWcursor* cursor = glfwCreateCursor(&cursorimg, 0, 0);
	if (cursor)
	{
		glfwSetCursor(mlx->window, cursor);
		return (cursor);
	}
	return ((void *)mlx_error(MLX_MEMFAIL));
	*/
	return (NULL);
}

void mlx_set_cursor(mlx_t* mlx, void* cursor)
{
	glfwSetCursor(mlx->window, cursor);
}

void mlx_set_cursor_mode(mlx_t* mlx, mouse_mode_t mode)
{
	glfwSetInputMode(mlx->window, GLFW_CURSOR, mode);
}
