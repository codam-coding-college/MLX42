/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_font.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 12:01:37 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/28 13:20:33 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "MLX42/MLX42_Int.h"

static void	mlx_draw_font(t_mlx_image *image, const t_mlx_texture *texture, \
int32_t texoffset, int32_t imgoffset)
{
	uint32_t	y;
	uint32_t	bpp;
	uint8_t		*pixelx;
	uint8_t		*pixeli;

	y = 0;
	bpp = texture->bytes_per_pixel;
	while (y < FONT_HEIGHT)
	{
		pixelx = &texture->pixels[(y * texture->width + texoffset) * bpp];
		pixeli = &image->pixels[(y * image->width + imgoffset) * bpp];
		memmove(pixeli, pixelx, FONT_WIDTH * bpp);
		y++;
	}
}

static bool	mlx_draw_text(const char *str, t_mlx_image *image)
{
	size_t				i;
	int32_t				imgoffset;
	int32_t				texoffset;
	const t_mlx_tex		atlas = {
		font_atlas.width,
		font_atlas.height,
		font_atlas.bpp,
		font_atlas.pixels,
	};

	i = 0;
	imgoffset = 0;
	while (str[i])
	{
		// Get character offset in the atlas texture
		texoffset = (FONT_WIDTH + 2) * (str[i] - 32);
		//printf("Draw: %c Pos: %d %d | CharOffset @ %d\n", str[i], imgoffset, 0, texoffset);
		mlx_draw_font(image, &atlas, texoffset, imgoffset);
		imgoffset += FONT_WIDTH;
		i++;
	}
	return (true);
}

t_mlx_image	*mlx_put_string(t_mlx *mlx, const char *str, int32_t x, int32_t y)
{
	int32_t		total_width;
	t_mlx_image	*strimage;

	total_width = strlen(str) * (FONT_WIDTH);
	//printf("Draw img with width: %d\n", total_width);
	strimage = mlx_new_image(mlx, total_width, FONT_HEIGHT);
	if (!strimage)
		return (NULL);
	mlx_draw_text(str, strimage);
	if (!mlx_image_to_window(mlx, strimage, x, y))
		return (mlx_delete_image(mlx, strimage), NULL);
	return (strimage);
}
