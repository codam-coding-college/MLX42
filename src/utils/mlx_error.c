/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_error.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:51:54 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/23 15:07:06 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

// English description of the error codes.
static const char		*g_mlx_errors[] = {
	"No Errors",
	"File has invalid extension",
	"Failed to open the file",
	"Invalid parameter passed to function",
	"Argument passed was NULL",
	"Failed to compile shader",
	"Failed to initilize the renderer",
	"Failed to allocated memory",
	"XPM42 file is invalid or corrupted",
	"Failed to initialize GLFW",
	"Failed to create GLFW Window",
	"Failed to initialize GLAD",
	"Texture area out of range",
	"Texture is larger than image"
	"New image size is too big"
	"PNG file is invalid or corrupted",
};

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
 * Functions to set the error number, simply for convenience.
 * 
 * @param val The error value.
 * @return Always false 
 */
bool	mlx_error(t_mlx_errno val)
{
	g_mlx_errno = val;
	return (false);
}

const char	*mlx_strerror(t_mlx_errno val)
{
	return (g_mlx_errors[val]);
}
