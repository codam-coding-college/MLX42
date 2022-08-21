/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_vec.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/20 21:33:52 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/08/20 21:33:52 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

static bool mlx_vector_resize(mlx_vec_t* v, int32_t capacity)
{
	MLX_NONNULL(v);

	void* data = realloc(v->data, v->elementSize * capacity);
	if (data) 
	{
		v->data = data;
		v->capacity = capacity;
		return (true);
	}
	return (mlx_error(MLX_MEMFAIL));
}

bool mlx_vector_init(mlx_vec_t* v, size_t elementSize)
{
	MLX_NONNULL(v);

	v->count = 0;
	v->capacity = 1;
    v->position = 0;
    v->elementSize = elementSize;
	if (!(v->data = malloc(elementSize * v->capacity)))
		return (mlx_error(MLX_MEMFAIL));
	return (true);
}

bool mlx_vector_push_back(mlx_vec_t* v, void* item)
{
	MLX_NONNULL(v);

	if (v->capacity == v->count && !mlx_vector_resize(v, v->capacity * 2))
		return (false);
		
	memcpy(v->data + v->position, item, v->elementSize);
    v->position += v->elementSize;
    v->count++;
	return (true);
}

void mlx_vector_set(mlx_vec_t* v, int32_t index, void* item)
{
	MLX_NONNULL(v);
	MLX_ASSERT(index >= 0 && index < v->count, "Out of bounds");

	memcpy(v->data + (index * v->elementSize), item, v->elementSize);
}

void* mlx_vector_get(mlx_vec_t* v, int32_t index)
{
	MLX_NONNULL(v);
	MLX_ASSERT(index >= 0 && index < v->count, "Out of bounds");

	return (v->data + (index * v->elementSize)); 
}

void mlx_vector_swap(mlx_vec_t* v, int32_t srcIndex, int32_t dstIndex)
{
	MLX_NONNULL(v);
	MLX_ASSERT(srcIndex >= 0 && srcIndex < v->count, "Src Out of bounds");
	MLX_ASSERT(dstIndex >= 0 && dstIndex < v->count, "Dst Out of bounds");

	int32_t srcPosition = v->elementSize * srcIndex;
	int32_t dstPosition = v->elementSize * dstIndex;

	void* temp = alloca(v->elementSize);

	memcpy(temp, v->data + srcPosition, v->elementSize);
	memcpy(v->data + srcPosition, v->data + dstPosition, v->elementSize);
	memcpy(v->data + dstPosition, temp, v->elementSize);
}

bool mlx_vector_delete(mlx_vec_t* v, int32_t index)
{
	MLX_NONNULL(v);
	MLX_ASSERT(index >= 0 && index < v->count, "Out of bounds");

    if (index == 0)
    {
        if (v->count == 1)
            v->position = 0;
        else
        {
            memcpy(v->data, v->data + v->elementSize, v->elementSize * v->count - 1);
            v->position -= v->elementSize;
        }
    }
    else if(index == v->count - 1)
        v->position -= v->elementSize;
	else
    {
        memcpy(v->data + (index * v->elementSize), v->data + ((index + 1) * v->elementSize), v->elementSize * (v->count - index));
        v->position = v->elementSize * (v->count - 1);
    }
    
    v->count--;

	if (v->count > 0 && v->count == v->capacity / 4)
		return (mlx_vector_resize(v, v->capacity / 2));
	return (true);
}

void mlx_vector_clear(mlx_vec_t* v)
{
	v->position = 0;
	v->count = 0;
}

void mlx_vector_free(mlx_vec_t* v)
{
	mlx_vector_clear(v);
	free(v->data);
	v->capacity = 0;
}
