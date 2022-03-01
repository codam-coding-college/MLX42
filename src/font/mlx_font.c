/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_font.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 12:01:37 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 22:37:45 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "MLX42/MLX42_Int.h"

/**
 * Retrieves the X offset of the given char in the font texture strip.
 * 
 * NOTE: Cheesy branchless operation :D
 * 
 * @param c The char to find.
 * @return Non-negative if found or -1 if not found.
 */
static int32_t mlx_get_texoffset(char c)
{
	const bool	_isprint = isprint(c);

	return (-1 * !_isprint + ((FONT_WIDTH + 2) * (c - 32)) * _isprint);
}

/**
 * Does the actual copying of pixels form the atlas buffer to the
 * image buffer.
 * 
 * Skips any non-printable characters.
 * 
 * @param image The image to draw on.
 * @param texture The font_atlas.
 * @param texoffset The character texture X offset.
 * @param imgoffset The image X offset.
 */
static void mlx_draw_font(mlx_image_t* image, const mlx_texture_t* texture, int32_t texoffset, int32_t imgoffset)
{
	uint32_t y = 0;
	uint8_t* pixelx = NULL;
	uint8_t* pixeli = NULL;
	const uint32_t bpp = texture->bytes_per_pixel;

	if (texoffset < 0)
		return;

	while (y < FONT_HEIGHT)
	{
		pixelx = texture->pixels + ((y * texture->width + texoffset) * bpp);
		pixeli = image->pixels + ((y * image->width + imgoffset) * bpp);
		memcpy(pixeli, pixelx, FONT_WIDTH * bpp);
		y++;
	}
}

/**
 * Draws the given text onto an image.
 * 
 * @param str The string to draw.
 * @param image The target image.
 */
static void	mlx_draw_text(const char* str, mlx_image_t* image)
{
	size_t i = 0;
	int32_t imgoffset = 0;

	// We need to 'convert' it from one struct to another.
	const mlx_texture_t atlas = {
		font_atlas.width,
		font_atlas.height,
		font_atlas.bpp,
		font_atlas.pixels,
	};

	while (str[i])
	{
		mlx_draw_font(image, &atlas, mlx_get_texoffset(str[i++]), imgoffset);
		imgoffset += FONT_WIDTH;
	}
}

mlx_image_t* mlx_put_string(mlx_t* mlx, const char* str, int32_t x, int32_t y)
{
	mlx_image_t* strimage;

	if (!mlx || !str)
		return (mlx_error(MLX_NULLARG));
	if (!(strimage = mlx_new_image(mlx, strlen(str) * FONT_WIDTH, FONT_HEIGHT)))
		return (NULL);
	mlx_draw_text(str, strimage);
	if (!mlx_image_to_window(mlx, strimage, x, y))
		return (mlx_delete_image(mlx, strimage), NULL);
	return (strimage);
}
