/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 01:24:36 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/17 10:36:12 by W2Wizard      ########   odam.nl         */
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
	}
	return (true);
}

// Essentially just loops forever and executes the hooks and window size.
void	mlx_loop(t_mlx *mlx)
{
	t_mlx_ctx	*context;

	context = mlx->context;
	while (!glfwWindowShouldClose(mlx->window))
	{
		if (!mlx_handle_resize(mlx))
		{
			mlx_quit(mlx);
			mlx_error(MLX_MEMORY_FAIL);
		}
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mlx->width, mlx->height, \
		0, GL_RGBA, GL_UNSIGNED_BYTE, mlx->pixels);
		glBindVertexArray(context->shaderprogram);
		mlx_exec_loop_hooks(mlx);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(mlx->window);
		glfwPollEvents();
	}
}
