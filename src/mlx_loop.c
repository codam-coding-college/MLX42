/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_loop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 01:24:36 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/05 13:04:59 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	mlx_exec_loop_hooks(t_MLX *mlx)
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

bool	mlx_loop_hook(t_MLX *mlx, void (*f)(void *), void *param)
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

// Essentially just loops forever and executes the hooks and window size.
// glfwGetFramebufferSize(mlx->window, &(mlx->width), &(mlx->height));
void	mlx_loop(t_MLX *mlx)
{
	t_mlx_ctx	*context;

	context = mlx->context;
	while (!glfwWindowShouldClose(mlx->window))
	{
		mlx_exec_loop_hooks(mlx);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mlx->width, mlx->height, \
		0, GL_RGBA, GL_UNSIGNED_BYTE, mlx->pixels);
		glBindVertexArray(context->shaderprogram);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(mlx->window);
		glfwPollEvents();
	}
}
