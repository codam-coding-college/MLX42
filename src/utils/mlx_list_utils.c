/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_list_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/31 15:20:51 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 13:09:03 by lde-la-h      ########   odam.nl         */
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
	t_mlx_list	*lstcpy;

	lstcpy = *lst;
	while (lstcpy && !comp(lstcpy->content, value))
		lstcpy = lstcpy->next;
	if (lstcpy == NULL)
		return (NULL);
	if (lstcpy == *lst)
		*lst = lstcpy->next;
	if (lstcpy->next != NULL)
		lstcpy->next->prev = lstcpy->prev;
	if (lstcpy->prev != NULL)
		lstcpy->prev->next = lstcpy->next;
	return (lstcpy);
}
