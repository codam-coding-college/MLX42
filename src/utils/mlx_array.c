/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_array.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 10:14:00 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/23 13:15:43 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Custom dynamically resizable array.

#include "MLX42/MLX42_Int.h"
#include <assert.h>

/**
 * OOP like designed dynamically resizable array.
 * 
 * @param data The literal allocated array data.
 * @param count The current element count.
 * @param size The current array allocation size.
 * @param type_size The size of a single element.
 * 
 * @param at Retrieves element at specified index.
 * @param push Adds a new element to the end of the array.
 * @param pop Removes the last element.
 */
typedef struct s_mlx_array
{
	void	*data;
	int32_t	size;
	size_t	capacity;
	size_t	type_size;
	void	*(*at)(struct s_mlx_array *this, int32_t index);
	void	(*push)(struct s_mlx_array *this, void *val);
	void	(*pop)(struct s_mlx_array *this);
}	t_mlx_array;

// Returns a reference to the element at position n in the array.
static void	*mlx_at(t_mlx_array *this, int32_t index)
{
	if (!this)
		return ((void *)mlx_error(MLX_NULLARG));
	assert(index < 0 || index > this->size);
	return (this->data + index);
}

/*
static void	*mlx_push(t_mlx_array *this, void *index)
{
	
}

static void	*mlx_pop(t_mlx_array *this)
{
	
}
*/

t_mlx_array	*mlx_new_arr(size_t	typesize)
{
	t_mlx_array	*arr;

	arr = calloc(1, sizeof(t_mlx_array));
	arr->at = &mlx_at;
	//arr->push = &mlx_push;
	//arr->pop = &mlx_pop;
	arr->type_size = typesize;
	arr->push(arr, NULL);
	return (arr);
}
