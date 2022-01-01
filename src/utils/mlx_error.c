/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_error.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:51:54 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/01 16:50:04 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

/**
 * Simple error handling function.
 * 
 * @param error The error message to write.
 * @return Always false, for the sake of making it convenient. 
 */
bool	mlx_error(const char *error)
{
	fprintf(stderr, "%s%s", MLX_ERROR, error);
	return (false);
}
