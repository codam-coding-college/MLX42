/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MLX42_Int.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/27 23:55:34 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/15 17:42:41 by w2wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX42_INT_H
# define MLX42_INT_H
# include "MLX42/MLX42.h"
# include "glad/glad.h"
# include "KHR/khrplatform.h"
# if defined(__APPLE__)
#  define GL_SILENCE_DEPRECATION
#  define IS_APPLE 1
# else
#  define IS_APPLE 0
# endif
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include <memory.h>
# include <stdio.h>
# include <limits.h>
# include <ctype.h>
# ifndef VERTEX_PATH
#  define VERTEX_PATH "shaders/default.vert"
# endif
# ifndef FRAGMENT_PATH
#  define FRAGMENT_PATH "shaders/default.frag"
# endif
# define MLX_ERROR "MLX42 Error:"
# define MLX_INVALID_FILE_EXT "Invalid file extension!"
# define MLX_INVALID_FILE "Failed to read file!"
# define MLX_SHADER_FAILURE "Shader failure!"
# define MLX_RENDER_FAILURE "Failed to initialize Renderer!"
# define MLX_MEMORY_FAIL "Failed to allocate enough memory!"
# define GLFW_INIT_FAILURE "Failed to initialize GLFW!"
# define GLFW_WIN_FAILURE "Failed to create GLFW Window!"
# define GLFW_GLAD_FAILURE "Failed to initialize GLAD!"

//= Types =//

// OpenGL variables.
typedef struct s_mlx_ctx
{
	uint32_t	shaderprogram;
	uint32_t	texture;
	uint32_t	vao;
	uint32_t	vbo;
	uint32_t	ebo;
}	t_mlx_ctx;

// Struct witholding a simple hook function with a param.
typedef struct s_mlx_hook
{
	void	*param;
	void	(*func)(void*);
}	t_mlx_hook;

// Linked List structure.
typedef struct s_mlx_list
{
	void				*content;
	struct s_mlx_list	*next;
}	t_mlx_list;

typedef struct s_mlx_line
{
	char	*buff;
	size_t	len;
}	t_mlx_line;

//= Functions =//

int32_t		mlx_lstsize(t_mlx_list *lst);
void		mlx_lstclear(t_mlx_list **lst, void (*del)(void*));
t_mlx_list	*mlx_lstnew(void *content);
t_mlx_list	*mlx_lstlast(t_mlx_list *lst);
void		mlx_lstadd_back(t_mlx_list **lst, t_mlx_list *new);

bool		mlx_error(const char *error);

bool		mlx_compile_shader(const char *Path, int32_t Type, uint32_t *out);
bool		mlx_init_shaders(t_mlx *mlx, uint32_t *shaders);
char		*mlx_readfile(const char *FilePath);
int32_t		mlx_rgba_to_mono(int32_t color);
int32_t		mlx_atoi_base(const char *str, int32_t base);
#endif
