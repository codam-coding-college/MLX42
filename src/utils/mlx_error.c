/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_error.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:51:54 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/08/10 13:01:50 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

// English description of the error codes.
static const char* mlx_errors[MLX_ERRMAX] = {
	"No Errors",
	"File has invalid extension",
	"Failed to open the file",
	"PNG file is invalid or corrupted",
	"XPM42 file is invalid or corrupted",
	"The specified X or Y positions are out of bounds",
	"The specified Width or Height dimensions are out of bounds",
	"The provided image is invalid, might indicate mismanagement of images",
	"Failed to compile the vertex shader.",
	"Failed to compile the fragment shader.",
	"Failed to compile the shaders.",
	"Failed to allocate memory",
	"Failed to initialize GLAD",
	"Failed to initialize GLFW",
	"Failed to create window",
	"String is to big to be drawn",
};

/**
 * Functions to set the error number, simply for convenience.
 * 
 * @param val The error value.
 * @return Always false 
 */
bool mlx_error(mlx_errno_t val)
{
	mlx_errno = val;
#ifndef NDEBUG
# ifdef _WIN32
	fprintf(stderr, "MLX42: %s", mlx_strerror(mlx_errno));
# else
	warnx("MLX42: %s", mlx_strerror(mlx_errno));
# endif
#endif
	return (false);
}

//= Public =//

const char* mlx_strerror(mlx_errno_t val)
{
	MLX_ASSERT(val >= 0, "Index must be positive");
	MLX_ASSERT(val < MLX_ERRMAX, "Index out of bounds");

	return (mlx_errors[val]);
}
