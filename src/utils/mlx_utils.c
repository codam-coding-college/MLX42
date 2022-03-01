/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/03 20:13:17 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 10:44:34 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static int32_t	isbase(char c, int32_t base)
{
	if (base <= 10)
		return (isdigit(c));
	return (isdigit(c) || (c >= 'A' && c <= ('A' + base - 10)) || \
	(c >= 'a' && c <= ('a' + base - 10)));
}

/**
 * Converts a given string to an integer of a given base.
 * 
 * @param str The string to convert.
 * @param base A given base, only up to 16.
 * @return The result of the conversion. 
 */
int32_t	mlx_atoi_base(const char *str, int32_t base)
{
	int32_t	i;
	int32_t	nbr;
	int32_t	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	if (!str || (base < 2 || base > 16))
		return (0);
	while (isspace(str[i]) || str[i] == '#')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -sign;
	while (str[i] && isbase(str[i], base))
	{
		if (str[i] >= 'A' && 'F' >= str[i])
			nbr = (nbr * base) + (str[i] - 'A' + 10);
		else if (str[i] >= 'a' && 'f' >= str[i])
			nbr = (nbr * base) + (str[i] - 'a' + 10);
		else
			nbr = (nbr * base) + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

int32_t	mlx_get_time(void)
{
	return (glfwGetTime());
}

void	mlx_focus(t_mlx *mlx)
{
	glfwFocusWindow(mlx->window);
}

/**
 * Converts an RGBA value to a monochrome/grayscale value.
 * It does so using specific weights for each channel.
 * 
 * @see https://goodcalculators.com/rgb-to-grayscale-conversion-calculator/
 * 
 * @param color The input RGBA value.
 * @return The rgba value converted to a grayscale color.
 */
int32_t	mlx_rgba_to_mono(int32_t color)
{
	const uint8_t	r = 0.299f * ((color >> 24) & 0xFF);
	const uint8_t	g = 0.587f * ((color >> 16) & 0xFF);
	const uint8_t	b = 0.114f * ((color >> 8) & 0xFF);
	const uint8_t	y = r + g + b;

	return (y << 24 | y << 16 | y << 8 | (color & 0xFF));
}
