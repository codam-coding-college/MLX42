/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_xpm42_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 14:00:50 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 12:52:44 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

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

void	mlx_delete_xpm42(t_xpm *xpm)
{
	if (!xpm)
	{
		mlx_error(MLX_NULLARG);
		return ;
	}
	mlx_delete_texture(&xpm->texture);
	free(xpm);
}
