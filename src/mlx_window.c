/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_window.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2wizard <w2wizzard@gmail.com>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 01:14:59 by W2wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 12:52:28 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

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
	glfwSetWindowSizeLimits(mlx->window, min_wh[0], min_wh[1], \
	max_wh[0], max_wh[1]);
}
