/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 01:24:36 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 17:55:30 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	mlx_exec_loop_hooks(t_mlx *mlx)
{
	t_mlx_list		*lstcpy;
	t_mlx_hook		*hook;
	const t_mlx_ctx	*mlxctx = mlx->context;

	lstcpy = mlxctx->hooks;
	while (lstcpy && !glfwWindowShouldClose(mlx->window))
	{
		hook = ((t_mlx_hook *)lstcpy->content);
		hook->func(hook->param);
		lstcpy = lstcpy->next;
	}
}

bool	mlx_loop_hook(t_mlx *mlx, void (*f)(void *), void *param)
{
	t_mlx_list		*lst;
	t_mlx_hook		*hook;
	const t_mlx_ctx	*mlxctx = mlx->context;

	if (!mlx || !f)
		return (mlx_error(MLX_NULLARG));
	hook = malloc(sizeof(t_mlx_hook));
	if (!hook)
		return (false);
	hook->func = f;
	hook->param = param;
	lst = mlx_lstnew(hook);
	if (!lst)
	{
		free(hook);
		return (mlx_error(MLX_MEMFAIL));
	}
	mlx_lstadd_back((t_mlx_list **)(&mlxctx->hooks), lst);
	return (true);
}

// 1. Iterate over images to upload the texture to the GPU
// to update pixel data.
// 2. Bind the texture and execute draw call.
static void	mlx_render_images(t_mlx *mlx)
{
	t_mlx_image			*image;
	t_draw_queue		*drawcall;
	const t_mlx_ctx		*mlxctx = mlx->context;
	const t_mlx_list	*imglst = mlxctx->images;
	const t_mlx_list	*render_queue = mlxctx->render_queue;

	while (imglst)
	{
		image = imglst->content;
		glBindTexture(GL_TEXTURE_2D, \
		((t_mlx_image_ctx *)image->context)->texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->width, image->height, \
		GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
		imglst = imglst->next;
	}
	while (render_queue)
	{
		drawcall = render_queue->content;
		if (drawcall && drawcall->image->enabled)
			mlx_draw_instance(drawcall->image, \
			&drawcall->image->instances[drawcall->instanceid]);
		render_queue = render_queue->next;
	}
}

// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
void	mlx_loop(t_mlx *mlx)
{
	double		start;
	double		oldstart;

	oldstart = 0;
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
		glfwSwapBuffers(mlx->window);
		glfwPollEvents();
	}
}
