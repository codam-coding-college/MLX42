/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_monitor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 17:18:59 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/04/13 00:25:43 by w2wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Public =//

void mlx_get_monitor_size(int32_t index, int32_t* width, int32_t* height)
{
	MLX_ASSERT(index < 0);
	MLX_ASSERT(!width);
	MLX_ASSERT(!height);

	*width = 0;
	*height = 0;
	
	int32_t monitor_count;
	GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
	if (index > monitor_count || !monitors)
		return;

	const GLFWvidmode* vidmode;
	if ((vidmode = glfwGetVideoMode(monitors[index])))
	{
		*width = vidmode->width;
		*height = vidmode->height;
	}
}
