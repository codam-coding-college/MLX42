/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_xpm42.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 03:42:29 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/25 14:08:00 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

/**
 * XPM is an obscure image format which can't seem to make up its mind
 * wether it wants to be written in C code or not.
 * 
 * https://en.wikipedia.org/wiki/X_PixMap
 * 
 * This might anger some but instead I decided to write my own
 * image format, very similar to XPM2, which seems to be the better
 * option between the 3 versions. The only difference is in the
 * header which carries the file type, width, height, color count
 * and finally color type aka 'c' for RGBA8 or 'm' for monochrome
 * output.
 * 
 * The changes, in my opinion, very much simplify the XPM format
 * into something literally anybody can use without much guessing
 * as to what does what.
 * 
 * Additionally with the C style format, the idea is that you simply include
 * it directly into the compilation of the program (since its just c).
 * 
 * As convenient as this is, I just find it hideous especially the XPM3 variant.
 * By sticking to the XPM style format, conversion should be very easy and 
 * straight forward to this format however.
 */

/**
 * Retrieves the pixel data line by line and then processes each pixel
 * by hashing the characters and looking it up from the color table.
 * 
 * Dirty norme hack to make this norme with the X array... norme is great right?
 */
static bool	mlx_read_data(t_xpm *xpm, FILE *file, uint32_t *ctable, size_t s)
{
	int64_t	x[2];
	int64_t	y;
	int64_t	bread;
	size_t	buffsize;
	char	*line;

	y = -1;
	line = NULL;
	while (++y < xpm->texture.height)
	{
		x[0] = -1;
		x[1] = 0;
		bread = getline(&line, &buffsize, file);
		if (line[bread - 1] == '\n')
			bread--;
		if (bread == -1 || bread != xpm->texture.width * xpm->cpp)
			return (mlx_freen(1, line));
		while (++x[0] < xpm->texture.width)
		{
			mlx_xpm_putpixel(xpm, x[0], y, \
			mlx_grab_xpm_pixel(&line[x[1]], ctable, xpm, s));
			x[1] += xpm->cpp;
		}
	}
	return (!mlx_freen(1, line));
}

/**
 * For quick lookups we basically create a stack allocated lookup
 * table with every ascii character in it. This should help avoid a O(n)
 * case and give us a O(1) for very fast look ups.
 * 
 * Downside is we still need to iterate of each pixel to solve its color.
 * So I hope this makes it atleast a bit faster.
 * 
 * TODO: This buffer might be way to big! Do actual collision checks, 
 * for now just straight up raw dog this.
 */
static bool	mlx_read_table(t_xpm *xpm, FILE *file)
{
	char		*line;
	int32_t		i;
	int64_t		bread;
	size_t		buffsize;
	uint32_t	ctable[UINT16_MAX];

	i = -1;
	line = NULL;
	memset(ctable, 0, sizeof(ctable));
	while (++i < xpm->color_count)
	{
		bread = getline(&line, &buffsize, file);
		if (bread < 1)
			return (mlx_freen(1, line));
		if (!mlx_insert_xpm_entry(xpm, line, ctable, (sizeof(ctable) / 4)))
			return (mlx_freen(1, line));
	}
	free(line);
	return (mlx_read_data(xpm, file, ctable, (sizeof(ctable) / 4)));
}

/**
 * Reads the XPM42 file header which usually consists of a
 * file type declaration of "!XPM42" followed by the next line
 * containing image information such as width, height, unique color
 * count and finally the color mode. Which is either c for Color or
 * m for Monochrome.
 */
static bool	mlx_read_xpm_header(t_xpm *xpm, FILE *file)
{
	int32_t	flagc;
	char	buffer[64];

	memset(buffer, '\0', sizeof(buffer));
	if (!fgets(buffer, sizeof(buffer), file))
		return (false);
	if (strncmp(buffer, "!XPM42\n", sizeof(buffer)) != 0)
		return (false);
	if (!fgets(buffer, sizeof(buffer), file))
		return (false);
	flagc = sscanf(buffer, "%i %i %i %i %c\n", &xpm->texture.width, \
	&xpm->texture.height, &xpm->color_count, &xpm->cpp, &xpm->mode);
	if (flagc < 4 || xpm->texture.width > INT16_MAX || \
	xpm->texture.height > INT16_MAX)
		return (false);
	if (!(xpm->mode == 'c' || xpm->mode == 'm') || xpm->cpp > 10)
		return (false);
	xpm->texture.pixels = calloc(xpm->texture.width * \
		xpm->texture.height, sizeof(int32_t));
	if (!xpm->texture.pixels)
		return (false);
	xpm->texture.bytes_per_pixel = sizeof(int32_t);
	return (mlx_read_table(xpm, file));
}

t_xpm	*mlx_load_xpm42(const char *path)
{
	t_xpm	*xpm;
	FILE	*file;

	xpm = NULL;
	if (!strstr(path, ".xpm42"))
		return ((void *)mlx_error(MLX_INVEXT));
	file = fopen(path, "r");
	if (!file)
		return ((void *)mlx_error(MLX_INVFILE));
	xpm = calloc(1, sizeof(t_xpm));
	if (!xpm)
		return ((void *)mlx_error(MLX_MEMFAIL));
	if (!mlx_read_xpm_header(xpm, file))
	{
		mlx_freen(2, xpm->texture.pixels, xpm);
		mlx_error(MLX_INVXPM);
		xpm = NULL;
	}
	fclose(file);
	return (xpm);
}
