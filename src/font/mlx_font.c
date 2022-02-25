/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_font.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 12:01:37 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/25 15:57:42 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "MLX42/MLX42_Int.h"

// Overwrite error code on purpose, the previous ones are to broad in scope.
bool	mlx_parse_font_atlas(t_mlx *mlx)
{
	int32_t				i;
	int32_t				xy[2];
	int32_t				wh[2];
	t_mlx_ctx *const	mlxctx = mlx->context;
	const t_mlx_texture	font = (t_mlx_tex)
	{
		font_atlas.width,
		font_atlas.height,
		font_atlas.bpp,
		font_atlas.pixels
	};

	i = -1;
	wh[0] = FONT_WIDTH;
	wh[1] = FONT_HEIGHT;
	memset(xy, 0, sizeof(xy));
	while (++i < 94)
	{
		mlxctx->char_images[i] = mlx_texture_area_to_image(mlx, \
		(t_mlx_tex *)&font, (int32_t *)xy, (uint32_t *)wh);
		if (mlxctx->char_images[i] == NULL)
			return (mlx_error(MLX_INVFONT));
		xy[0] += FONT_WIDTH + 2;
	}
	return (true);
}

void	mlx_put_string(t_mlx *mlx, char *str, int32_t x, int32_t y)
{
	size_t			i;
	int32_t			gx;
	const t_mlx_ctx	*mlxctx = mlx->context;

	i = 0;
	gx = x;
	while (str[i] != '\0')
	{
		if (isprint(str[i]))
		{
			if (!mlx_image_to_window(mlx, \
			mlxctx->char_images[str[i++] - 32], gx, y))
				return ;
			gx += FONT_WIDTH;
		}
	}
}
