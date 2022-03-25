/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_xpm42.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 03:42:29 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/03 14:39:57 by lde-la-h      ########   odam.nl         */
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
 * Parses the XPM coolor value entry e.g: ".X #00FF00FF"
 * into the color table while also verifying the format.
 * 
 * @param xpm The XPM.
 * @param line The line to parse.
 * @param ctable The color hash table.
 * @param s Size of the hash table
 * @return True or false depending on if it sucessfully parsed the line.
 */
static bool mlx_insert_xpm_entry(xpm_t* xpm, char* line, uint32_t* ctable, size_t s)
{
	// NOTE: uintptr because windows likes to complain...
	// Verify the length of the Pixel string by checking backwards for the first
	// occurence of a space and then check the distance by comparing with cpp.
	if (((uintptr_t)strrchr(line, ' ') - (uintptr_t)line) != (uint64_t)xpm->cpp)
		return (false);
	if (!isspace(line[xpm->cpp]) || line[xpm->cpp + 1] != '#' || !isalnum(line[xpm->cpp + 2]))
		return (false);

	int32_t index = mlx_fnv_hash(line, xpm->cpp) % s;
	uint32_t color = (uint32_t)strtol(line + xpm->cpp + 2, NULL, 16);
	ctable[index] = xpm->mode == 'm' ? mlx_rgba_to_mono(color) : color;
	return (true);
}

/**
 * Retrieves the pixel data line by line and then processes each pixel
 * by hashing the characters and looking it up from the color table.
 * 
 * TODO: Use ssize_t as specified by getline.
 * 
 * @param xpm The XPM.
 * @param file The filepath to the XPM42 file.
 * @param ctable The color hash table.
 * @param s Size of the hash table.
 * @return True or false depending on if it sucessfully parsed the line.
 */
static bool mlx_read_data(xpm_t* xpm, FILE* file, uint32_t* ctable, size_t s)
{
	int64_t bread;
	size_t buffsize;
	char* line = NULL;

	for (int64_t y_xpm = 0; y_xpm < xpm->texture.height; y_xpm++)
	{
		if ((bread = getline(&line, &buffsize, file)) == -1)
			return (free(line), false);
		if (line[bread - 1] == '\n')
			bread--;
		if (bread != xpm->texture.width * xpm->cpp)
			return (free(line), false);

		// NOTE: Copy pixel by pixel as we need to retrieve the hash table.
		for (int64_t x_xpm = 0, x_line = 0; x_xpm < xpm->texture.width; x_xpm++, x_line += xpm->cpp)
		{
			uint8_t* pixelstart = &xpm->texture.pixels[(y_xpm * xpm->texture.width + x_xpm) * BPP];
			mlx_draw_pixel(pixelstart, ctable[mlx_fnv_hash(&line[x_line], xpm->cpp) % s]);
		}
	}
	free(line);
	return (true);
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
static bool mlx_read_table(xpm_t* xpm, FILE* file)
{
	size_t buffsize;
	char* line = NULL;
	int64_t bread = 0;
	uint32_t ctable[UINT16_MAX] = {0};

	for (int32_t i = 0; i < xpm->color_count; i++)
	{
		if ((bread = getline(&line, &buffsize, file)) == -1 || \
		!mlx_insert_xpm_entry(xpm, line, ctable, (sizeof(ctable) / BPP)))
			return (free(line), false);
	}
	free(line);
	return (mlx_read_data(xpm, file, ctable, (sizeof(ctable) / BPP)));
}

/**
 * Reads the XPM42 file header which usually consists of a
 * file type declaration of "!XPM42" followed by the next line
 * containing image information such as width, height, unique color
 * count and finally the color mode. Which is either c for Color or
 * m for Monochrome.
 */
static bool mlx_read_xpm_header(xpm_t* xpm, FILE *file)
{
	int32_t	flagc;
	char	buffer[64] = {0};

	// Check file type dec...
	if (!fgets(buffer, sizeof(buffer), file))
		return (false);
	if (strncmp(buffer, "!XPM42\n", sizeof(buffer)) != 0)
		return (false);

	// Get header info ...
	if (!fgets(buffer, sizeof(buffer), file))
		return (false);
	flagc = sscanf(buffer, "%i %i %i %i %c\n", &xpm->texture.width, &xpm->texture.height, &xpm->color_count, &xpm->cpp, &xpm->mode);
	if (flagc < 4 || xpm->texture.width > INT16_MAX || xpm->texture.height > INT16_MAX || \
		!(xpm->mode == 'c' || xpm->mode == 'm') || xpm->cpp > 10)
		return (false);
	xpm->texture.bytes_per_pixel = BPP;
	xpm->texture.pixels = calloc(xpm->texture.width * xpm->texture.height, sizeof(int32_t));
	return (xpm->texture.pixels != NULL ? mlx_read_table(xpm, file) : false);
}

//= Public =//

xpm_t* mlx_load_xpm42(const char* path)
{
	FILE* file;
	xpm_t* xpm = NULL;

	if (!strstr(path, ".xpm42"))
		return ((void*)mlx_error(MLX_INVEXT));
	if (!(file = fopen(path, "r")))
		return ((void*)mlx_error(MLX_INVFILE));
	if (!(xpm = calloc(1, sizeof(xpm_t))))
		return ((void*)mlx_error(MLX_MEMFAIL));
	if (!mlx_read_xpm_header(xpm, file))
	{
		mlx_freen(2, xpm->texture.pixels, xpm);
		mlx_error(MLX_INVXPM);
		xpm = NULL;
	}
	fclose(file);
	return (xpm);
}

void mlx_delete_xpm42(xpm_t* xpm)
{
	if (!xpm)
	{
		mlx_error(MLX_NULLARG);
		return;
	}
	free(xpm->texture.pixels);
	free(xpm);
}
