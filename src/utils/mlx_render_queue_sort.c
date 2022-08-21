/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_render_queue_sort.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/20 21:33:52 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/08/20 21:33:52 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

void mlx_render_queue_sort(mlx_vec_t* render_queue)
{
    if(render_queue->count < 1)
        return;

    int32_t currentDepth = 0;
    for (int32_t i = 0; i < render_queue->count; i++)
    {
        draw_queue_t* element = mlx_vector_get(render_queue, i);
        mlx_instance_t* instance = &element->image->instances[element->instanceid];
        
        element->caluclatedDepth = instance->custom_depth > 0 ? instance->custom_depth : currentDepth++;
        // printf("%i -> %i\n", element->instanceid, element->caluclatedDepth);    
    }
    
    for (int32_t i = 0; i < render_queue->count; i++)
	{
		bool hasSwap = false;
		for (int32_t j = 0; j < render_queue->count - i - 1; j++)
		{
			draw_queue_t* aElement = mlx_vector_get(render_queue, j);
			draw_queue_t* bElement = mlx_vector_get(render_queue, j + 1);
			
			if (aElement->caluclatedDepth > bElement->caluclatedDepth)
			{
				mlx_vector_swap(render_queue, j, j + 1);
				hasSwap = true;
			}
		}
        
        if (!hasSwap)
            break;
	}

    // printf("firstInstanceToRender -> %i\n",  ((draw_queue_t*)mlx_vector_get(render_queue, 0))->instanceid);
    // printf("lastInstanceToRender -> %i\n",  ((draw_queue_t*)mlx_vector_get(render_queue, render_queue->count - 1))->instanceid);
}