/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 01:24:36 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/21 18:10:47 by W2Wizard      ########   odam.nl         */
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

static bool	mlx_handle_resize(t_mlx *mlx)
{
	const int32_t	old_width = mlx->width;
	const int32_t	old_height = mlx->height;

	glfwGetWindowSize(mlx->window, &(mlx->width), &(mlx->height));
	if (mlx->width != old_width || mlx->height != old_height)
	{
		mlx->pixels = realloc(mlx->pixels, \
		(mlx->width * mlx->height) * sizeof(int32_t));
		if (mlx->pixels == NULL)
			return (false);
		memset(mlx->pixels, 0, (mlx->width * mlx->height) * sizeof(int32_t));
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
		glActiveTexture(imgctx->texture);
		glBindTexture(GL_TEXTURE_2D, imgctx->texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mlx->width, mlx->height, \
		0, GL_RGBA, GL_UNSIGNED_BYTE, mlx->pixels);
		glUniform1i(glGetUniformLocation(mlxctx->shaderprogram, "texture"), 0);
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
		if (!mlx_handle_resize(mlx))
		{
			mlx_quit(mlx);
			mlx_error(MLX_MEMORY_FAIL);
			break ;
		}
		start = glfwGetTime();
		mlx->delta_time = start - oldstart;
		oldstart = start;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mlx_exec_loop_hooks(mlx);
		mlx_render_images(mlx);
		glfwSwapBuffers(mlx->window);
		glfwPollEvents();
	}
}
