/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 01:24:36 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/02 16:44:03 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

static void mlx_exec_loop_hooks(mlx_t* mlx)
{
	const mlx_ctx_t* mlxctx = mlx->context;

	mlx_list_t* lstcpy = mlxctx->hooks;
	while (lstcpy && !glfwWindowShouldClose(mlx->window))
	{
		mlx_hook_t* hook = ((mlx_hook_t*)lstcpy->content);
		hook->func(hook->param);
		lstcpy = lstcpy->next;
	}
}

static void mlx_render_images(mlx_t* mlx)
{
	const mlx_ctx_t* mlxctx = mlx->context;
	const mlx_list_t* imglst = mlxctx->images;
	const mlx_list_t* render_queue = mlxctx->render_queue;

	// Upload image textures to GPU
	while (imglst)
	{
		mlx_image_t* image = imglst->content;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ((mlx_image_ctx_t*)image->context)->texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->width, image->height, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
		imglst = imglst->next;
	}

	// Execute draw calls
	while (render_queue)
	{
		draw_queue_t* drawcall = render_queue->content;
		if (drawcall && drawcall->image->enabled)
			mlx_draw_instance(mlx->context, drawcall->image,
							  &drawcall->image->instances[drawcall->instanceid]);
		render_queue = render_queue->next;
	}
}

//= Public =//

bool mlx_loop_hook(mlx_t* mlx, void (*f)(void*), void* param)
{
	if (!mlx || !f)
		return (mlx_error(MLX_NULLARG));

	mlx_hook_t* hook;
	if (!(hook = malloc(sizeof(mlx_hook_t))))
		return (mlx_error(MLX_MEMFAIL));

	mlx_list_t* lst;
	if (!(lst = mlx_lstnew(hook)))
	{
		free(hook);
		return (mlx_error(MLX_MEMFAIL));
	}
	hook->func = f;
	hook->param = param;
	const mlx_ctx_t	*mlxctx = mlx->context;
	mlx_lstadd_back((mlx_list_t**)(&mlxctx->hooks), lst);
	return (true);
}

// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
void mlx_loop(mlx_t* mlx)
{
	double start, oldstart = 0;

	while (!glfwWindowShouldClose(mlx->window))
	{
		start = glfwGetTime();
		mlx->delta_time = start - oldstart;
		oldstart = start;
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetWindowSize(mlx->window, &(mlx->width), &(mlx->height));
		mlx_exec_loop_hooks(mlx);
		mlx_render_images(mlx);
		mlx_flush_batch(mlx->context);
		glfwSwapBuffers(mlx->window);
		glfwPollEvents();
	}
}
