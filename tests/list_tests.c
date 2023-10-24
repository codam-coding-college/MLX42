#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../include/MLX42/MLX42.h"
#include "../include/MLX42/MLX42_Int.h"

void mlx_lstdelone(mlx_list_t* lst, void (*del)(void *))
{
	if (del != NULL)
		del(lst->content);
	free(lst);
}

bool compare(void *src, void *dst)
{
	return (!strncmp((char *)src, (char *)dst, strlen((char *)dst) + 1));
}

void printlist(int fd, mlx_list_t *lst)
{
	while (lst)
	{
		(void)dprintf(fd, "%s\n", (char *)lst->content);
		lst = lst->next;
	}
}

int test_content(int fd, char *expected, int length)
{
	char buf[201];
	(void)read(fd, buf, length);
	buf[length] = '\0';
	return (strncmp(buf, expected, length));
}

int main()
{
	int tube[2];
	(void)pipe(tube); // 0 read, 1 write
	mlx_list_t *lst = NULL;
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("Hello")));
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("again")));
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("does")));
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("")));
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("this")));
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("work")));
	printlist(tube[1], lst);
	(void)close(tube[1]);
	if (test_content(tube[0], "Hello\nagain\ndoes\n\nthis\nwork\n", 28) != 0)
		return 1;
	(void)close(tube[0]);
	mlx_lstclear(&lst, &free);
	if (lst)
		return 1;
	(void)pipe(tube);
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("Hello")));
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("again")));
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("does")));
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("")));
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("this")));
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("work")));
	mlx_lstdelone(mlx_lstremove(&lst, "again", &compare), &free);
	printlist(tube[1], lst);
	(void)close(tube[1]);
	if (test_content(tube[0], "Hello\ndoes\n\nthis\nwork\n", 22) != 0)
		return 1;
	(void)close(tube[0]);
	(void)pipe(tube);
	printlist(tube[1], mlx_lstlast(lst));
	if (test_content(tube[0], "work\n", 5) != 0)
		return 1;
	if (mlx_lstsize(lst) != 5)
		return 1;
	mlx_lstclear(&lst, &free);
	if (lst)
		return 1;
	(void)pipe(tube);
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("Hello")));
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("again")));
	mlx_lstadd_front(&lst, mlx_lstnew(strdup("does")));
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("")));
	mlx_lstadd_front(&lst, mlx_lstnew(strdup("this")));
	mlx_lstadd_back(&lst, mlx_lstnew(strdup("work")));
	printlist(tube[1], lst);
	(void)close(tube[1]);
	if (test_content(tube[0], "this\ndoes\nHello\nagain\n\nwork\n", 28) != 0)
		return 1;
	(void)close(tube[0]);
	if (mlx_lstsize(lst) != 6)
		return 1;
	mlx_lstclear(&lst, &free);
	if (lst)
		return 1;
	return 0;
}