/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_hash.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:32:12 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 13:06:45 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

/**
 * String hashing algorithm using FNV-1a.
 * Source: https://bit.ly/3JcRGHa
 * 
 * @param str The string to hash
 * @param len The length of the string.
 * @return The hashed output.
 */
uint64_t	mlx_fnv_hash(char *str, size_t len)
{
	size_t			i;
	uint64_t		hash;
	const uint64_t	fnv_prime = 0x100000001b3;
	const uint64_t	fnv_offset = 0xcbf29ce484222325;

	i = 0;
	hash = fnv_offset;
	while (i < len)
	{
		hash ^= str[i++];
		hash *= fnv_prime;
	}
	return (hash);
}
