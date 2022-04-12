/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_error.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:51:54 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/04/13 00:16:51 by w2wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

// English description of the error codes.
static const char* mlx_errors[] = {
	"No Errors",
	"File has invalid extension",
	"Failed to open the file",
	"PNG file is invalid or corrupted",
	"XPM42 file is invalid or corrupted",
	"Font atlas data is invalid",
	"Texture area out of range",
	"Failed to compile shader",
	"Failed to allocate memory",
	"Failed to initialize GLAD",
	"Failed to initialize GLFW",
	"Failed to create window",
	"Image size is too big",
	"Image size is too small",
	"Texture is larger than image",
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
	return (false);
}

//= Public =//

const char* mlx_strerror(mlx_errno_t val)
{
	MLX_ASSERT(val < 0);
	MLX_ASSERT(val >= MLX_ERRMAX);

	return (mlx_errors[val]);
}
