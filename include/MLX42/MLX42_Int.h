/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MLX42_Int.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/27 23:55:34 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/01 16:35:32 by W2Wizard      ########   odam.nl         */
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
#  include <GLFW/glfw3.h>
# else
#  define IS_APPLE 0
#  include "GLFW/glfw3.h"
# endif
# include <stdlib.h>
# include <memory.h>
# include <stdio.h>
# ifndef VERTEX_PATH
#  define VERTEX_PATH "shaders/default.vert"
# endif
# ifndef FRAGMENT_PATH
#  define FRAGMENT_PATH "shaders/default.frag"
# endif
# define MLX_ERROR "MLX42 Error: "
# define MLX_SHADER_FAILURE "Shader failure!\n"
# define MLX_RENDER_FAILURE "Failed to initialize Renderer\n"
# define GLFW_INIT_FAILURE "Failed to initialize GLFW\n"
# define GLFW_WIN_FAILURE "Failed to create GLFW Window\n"
# define GLFW_GLAD_FAILURE "Failed to initialize GLAD\n"

//= Types =//

// Same as MLX images, renamed to canvas to be more appropriate.
typedef struct s_mlx_canvas
{
	int32_t	width;
	int32_t	height;
	int32_t	*pixels;
	GLfloat	vertices[6];
}	t_mlx_canvas;

typedef struct s_mlx_img_ctx
{
	GLuint			texture;
	GLuint			vbuffer;
	t_mlx_canvas	*img;
}	t_mlx_img_ctx;

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

//= Functions =//

int32_t		mlx_lstsize(t_mlx_list *lst);
void		mlx_lstclear(t_mlx_list **lst, void (*del)(void*));
t_mlx_list	*mlx_lstnew(void *content);
t_mlx_list	*mlx_lstlast(t_mlx_list *lst);
void		mlx_lstadd_back(t_mlx_list **lst, t_mlx_list *new);

bool		mlx_error(const char *error);

bool		mlx_compile_shader(const char *Path, int32_t Type, uint32_t *out);
bool		mlx_init_shaders(t_MLX *mlx, uint32_t *shaders);
void		mlx_argb_to_float(int32_t color, float out[4]);
#endif
