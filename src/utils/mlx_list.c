/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 01:53:51 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/31 15:12:24 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

int32_t	mlx_lstsize(t_mlx_list *lst)
{
	int32_t	i;

	i = 0;
	if (!lst)
		return (i);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	mlx_lstclear(t_mlx_list **lst, void (*del)(void*))
{
	if (!*lst)
		return ;
	if ((*lst)->next)
		mlx_lstclear(&(*lst)->next, del);
	del((*lst)->content);
	free(*lst);
	(*lst) = NULL;
}

t_mlx_list	*mlx_lstnew(void *content)
{
	t_mlx_list	*out;

	out = malloc(sizeof(t_mlx_list));
	if (out)
	{
		out->content = content;
		out->next = NULL;
		out->prev = NULL;
		return (out);
	}
	return (NULL);
}

t_mlx_list	*mlx_lstlast(t_mlx_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	mlx_lstadd_back(t_mlx_list **lst, t_mlx_list *new)
{
	t_mlx_list	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		temp = mlx_lstlast(*lst);
		new->prev = temp;
		temp->next = new;
	}
}
