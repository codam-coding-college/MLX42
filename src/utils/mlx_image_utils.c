/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_image_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 07:52:41 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/27 21:03:10 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

bool	mlx_resize_image(t_mlx_image *img, uint32_t nwidth, uint32_t nheight)
{
	uint8_t			*tempbuff;

	if (!img)
		return (mlx_error(MLX_NULLARG));
	if (nwidth > INT16_MAX || nheight > INT16_MAX)
		return (mlx_error(MLX_IMGTOBIG));
	if (nwidth != img->width || nheight != img->height)
	{
		tempbuff = realloc(img->pixels, (nwidth * nheight) * sizeof(int32_t));
		if (!tempbuff)
			return (mlx_error(MLX_MEMFAIL));
		img->pixels = tempbuff;
		(*(uint32_t *)&img->width) = nwidth;
		(*(uint32_t *)&img->height) = nheight;
		memset(img->pixels, 0, (img->width * img->height) * sizeof(int32_t));
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nwidth, nheight, 0, GL_RGBA, \
		GL_UNSIGNED_BYTE, img->pixels);
	}
	return (true);
}

/**
 * Recalculate the view projection matrix, used by images for screen pos
 * Reference: https://bit.ly/3KuHOu1 (Matrix View Projection)
 */
static void	mlx_update_matrix(const t_mlx *mlx, int32_t width, int32_t height)
{
	const float		matrix[16] = {
		2.f / width, 0, 0, 0,
		0, 2.f / -(height), 0, 0,
		0, 0, -2.f / (1000.f - -1000.f), 0,
		-1, -(height / -height),
		-((1000.f + -1000.f) / (1000.f - -1000.f)), 1
	};

	glUniformMatrix4fv(glGetUniformLocation(((t_mlx_ctx *)mlx->context) \
	->shaderprogram, "ProjMatrix"), 1, GL_FALSE, matrix);
}

void	mlx_on_resize(GLFWwindow *window, int32_t width, int32_t height)
{
	const t_mlx		*mlx = glfwGetWindowUserPointer(window);

	if (width > 1 || height > 1)
		mlx_update_matrix(mlx, width, height);
}
