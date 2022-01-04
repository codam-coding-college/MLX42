/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/03 20:13:17 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/03 20:21:42 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

/**
 * Converts an RGBA value to a float component/vector.
 * 
 * @note Because norminette is so good! We need to do * without spaces :)
 * @param color The input RGBA value.
 * @param out Float buffer to apply the converted color values to.
 */
void	mlx_rgba_to_float(int32_t color, t_FVec4 *RGBA_Out)
{
	RGBA_Out->x = (float)(1.0f / UINT8_MAX) *((color >> 24) & 0xFF);
	RGBA_Out->y = (float)(1.0f / UINT8_MAX) *((color >> 16) & 0xFF);
	RGBA_Out->z = (float)(1.0f / UINT8_MAX) *((color >> 8) & 0xFF);
	RGBA_Out->w = (float)(1.0f / UINT8_MAX) *(color & 0xFF);
}

/**
 * Reads an entire file into a single allocated string.
 * 
 * @param FilePath The path to the file to read.
 * @return The files content in a single string.
 */
char	*mlx_readfile(const char *FilePath)
{
	FILE		*file;
	char		*shader;
	int64_t		filesize;

	file = fopen(FilePath, "r");
	if (!file)
		return (NULL);
	fseek(file, 0L, SEEK_END);
	filesize = ftell(file);
	fseek(file, 0L, SEEK_SET);
	shader = calloc(filesize, sizeof(char));
	if (!shader)
		return (NULL);
	fread(shader, sizeof(char), filesize, file);
	fclose(file);
	return (shader);
}