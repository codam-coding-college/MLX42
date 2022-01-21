/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 01:24:36 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/21 20:20:19 by W2Wizard      ########   odam.nl         */
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

static bool	mlx_handle_resize(t_mlx *mlx, t_mlx_image *img)
{
	const int32_t	old_width = img->width;
	const int32_t	old_height = img->height;

	glfwGetWindowSize(mlx->window, &(mlx->width), &(mlx->height));
	if (img->width != old_width || img->height != old_height)
	{
		printf("SETWEGWIEGJIWEG\n");
		img->pixels = realloc(img->pixels, \
		(img->width * img->height) * sizeof(int32_t));
		if (img->pixels == NULL)
			return (false);
		memset(img->pixels, 0, (img->width * img->height) * sizeof(int32_t));
	}
	return (true);
}

static void	mlx_render_images(t_mlx *mlx)
{
	t_mlx_ctx		*mlxctx;
	t_mlx_list		*images;
	t_mlx_image		*img;
	t_mlx_image_ctx	*imgctx;

	images = mlx->images;
	mlxctx = mlx->context;
	while (images)
	{
		img = images->content;
		imgctx = img->context;
		mlx_handle_resize(mlx, img);
		mlx_draw_image(mlx, img, 0, 0, 0);
		images = images->next;
	}
}

// Essentially just loops forever and executes the hooks and window size.
void	mlx_loop(t_mlx *mlx)
{
	double		start;
	double		oldstart;

	oldstart = 0;
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(mlx->window))
	{
		start = glfwGetTime();
		mlx->delta_time = start - oldstart;
		oldstart = start;
		glClearColor(1.0f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mlx_exec_loop_hooks(mlx);
		mlx_render_images(mlx);
		glfwSwapBuffers(mlx->window);
		glfwPollEvents();
	}
}
