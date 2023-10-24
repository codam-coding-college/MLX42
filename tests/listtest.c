#include "../include/MLX42/MLX42_Int.h"

// Retrieve Z value from queue.
static int32_t mlx_getzdata(mlx_list_t* entry)
{
	const draw_queue_t* queue = entry->content;

	return (queue->image->instances[queue->instanceid].z);
}

int main() {
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
	int res[6];
	i = 0;
	while (lst)
	{
		res[i] = mlx_getzdata(lst);
		printf("%i\n", res[i]);
		++i;
		lst = lst->next;
	}
}