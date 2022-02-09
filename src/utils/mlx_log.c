/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_log.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:51:54 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/09 10:12:07 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"
#include <stdarg.h>

/**
 * This is what a 25 line limit does to people...
 * Utility function that lets you free x amount of pointers.
 * 
 * @param count The amount of args provided.
 * @param ... Any form of pointer.
 * @return False, this is simply for convinience when necessary.
 */
bool	mlx_freen(int32_t count, ...)
{
	int32_t	i;
	va_list	args;

	i = 0;
	va_start(args, count);
	while (i < count)
	{
		free(va_arg(args, void *));
		i++;
	}
	va_end(args);
	return (false);
}

/**
 * Simple logging function.
 * 
 * @param msg The message to write.
 * @return Always false, for the sake of making it convenient. 
 */
bool	mlx_log(const t_logtype type, const char *msg)
{
	if (type == MLX_INFO)
		fprintf(stdout, "MLX42: Info: %s\n", msg);
	else if (type == MLX_WARNING)
		fprintf(stderr, "MLX42: Warning: %s\n", msg);
	else if (type == MLX_ERROR)
		fprintf(stderr, "MLX42: Error: %s\n", msg);
	return (false);
}
