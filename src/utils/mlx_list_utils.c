/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_list_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:20:51 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/17 11:52:25 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

bool	mlx_equal_image(void *lstcontent, void *value)
{
	const t_mlx_image	*lcontent = lstcontent;
	const t_mlx_image	*lvalue = value;

	return (lcontent == lvalue);
}

bool	mlx_equal_inst(void *lstcontent, void *value)
{
	const t_draw_queue	*lcontent = lstcontent;
	const t_mlx_image	*lvalue = value;

	return (lcontent->image == lvalue);
}

void	mlx_lstadd_front(t_mlx_list **lst, t_mlx_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	new->prev = NULL;
	*lst = new;
}

/**
 * Removes the specified content form the list, if found.
 * Also fixes any relinking that might be needed.
 *  
 * @param[in] lst The list
 * @param[in] comp Function to check if the content and value are the same.
 * @returns The removed element, clean up as you wish.
 */
t_mlx_list	*mlx_lstremove(t_mlx_list **lst, void *value, \
bool (*comp)(void *, void*))
{
	t_mlx_list		*temp;
	t_mlx_list		*prev;

	temp = *lst;
	if (temp != NULL && comp(temp->content, value))
	{
		*lst = temp->next;
		temp->prev = NULL;
		temp->next = NULL;
		return (temp);
	}
	while (temp && !comp(temp->content, value))
	{
		prev = temp->prev;
		temp = temp->next;
	}
	if (!temp)
		return (NULL);
	prev->next = temp->next;
	temp->next = NULL;
	temp->prev = NULL;
	return (temp);
}
