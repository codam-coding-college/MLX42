/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_xpm42.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 03:42:29 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/07 15:17:51 by W2Wizard      ########   odam.nl         */
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
	ssize_t		output;
	int32_t		flagc;
	t_mlx_line	line;

	bzero(&line, sizeof(line));
	output = getline(&line.buff, &line.len, file);
	if (output == -1 || !strncmp(line.buff, "!XMP42", 7))
		return (false);
	output = getline(&line.buff, &line.len, file);
	if (output == -1)
	{
		free(line.buff);
		return (false);
	}
	flagc = sscanf(line.buff, "%d %d %d %c", &xpm->width, &xpm->height, \
	&xpm->color_count, &xpm->mode);
	free(line.buff);
	return (flagc == 4);
}

static bool	mlx_read_xpm_colors(t_xpm *xpm, FILE *file)
{
	(void)xpm;
	(void)file;
	return (false);
}
/*

static bool	mlx_read_xpm_data(t_xpm *xpm, FILE *file)
{
	return (false);
}

void	mlx_draw_xpm(t_mlx *mlx, t_xpm *xpm, int32_t X, int32_t Y)
{
	return ;
}
*/
t_xpm	*mlx_load_xpm42(const char *path)
{
	t_xpm	*xpm;
	FILE	*file;

	xpm = NULL;
	if (!strnstr(path, ".xpm42", PATH_MAX))
		return ((void *)mlx_error(MLX_INVALID_FILE_EXT));
	file = fopen(path, "r");
	if (!file)
		return ((void *)mlx_error(MLX_INVALID_FILE));
	xpm = malloc(sizeof(xpm));
	if (xpm)
		if (!mlx_read_xpm_header(xpm, file) || \
			!mlx_read_xpm_colors(xpm, file))
			free (xpm);
	fclose(file);
	return (xpm);
}
