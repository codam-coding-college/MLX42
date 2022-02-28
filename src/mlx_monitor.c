/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_monitor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 17:18:59 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/28 20:45:19 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void	mlx_get_monitor_size(int32_t index, int32_t *width, int32_t *height)
{
	const GLFWvidmode	*vidmode;
	GLFWmonitor			**monitors;
	int32_t				monitor_count;

	*width = 0;
	*height = 0;
	monitors = glfwGetMonitors(&monitor_count);
	if (index > monitor_count || !monitors)
		return ;
	vidmode = glfwGetVideoMode(monitors[index]);
	if (vidmode)
	{
		*width = vidmode->width;
		*height = vidmode->height;
	}
}
