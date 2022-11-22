/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/03 20:13:17 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/11/22 10:56:09 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

/**
 * Function to read a file stream line by line, reusing the same output pointer.
 * Since the same output pointer is reused it should only be freed once, either on success or failure.
 * This function is made to be somewhat similar to getline.
 * Getline can't be used directly since its not standard and therefore not available on all platforms.
 *
 * @param out Pointer to store output string.
 * @param out_size Pointer to store output strings length.
 * @param file File stream to read from.
 * @return True if line was read, false if EOF was reached or an error ocurred.
 */
bool mlx_getline(char** out, size_t* out_size, FILE* file)
{
	MLX_NONNULL(out);
	MLX_NONNULL(out_size);
	MLX_NONNULL(file);

	size_t size = 0;
	char* temp = NULL;
	static char BUFF[GETLINE_BUFF + 1]; // Add space for '\0'

	if (*out) *out[0] = '\0';

	while (fgets(BUFF, sizeof(BUFF), file))
	{
		size += strlen(BUFF);
		if (!(temp = realloc(*out, sizeof(char) * size + 1)))
			return (false);
		if (*out == NULL)
			memset(temp, '\0', size);
		temp[size] = '\0';

		*out = temp;
		*out_size = size;

		strncat(*out, BUFF, size);
		if (strrchr(BUFF, '\n'))
			return (true);
		memset(BUFF, '\0', sizeof(BUFF));
	}
	return (size);
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
	const uint64_t fnv_prime = 0x100000001b3;
	const uint64_t fnv_offset = 0xcbf29ce484222325;
	uint64_t hash = fnv_offset;

	for (size_t i = 0; i < len; i++)
	{
		hash ^= str[i];
		hash *= fnv_prime;
	}
	return (hash);
}

/**
 * Utility function that lets you free x amount of pointers.
 * 
 * @param count The amount of args provided.
 * @param ... Any form of pointer.
 * @return False, this is simply for convenience when necessary.
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
uint32_t mlx_rgba_to_mono(uint32_t color)
{
	const uint8_t r = 0.299f * ((color >> 24) & 0xFF);
	const uint8_t g = 0.587f * ((color >> 16) & 0xFF);
	const uint8_t b = 0.114f * ((color >> 8) & 0xFF);
	const uint8_t y = r + g + b;

	return (y << 24 | y << 16 | y << 8 | (color & 0xFF));
}

//= Public =//

double mlx_get_time(void)
{
	return (glfwGetTime());
}

void mlx_focus(mlx_t* mlx)
{
	MLX_NONNULL(mlx);

	glfwFocusWindow(mlx->window);
}
