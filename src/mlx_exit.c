/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <main@w2wizard.dev>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:43:22 by W2Wizard      #+#    #+#                 */
/*   Updated: 2023/06/08 18:12:20 by XEDGit        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

static void mlx_free_image(void* content)
{
	mlx_image_t* img = content;

	mlx_freen(4, img->context, img->pixels, img->instances, img);
}

//= Public =//

void mlx_close_window(mlx_t* mlx)
{
	MLX_NONNULL(mlx);
	glfwSetWindowShouldClose(mlx->window, true);
}

/**
 * All of glfw & glads resources are cleaned up by the terminate function.
 * Now it's time to clean up our own mess.
 */
void mlx_terminate(mlx_t* mlx)
{
	MLX_NONNULL(mlx);

	mlx_ctx_t *const mlxctx = mlx->context;

	glUseProgram(0);
	glLinkProgram(mlxctx->shaderprogram);
	glDeleteProgram(mlxctx->shaderprogram);
	glfwTerminate();
	mlx_lstclear((mlx_list_t**)(&mlxctx->hooks), &free);
	mlx_lstclear((mlx_list_t**)(&mlxctx->render_queue), &free);
	mlx_lstclear((mlx_list_t**)(&mlxctx->images), &mlx_free_image);
	mlx_freen(2, mlxctx, mlx);
}
