/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_xpm42.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 03:42:29 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/07 18:35:20 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"
#include <string.h>

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
 * 
 * 
 * @param xpm 
 * @param color 
 * @param x 
 * @param y 
 * @return If it managed to add 
 */
bool	mlx_add_pixel(t_xpm *xpm, uint32_t color, int32_t x, int32_t y)
{
	uint8_t	*pixelstart;

	pixelstart = &xpm->pixels[(y * xpm->width + x) * sizeof(int32_t)];
	*(xpm->pixels + 0) = (uint8_t)((color >> 24) & 0xFF);
	*(xpm->pixels + 1) = (uint8_t)((color >> 16) & 0xFF);
	*(xpm->pixels + 2) = (uint8_t)((color >> 8) & 0xFF);
	*(xpm->pixels + 3) = (uint8_t)((color >> 0) & 0xFF);
	return (true);
}

void	mlx_draw_xpm(t_mlx_image *image, t_xpm *xpm, int32_t X, int32_t Y)
{
	uint8_t		*pixel;
	uint32_t	color;
	int32_t		i;
	int32_t		j;

	i = 0;
	while (i < xpm->height)
	{
		j = 0;
		while (j < xpm->width)
		{
			pixel = &image->pixels[((Y + i) * image->width + X + j) * \
				sizeof(int32_t)];
			color = (*(uint32_t *)
					(xpm->pixels + (j * 4 + (i * xpm->width * 4))) / 256);
			*(uint32_t *)pixel = color;
			j++;
		}
		i++;
	}
}

static bool	mlx_read_data(t_xpm *xpm, FILE *file, uint32_t *ctable)
{
	int64_t	x;
	int64_t	y;
	int64_t	bread;
	size_t	buffsize;
	char	*line;

	y = -1;
	line = NULL;
	(void) ctable;
	while (++y < xpm->height)
	{
		x = 0;
		bread = getline(&line, &buffsize, file);
		if (bread == -1 || bread < xpm->width)
			return (mlx_freen(1, line));
		while (x < xpm->width)
		{
			if (!mlx_add_pixel(xpm, ctable[(uint32_t)line[x]], x, y))
				return (mlx_freen(1, line));
			x++;
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
 * TODO: Make actual function that ensure that the string follows these rules!
 */
static bool	mlx_read_table(t_xpm *xpm, FILE *file)
{
	char		*line;
	int32_t		i;
	int64_t		bread;
	size_t		buffsize;
	uint32_t	ctable[UINT8_MAX];

	i = -1;
	line = NULL;
	memset(ctable, 0, sizeof(ctable));
	while (++i < xpm->color_count)
	{
		bread = getline(&line, &buffsize, file);
		if (bread < 1 || !isascii(line[0]) || !isspace(line[1]) || \
			line[2] != '#' || !isalnum(line[3]))
			return (mlx_freen(1, line));
		ctable[(int32_t)line[0]] = mlx_atoi_base(&(line[1]), 16);
	}
	free(line);
	return (mlx_read_data(xpm, file, ctable));
}

/**
 * Reads the XPM42 file header which usually consists of a
 * file type declaration of "!XPM42" followed by the next line
 * containing image information such as width, height, unique color
 * count and finally the color mode. Which is either c for Color or
 * m for Monochrome.
 * 
 * TODO: xpm->mode != 'c' || xpm->mode != 'm'
 * 
 * @param xpm The XPM image.
 * @param file The XPM file pointer.
 * @return Wether or not it was successful to parse the header.
 */
static bool	mlx_read_xpm_header(t_xpm *xpm, FILE *file)
{
	int32_t	flagc;
	char	buffer[128];

	memset(buffer, '\0', sizeof(buffer));
	flagc = fscanf(file, "%128s\n", buffer);
	if (flagc < 1 || strncmp(buffer, "!XPM42", sizeof(buffer)) != 0)
		return (false);
	flagc = fscanf(file, "%i %i %i %c\n", &xpm->width, &xpm->height, \
	&xpm->color_count, &xpm->mode);
	if (flagc < 4 || xpm->width < 0 || xpm->width > UINT16_MAX || \
		xpm->height < 0 || xpm->height > UINT16_MAX)
		return (false);
	xpm->pixels = calloc(xpm->width * xpm->height, sizeof(int32_t));
	if (!xpm->pixels)
		return (false);
	return (mlx_read_table(xpm, file));
}

t_xpm	*mlx_load_xpm42(const char *path)
{
	t_xpm	*xpm;
	FILE	*file;

	xpm = NULL;
	if (!strstr(path, ".xpm42"))
		return ((void *)mlx_log(MLX_ERROR, MLX_INVALID_FILE_EXT));
	file = fopen(path, "r");
	if (!file)
		return ((void *)mlx_log(MLX_ERROR, MLX_INVALID_FILE));
	xpm = malloc(sizeof(t_xpm));
	if (!xpm)
		return ((void *)mlx_log(MLX_ERROR, MLX_MEMORY_FAIL));
	if (!mlx_read_xpm_header(xpm, file))
	{
		mlx_freen(2, xpm->pixels, xpm);
		mlx_log(MLX_ERROR, MLX_XPM_FAILURE);
		xpm = NULL;
	}
	fclose(file);
	return (xpm);
}
