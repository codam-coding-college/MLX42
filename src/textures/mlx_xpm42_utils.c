/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_xpm42_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 14:00:50 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/11 11:56:14 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

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

	if (((int64_t)strrchr(line, ' ') - (int64_t)line) != xpm->cpp)
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
