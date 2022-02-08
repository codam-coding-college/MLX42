/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_xpm42.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 03:42:29 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/08 23:33:28 by W2Wizard      ########   odam.nl         */
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

// Basicaly just "putpixels" every pixel character it finds onto the buffer.
static bool	mlx_read_data(t_xpm *xpm, FILE *file, uint32_t *ctable)
{
	int64_t	x;
	int64_t	y;
	int64_t	bread;
	size_t	buffsize;
	char	*line;

	y = -1;
	line = NULL;
	while (++y < xpm->texture.height)
	{
		x = 0;
		bread = getline(&line, &buffsize, file);
		if (bread == -1 || bread < xpm->texture.width)
			return (mlx_freen(1, line));
		while (x < xpm->texture.width)
		{
			mlx_xpm_putpixel(xpm, x, y, ctable[(uint32_t)line[x]]);
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
		if (xpm->mode == 'm')
			ctable[(int32_t)line[0]] = \
			mlx_rgba_to_mono(mlx_atoi_base(&(line[1]), 16));
		else
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
 * Because fscanf is amazing we do a single seek of 1 byte forward
 * to skip the newline... Adding a newline to the fscanf technically works
 * but XPM's have the tendency to have the ' ' character as a pixel and having
 * that newline causes the file pointer to skip that very important
 * space!!! W T F!!! This causes an issue as now we when we call getline
 * we don't get those spaces anymore and only a color which the program
 * then assumes is invalid! I need to check this a bit more however.
 * 
 * TODO: xpm->mode != 'c' || xpm->mode != 'm'
 */
static bool	mlx_read_xpm_header(t_xpm *xpm, FILE *file)
{
	int32_t	flagc;
	char	buffer[128];

	memset(buffer, '\0', sizeof(buffer));
	flagc = fscanf(file, "%127s\n", buffer);
	if (flagc < 1 || strncmp(buffer, "!XPM42", sizeof(buffer)) != 0)
		return (false);
	flagc = fscanf(file, "%i %i %i %c", &xpm->texture.width, \
	&xpm->texture.height, &xpm->color_count, &xpm->mode);
	if (flagc < 4 || xpm->texture.width < 0 || \
		xpm->texture.width > UINT16_MAX || xpm->texture.height < 0 || \
		xpm->texture.height > UINT16_MAX)
		return (false);
	xpm->texture.pixels = calloc(xpm->texture.width * \
		xpm->texture.height, sizeof(int32_t));
	if (!xpm->texture.pixels)
		return (false);
	xpm->texture.bytes_per_pixel = sizeof(int32_t);
	fseek(file, ftell(file) + 1, SEEK_SET);
	return (mlx_read_table(xpm, file));
}

void	mlx_draw_xpm42(t_mlx_image *image, t_xpm *xpm, int32_t X, int32_t Y)
{
	int32_t	i;
	int32_t	j;
	uint8_t	*pixel;

	if (!xpm || !image)
	{
		mlx_log(MLX_WARNING, MLX_NULL_ARG);
		return ;
	}
	i = 0;
	while (i < xpm->texture.height)
	{
		j = 0;
		while (j < xpm->texture.width)
		{
			pixel = &xpm->texture.pixels[(i * xpm->texture.width + j) * \
			sizeof(int32_t)];
			mlx_putpixel(image, X + j, Y + i, *pixel << 24 | \
			*(pixel + 1) << 16 | *(pixel + 2) << 8 | *(pixel + 3));
			j++;
		}
		i++;
	}
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
		mlx_freen(2, xpm->texture.pixels, xpm);
		mlx_log(MLX_ERROR, MLX_XPM_FAILURE);
		xpm = NULL;
	}
	fclose(file);
	return (xpm);
}
