/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_xpm42_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 14:00:50 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/15 10:04:55 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

t_mlx_image	*mlx_xpm42_area_to_image(t_mlx *mlx, t_xpm *xpm, uint16_t xy[2], \
uint16_t wh[2])
{
	int32_t		y;
	uint16_t	bpp;
	uint8_t		*pixelx;
	uint8_t		*pixeli;
	t_mlx_image	*image;

	y = -1;
	if (!mlx || !xpm || !xy || !wh)
		return ((void *)mlx_log(MLX_WARNING, MLX_NULL_ARG));
	bpp = xpm->texture.bytes_per_pixel;
	if (xy[0] > xpm->texture.width || xy[1] > xpm->texture.height)
		return ((void *)mlx_log(MLX_WARNING, MLX_INVALID_ARG));
	image = mlx_new_image(mlx, wh[0], wh[1]);
	if (!image)
		return ((void *)mlx_log(MLX_ERROR, MLX_MEMORY_FAIL));
	while (++y < wh[1])
	{
		pixelx = &xpm->texture.pixels[((xy[1] + y) * \
		xpm->texture.width + xy[0]) * bpp];
		pixeli = &image->pixels[y * wh[0] * bpp];
		memmove(pixeli, pixelx, wh[0] * bpp);
	}
	return (image);
}

t_mlx_image	*mlx_xpm42_to_image(t_mlx *mlx, const char *path)
{
	t_xpm		*xpm;
	t_mlx_image	*img;

	if (!mlx || !path)
		return ((void *)mlx_log(MLX_WARNING, MLX_NULL_ARG));
	xpm = mlx_load_xpm42(path);
	if (!xpm)
		return (NULL);
	img = mlx_new_image(mlx, xpm->texture.width, xpm->texture.height);
	if (!img)
		return (NULL);
	if (!mlx_draw_xpm42(img, xpm, 0, 0))
		return (NULL);
	mlx_delete_xpm42(&xpm);
	return (img);
}

uint32_t	mlx_grab_xpm_pixel(char *pixelstart, uint32_t *ctable, t_xpm *xpm, \
size_t s)
{
	uint64_t	index;
	char		*cpp_buffer;

	cpp_buffer = memset(alloca(xpm->cpp + 1), 0, xpm->cpp + 1);
	memcpy(cpp_buffer, pixelstart, xpm->cpp);
	index = mlx_fnv_hash(cpp_buffer, xpm->cpp) % s;
	return (ctable[index]);
}

/**
 * Inserts the given line into the color table, index is determined as hash.
 * TODO: Resolve collisions, if any.
 * 
 * @param xpm The XPM.
 * @param line The current color entry line.
 * @param ctable The color table.
 * @param s The size of the table
 * @return True if the entry has no faults and was added
 */
bool	mlx_insert_xpm_entry(t_xpm *xpm, char *line, uint32_t *ctable, size_t s)
{
	int32_t			index;

	if (((uintptr_t)strrchr(line, ' ') - (uintptr_t)line) != (uint64_t)xpm->cpp)
		return (false);
	if (!isspace(line[xpm->cpp]) || line[xpm->cpp + 1] != '#' || \
		!isalnum(line[xpm->cpp + 2]))
		return (false);
	index = mlx_fnv_hash(line, xpm->cpp) % s;
	if (xpm->mode == 'c')
		ctable[index] = mlx_atoi_base(&line[xpm->cpp], 16);
	else
		ctable[index] = mlx_rgba_to_mono(mlx_atoi_base(&line[xpm->cpp], 16));
	return (true);
}
