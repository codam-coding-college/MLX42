/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_monitor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 17:18:59 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/01/22 21:30:06 by W2Wizard      ########   odam.nl         */
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

void	mlx_get_monitor_size(int32_t index, int32_t *width, int32_t *height)
{
	const GLFWvidmode	*vidmode;
	GLFWmonitor			**monitors;
	int32_t				monitor_count;

	monitors = glfwGetMonitors(&monitor_count);
	if (index > monitor_count || !monitors)
		return ;
	vidmode = glfwGetVideoMode(monitors[index]);
	if (vidmode)
	{
		*width = vidmode->width;
		*height = vidmode->height;
	}
	else
	{
		*width = 0;
		*height = 0;
	}
}
