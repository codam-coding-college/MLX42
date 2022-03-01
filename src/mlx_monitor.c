/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_monitor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 17:18:59 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 13:08:14 by lde-la-h      ########   odam.nl         */
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
