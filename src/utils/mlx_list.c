/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_list.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 01:53:51 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/07/21 10:34:36 by sbos          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

int32_t mlx_lstsize(mlx_list_t* lst)
{
	int32_t	i = 0;

	if (!lst)
		return (i);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
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
	while (lst)
	{
		if (!lst->next)
			break;
		lst = lst->next;
	}
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
	new->next = *lst;
	new->prev = NULL;
	*lst = new;
}

// TODO: Move this somewhere else...
bool mlx_equal_image(void* lstcontent, void* value)
{
	const mlx_image_t* lcontent = lstcontent;
	const mlx_image_t* lvalue = value;

	return (lcontent == lvalue);
}

bool mlx_equal_inst(void* lstcontent, void* value)
{
	const draw_queue_t* lcontent = lstcontent;
	const mlx_image_t* lvalue = value;

	return (lcontent->image == lvalue);
}

/**
 * Removes the specified content form the list, if found.
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
static int32_t mlx_getdata(mlx_list_t* entry)
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
	else if (mlx_getdata(*head) >= mlx_getdata(new))
	{
		new->next = *head;
		new->next->prev = new;
		*head = new;
	}
	else
	{
		current = *head;

		// Find insertion location.
		while (current->next != NULL && mlx_getdata(current->next) < mlx_getdata(new))
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
