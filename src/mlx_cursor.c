/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_cursor.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/18 20:10:54 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/18 20:26:24 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void	*mlx_create_cursor(t_mlx *mlx, t_xpm *image)
{
	GLFWcursor	*cursor;

	cursor = glfwCreateCursor((GLFWimage *)image, 0, 0);
	if (cursor)
		glfwSetCursor(mlx->window, cursor);
	else
		return ((void *)mlx_error(MLX_MEMORY_FAIL));
	return (cursor);
}

void	mlx_set_cursor(t_mlx *mlx, void *cursor)
{
	glfwSetCursor(mlx->window, cursor);
}

void	mlx_set_cursor_mode(t_mlx *mlx, t_mouse_mode mode)
{
	glfwSetInputMode(mlx->window, GLFW_CURSOR, mode);
}
