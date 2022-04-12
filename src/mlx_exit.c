/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:43:22 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/04/13 00:08:15 by w2wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

static void mlx_free_image(void* content)
{
	mlx_image_t* img = content;

	mlx_freen(3, img->context, img->pixels, img->instances);
}

//= Public =//

void mlx_close_window(mlx_t* mlx)
{
	MLX_ASSERT(!mlx);
	glfwSetWindowShouldClose(mlx->window, true);
}

/**
 * All of glfw & glads resources are cleaned up by the terminate function.
 * Now its time to cleanup our own mess.
 */
void mlx_terminate(mlx_t* mlx)
{
	MLX_ASSERT(!mlx);

	mlx_ctx_t *const mlxctx = mlx->context;

	glfwTerminate();
	mlx_lstclear((mlx_list_t**)(&mlxctx->hooks), &free);
	mlx_lstclear((mlx_list_t**)(&mlxctx->render_queue), &free);
	mlx_lstclear((mlx_list_t**)(&mlxctx->images), &mlx_free_image);
	mlx_freen(2, mlxctx, mlx);
}
