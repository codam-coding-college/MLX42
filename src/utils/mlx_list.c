/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <main@w2wizard.dev>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 01:53:51 by W2Wizard      #+#    #+#                 */
/*   Updated: 2023/02/27 11:31:01 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

int32_t mlx_lstsize(mlx_list_t* lst)
{
	int32_t	i;

	for (i = 0; lst != NULL; i++)
		lst = lst->next;
	return (i);
}

static void mlx_lstdelone(mlx_list_t* lst, void (*del)(void *))
{
	if (del != NULL)
		del(lst->content);
	free(lst);
}

void mlx_lstclear(mlx_list_t** lst, void (*del)(void*))
{
	mlx_list_t* next_lst;

	while (*lst != NULL)
	{
		next_lst = (*lst)->next;
		mlx_lstdelone(*lst, del);
		*lst = next_lst;
	}
}

mlx_list_t* mlx_lstnew(void* content)
{
	mlx_list_t* out = NULL;

	if ((out = malloc(sizeof(mlx_list_t))))
	{
		out->content = content;
		out->next = NULL;
		out->prev = NULL;
	}
	return (out);
}

mlx_list_t* mlx_lstlast(mlx_list_t* lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void mlx_lstadd_back(mlx_list_t** lst, mlx_list_t* new)
{
	if (!lst || !new)
		return;
	if (!*lst)
		*lst = new;
	else
	{
		mlx_list_t* temp = mlx_lstlast(*lst);
		new->prev = temp;
		temp->next = new;
	}
}

void mlx_lstadd_front(mlx_list_t** lst, mlx_list_t* new)
{
	if (!lst || !new)
		return;
	if ((*lst) != NULL)
		(*lst)->prev = new;
	new->next = *lst;
	new->prev = NULL;
	*lst = new;
}

/**
 * Removes the specified content from the list, if found.
 * Also fixes any relinking that might be needed.
 *
 * @param[in] lst The list
 * @param[in] comp Function to check if the content and value are the same.
 * @returns The removed element, clean up as you wish.
 */
mlx_list_t* mlx_lstremove(mlx_list_t** lst, void* value, bool (*comp)(void*, void*))
{
	mlx_list_t* lstcpy = *lst;

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

// Retrieve Z value from queue.
static int32_t mlx_getzdata(mlx_list_t* entry)
{
	const draw_queue_t* queue = entry->content;

	return (queue->image->instances[queue->instanceid].z);
}

// Insert the entry back into head sorted.
static void mlx_insertsort(mlx_list_t** head, mlx_list_t* new)
{
	mlx_list_t* current;

	if (*head == NULL)
		*head = new;
	else if (mlx_getzdata(*head) >= mlx_getzdata(new))
	{
		new->next = *head;
		new->next->prev = new;
		*head = new;
	}
	else
	{
		current = *head;

		// Find insertion location.
		while (current->next != NULL && mlx_getzdata(current->next) < mlx_getzdata(new))
			current = current->next;
		new->next = current->next;

		// Insert at the end
		if (current->next != NULL)
			new->next->prev = new;
		current->next = new;
		new->prev = current;
	}
}

/**
 * Okay-ish sorting algorithm to sort the render queue / doubly linked list.
 * We need to do this to fix transparency.
 *
 * @param lst The render queue.
 */
void mlx_sort_renderqueue(mlx_list_t** lst)
{
	mlx_list_t* sorted = NULL;
	mlx_list_t* lstcpy = *lst;

	while (lstcpy != NULL)
	{
		mlx_list_t* next = lstcpy->next;

		// Separate entry out of list and insert it back but sorted.
		lstcpy->prev = lstcpy->next = NULL;
		mlx_insertsort(&sorted, lstcpy);
		lstcpy = next;
	}
	*lst = sorted;
}
