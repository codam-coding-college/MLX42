#include "../include/MLX42/MLX42_Int.h"

// Retrieve Z value from queue.
static int32_t mlx_getzdata(mlx_list_t* entry)
{
	const draw_queue_t* queue = entry->content;

	return (queue->image->instances[queue->instanceid].z);
}

int testpositive()
{
	mlx_instance_t inst[6];
	inst[0].z = 4;
	inst[1].z = 2;
	inst[2].z = 87;
	inst[3].z = 3;
	inst[4].z = 9;
	inst[5].z = 7;
	mlx_image_t image;
	image.instances = inst;
	draw_queue_t dqueue[6];
	int i;
	for (i = 0; i < 6; i++)
	{
		dqueue[i].instanceid = i;
		dqueue[i].image = &image;
	}
	mlx_list_t *lst = NULL;
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 1));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 2));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 3));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 4));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 5));
	mlx_sort_renderqueue(&lst);
	mlx_list_t *lstcpy = lst;
	int prev = mlx_getzdata(lstcpy);
	while (lstcpy)
	{
		if (mlx_getzdata(lstcpy) < prev)
		{
			mlx_lstclear(&lst, NULL);
			return 1;
		}
		prev = mlx_getzdata(lstcpy);
		lstcpy = lstcpy->next;
	}
	mlx_lstclear(&lst, NULL);
	return 0;
}

int testnegative()
{
	mlx_instance_t inst[6];
	inst[0].z = -4;
	inst[1].z = -2;
	inst[2].z = -87;
	inst[3].z = -3;
	inst[4].z = -9;
	inst[5].z = -7;
	mlx_image_t image;
	image.instances = inst;
	draw_queue_t dqueue[6];
	int i;
	for (i = 0; i < 6; i++)
	{
		dqueue[i].instanceid = i;
		dqueue[i].image = &image;
	}
	mlx_list_t *lst = NULL;
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 1));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 2));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 3));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 4));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 5));
	mlx_sort_renderqueue(&lst);
	mlx_list_t *lstcpy = lst;
	int prev = mlx_getzdata(lstcpy);
	while (lstcpy)
	{
		if (mlx_getzdata(lstcpy) < prev)
		{
			mlx_lstclear(&lst, NULL);
			return 1;
		}
		prev = mlx_getzdata(lstcpy);
		lstcpy = lstcpy->next;
	}
	mlx_lstclear(&lst, NULL);
	return 0;
}

int testposneg()
{
	mlx_instance_t inst[6];
	inst[0].z = -4;
	inst[1].z = 2;
	inst[2].z = 87;
	inst[3].z = 3;
	inst[4].z = -9;
	inst[5].z = -7;
	mlx_image_t image;
	image.instances = inst;
	draw_queue_t dqueue[6];
	int i;
	for (i = 0; i < 6; i++)
	{
		dqueue[i].instanceid = i;
		dqueue[i].image = &image;
	}
	mlx_list_t *lst = NULL;
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 1));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 2));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 3));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 4));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 5));
	mlx_sort_renderqueue(&lst);
	mlx_list_t *lstcpy = lst;
	int prev = mlx_getzdata(lstcpy);
	while (lstcpy)
	{
		if (mlx_getzdata(lstcpy) < prev)
		{
			mlx_lstclear(&lst, NULL);
			return 1;
		}
		prev = mlx_getzdata(lstcpy);
		lstcpy = lstcpy->next;
	}
	mlx_lstclear(&lst, NULL);
	return 0;
}

int main() {
	if (testpositive() == 1)
		return 1;
	if (testnegative() == 1)
		return 1;
	if (testposneg() == 1)
		return 1;
	return 0;
}