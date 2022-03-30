/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/03 20:13:17 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/29 18:01:45 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

#define GETLINE_BUFF 1280
/**
 * Function to read a file stream line by line.
 * Since getline is not a c standard function it does not exist on windows.
 * There for I created this function which is somewhat similarly to getline.
 * 
 * @param file File stream to read from.
 * @return Allocated result string or NULL if the EOF is encountered and no characters
 * have been read. If an error occurs, NULL is returned.
 */
char* mlx_getline(FILE* file)
{
	if (file == NULL)
		return (NULL);

	char* str;
	size_t size = 1;
	if (!(str = calloc(1, sizeof(char) * size)))
		return (NULL);

	char BUFF[GETLINE_BUFF + 1]; // Add space for '\0'
	while (fgets(BUFF, sizeof(BUFF), file))
	{
		char* new_str;
		size += sizeof(BUFF) - 1; // Dont need to account for BUFF's '\0'
		if (!(new_str = realloc(str, sizeof(char) * size)))
			return (free(str), NULL);
		str = new_str;

		strcat(str, BUFF);
		if (strrchr(BUFF, '\n'))
			return (str);
		memset(BUFF, 0, sizeof(BUFF));
	}
	if (size != 1)
		return (str);
	free(str);
	return (NULL);
}

/**
 * String hashing algorithm using FNV-1a.
 * Source: https://bit.ly/3JcRGHa
 * 
 * @param str The string to hash
 * @param len The length of the string.
 * @return The hashed output.
 */
uint64_t mlx_fnv_hash(char* str, size_t len)
{
	size_t i = 0;
	uint64_t hash;
	const uint64_t fnv_prime = 0x100000001b3;
	const uint64_t fnv_offset = 0xcbf29ce484222325;

	hash = fnv_offset;
	while (i < len)
	{
		hash ^= str[i++];
		hash *= fnv_prime;
	}
	return (hash);
}

/**
 * Utility function that lets you free x amount of pointers.
 * 
 * @param count The amount of args provided.
 * @param ... Any form of pointer.
 * @return False, this is simply for convinience when necessary.
 */
bool mlx_freen(int32_t count, ...)
{
	va_list	args;

	va_start(args, count);
	for (int32_t i = 0; i < count; i++)
		free(va_arg(args, void*));
	va_end(args);
	return (false);
}

/**
 * Converts an RGBA value to a monochrome/grayscale value.
 * It does so using specific weights for each channel.
 * 
 * @see https://goodcalculators.com/rgb-to-grayscale-conversion-calculator/
 * 
 * @param color The input RGBA value.
 * @return The rgba value converted to a grayscale color.
 */
uint32_t	mlx_rgba_to_mono(uint32_t color)
{
	const uint8_t r = 0.299f * ((color >> 24) & 0xFF);
	const uint8_t g = 0.587f * ((color >> 16) & 0xFF);
	const uint8_t b = 0.114f * ((color >> 8) & 0xFF);
	const uint8_t y = r + g + b;

	return (y << 24 | y << 16 | y << 8 | (color & 0xFF));
}

//= Public =//

int32_t mlx_get_time(void)
{
	return (glfwGetTime());
}

void mlx_focus(mlx_t* mlx)
{
	MLX_ASSERT(!mlx);
	glfwFocusWindow(mlx->window);
}
