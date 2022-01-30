/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_xpm42.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 03:42:29 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/30 21:55:52 by W2Wizard      ########   odam.nl         */
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

static bool	mlx_add_pixel(t_xpm *xpm, t_xpm42_entry *table, size_t *offset, \
char c)
{
	int32_t			i;
	t_xpm42_entry	ent;

	i = 0;
	while (i < xpm->color_count)
	{
		ent = table[i];
		if (ent.character == c)
		{
			*(xpm->pixels + *offset + 0) = (uint8_t)((ent.color >> 24) & 0xFF);
			*(xpm->pixels + *offset + 1) = (uint8_t)((ent.color >> 16) & 0xFF);
			*(xpm->pixels + *offset + 2) = (uint8_t)((ent.color >> 8) & 0xFF);
			*(xpm->pixels + *offset + 3) = (uint8_t)((ent.color >> 0) & 0xFF);
			*offset += 4;
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	mlx_read_xpm_data(t_xpm *xpm, FILE *file, t_xpm42_entry *table)
{
	size_t	i;
	size_t	j;
	size_t	len;
	int64_t	output;
	char	*buffer;

	j = 0;
	output = 0;
	buffer = NULL;
	(void) table;
	xpm->pixels = calloc(xpm->width * xpm->height, sizeof(int32_t));
	if (!(xpm->pixels))
		return ((void *)mlx_error(MLX_MEMORY_FAIL));
	while (output != -1)
	{
		i = 0;
		output = getline(&buffer, &len, file);
		while (output != -1 && (buffer[i] != '\0' && buffer[i] != '\n'))
		{
			if (!mlx_add_pixel(xpm, table, &j, buffer[i++]))
				return (mlx_freen(false, 2, buffer, xpm->pixels));
		}
	}
	free(buffer);
	return (true);
}

/**
 * Reads the XPM42 file header which usually consists of a
 * file type declaration of "!XPM42" followed by the next line
 * containing image information such as width, height, unique color
 * count and finally the color mode. Which is either c for Color or
 * m for Monochrome.
 * 
 * @param xpm The XPM image.
 * @param file The XPM file pointer.
 * @return Wether or not it was successful to parse the header.
 */
static bool	mlx_read_xpm_header(t_xpm *xpm, FILE *file)
{
	int32_t			i;
	int32_t			flagc;
	t_xpm42_entry	*table;
	char			buffer[128];

	i = 0;
	memset(buffer, '\0', sizeof(buffer));
	flagc = fscanf(file, "%s\n", buffer);
	if (flagc < 1 || !strstr(buffer, "!XPM42"))
		return (false);
	flagc = fscanf(file, "%i %i %i %c\n", &xpm->width, &xpm->height, \
	&xpm->color_count, &xpm->mode);
	if (flagc < 4)
		return (false);
	table = alloca(xpm->color_count * sizeof(t_xpm42_entry));
	while (i != xpm->color_count)
	{
		flagc = fscanf(file, "%c %s\n", &table[i].character, buffer);
		if (flagc < 2)
			return (false);
		table[i++].color = mlx_atoi_base(buffer, 16);
	}
	return (mlx_read_xpm_data(xpm, file, table));
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

// TODO: Add custom strnstr, seems like Linux doesn't have it ?
t_xpm	*mlx_load_xpm42(const char *path)
{
	t_xpm	*xpm;
	FILE	*file;

	xpm = NULL;
	if (!strstr(path, ".xpm42"))
		return ((void *)mlx_error(MLX_INVALID_FILE_EXT));
	file = fopen(path, "r");
	if (!file)
		return ((void *)mlx_error(MLX_INVALID_FILE));
	xpm = malloc(sizeof(t_xpm));
	if (!xpm)
		return ((void *)mlx_error(MLX_MEMORY_FAIL));
	if (!mlx_read_xpm_header(xpm, file))
	{
		free(xpm);
		xpm = NULL;
	}
	fclose(file);
	return (xpm);
}
