/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_monitor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 17:18:59 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/07/05 15:12:43 by jobvan-d      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Public =//

void mlx_get_monitor_size(int32_t index, uint32_t* width, uint32_t* height)
{
	MLX_ASSERT(index >= 0, "Index out of bounds");
	MLX_NONNULL(width);
	MLX_NONNULL(height);

	*width = 0;
	*height = 0;
	
	int32_t monitor_count;
	GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
	if (index > monitor_count || !monitors)
		return;

	const GLFWvidmode* vidmode;
	if ((vidmode = glfwGetVideoMode(monitors[index])))
	{
		*width = (uint32_t)vidmode->width;
		*height = (uint32_t)vidmode->height;
	}
}
