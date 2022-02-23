/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_image_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 07:52:41 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/23 13:17:03 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

bool	mlx_resize_image(t_mlx_image *img, uint32_t nwidth, uint32_t nheight)
{
	uint8_t			*tempbuff;
	t_mlx_image_ctx	*imgctx;

	if (!img)
		return (mlx_error(MLX_NULLARG));
	if (nwidth > UINT16_MAX || nheight > UINT16_MAX)
		return (mlx_error(MLX_RESTOBIG));
	if (nwidth != img->width || nheight != img->height)
	{
		imgctx = img->context;
		tempbuff = realloc(img->pixels, (nwidth * nheight) * sizeof(int32_t));
		if (!tempbuff)
			return (mlx_error(MLX_MEMFAIL));
		img->pixels = tempbuff;
		(*(uint32_t *)&img->width) = nwidth;
		(*(uint32_t *)&img->height) = nheight;
		memset(img->pixels, 0, (img->width * img->height) * sizeof(int32_t));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, imgctx->texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nwidth, nheight, 0, GL_RGBA, \
		GL_UNSIGNED_BYTE, img->pixels);
	}
	return (true);
}
