/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 01:24:36 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/24 15:36:22 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	mlx_exec_loop_hooks(t_mlx *mlx)
{
	t_mlx_list	*lstcpy;
	t_mlx_hook	*hook;

	lstcpy = mlx->hooks;
	while (lstcpy)
	{
		hook = ((t_mlx_hook *)lstcpy->content);
		hook->func(hook->param);
		lstcpy = lstcpy->next;
	}
}

bool	mlx_loop_hook(t_mlx *mlx, void (*f)(void *), void *param)
{
	t_mlx_list	*lst;
	t_mlx_hook	*hook;

	hook = malloc(sizeof(t_mlx_hook));
	if (!hook)
		return (false);
	hook->func = f;
	hook->param = param;
	lst = mlx_lstnew(hook);
	if (!lst)
	{
		free(hook);
		return (false);
	}
	mlx_lstadd_back((t_mlx_list **)(&mlx->hooks), lst);
	return (true);
}

/*
static bool	mlx_handle_resize(t_mlx *mlx, t_mlx_image *img)
{
	const int32_t	old_width = img->width;
	const int32_t	old_height = img->height;

	if (img->width != old_width || img->height != old_height)
	{
		img->pixels = realloc(img->pixels, \
		(img->width * img->height) * sizeof(int32_t));
		if (img->pixels == NULL)
			return (false);
		memset(img->pixels, 0, (img->width * img->height) * sizeof(int32_t));
	}
	return (true);
}
*/

static void	mlx_render_images(t_mlx *mlx)
{
	t_mlx_image		*img;
	t_mlx_image_ctx	*imgctx;
	t_mlx_list		*images;

	images = mlx->images;
	while (images)
	{
		img = images->content;
		imgctx = img->context;
		if (imgctx->draw)
			mlx_draw_image(mlx, img, img->x, img->y);
		images = images->next;
	}
}

int32_t	mlx_get_time(void)
{
	return (glfwGetTime());
}

// Essentially just loops forever and executes the hooks and window size.
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
