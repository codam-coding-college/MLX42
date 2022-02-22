/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_font.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 12:01:37 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/22 15:33:59 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "MLX42/MLX42_Int.h"

bool	mlx_parse_font_atlas(t_mlx *mlx)
{
	int32_t			i;
	t_mlx_texture	font;
	t_mlx_ctx		*mlxctx;
	int32_t			xy[2];
	int32_t			wh[2];

	i = -1;
	wh[0] = FONT_WIDTH;
	wh[1] = FONT_HEIGHT;
	memset(xy, 0, sizeof(xy));
	mlxctx = mlx->context;
	font.width = font_atlas.width;
	font.height = font_atlas.height;
	font.bytes_per_pixel = font_atlas.bpp;
	font.pixels = font_atlas.pixels;
	while (++i < 94)
	{
		mlxctx->char_images[i] = \
		mlx_texture_area_to_image(mlx, &font, (int32_t *)xy, (uint32_t *)wh);
		if (mlxctx->char_images[i] == NULL)
			return (false);
		xy[0] += FONT_WIDTH + 2;
	}
	return (true);
}

void	mlx_put_string(t_mlx *mlx, char *str, int32_t x, int32_t y)
{
	size_t		i;
	int32_t		gx;
	t_mlx_ctx	*mlxctx;

	i = 0;
	gx = x;
	mlxctx = mlx->context;
	while (str[i] != '\0')
	{
		if (isprint(str[i]))
		{
			mlx_image_to_window(mlx, mlxctx->char_images[str[i] - 32], gx, y);
			gx += FONT_WIDTH;
		}
		i++;
	}
}
