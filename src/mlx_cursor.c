/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_cursor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <main@w2wizard.dev>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 20:10:54 by W2Wizard      #+#    #+#                 */
/*   Updated: 2023/03/09 11:11:45 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Public =//

mlx_win_cursor_t* mlx_create_std_cursor(cursor_t type)
{
	MLX_ASSERT(type >= MLX_CURSOR_ARROW && type < MLX_CURSOR_VRESIZE, "Invalid standard cursor type");

	GLFWcursor* cursor;
	if ((cursor = glfwCreateStandardCursor(type)))
		return (cursor);
	return ((void *)mlx_error(MLX_MEMFAIL));
}

mlx_win_cursor_t* mlx_create_cursor(mlx_texture_t* texture)
{
	MLX_NONNULL(texture);

	GLFWcursor* cursor;
	GLFWimage image = (GLFWimage) {
		.width = texture->width,
		.height = texture->height,
		.pixels = texture->pixels
	};

	if ((cursor = glfwCreateCursor(&image, 0, 0)))
		return (cursor);
	return ((void *)mlx_error(MLX_MEMFAIL));
}

void mlx_destroy_cursor(mlx_win_cursor_t* cursor)
{
	MLX_NONNULL(cursor);

	glfwDestroyCursor(cursor);
}

void mlx_set_cursor(mlx_t* mlx, mlx_win_cursor_t* cursor)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(cursor);

	glfwSetCursor(mlx->window, cursor);
}

void mlx_set_cursor_mode(mlx_t* mlx, mouse_mode_t mode)
{
	MLX_NONNULL(mlx);

	glfwSetInputMode(mlx->window, GLFW_CURSOR, mode);
}
