/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MLX42_Int.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/27 23:55:34 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/21 11:10:21 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX42_INT_H
# define MLX42_INT_H
# define LODEPNG_NO_COMPILE_ALLOCATORS
# include "MLX42/MLX42.h"
# include "lodepng/lodepng.h"
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
# if defined(__linux__)
#  include <linux/limits.h>
# else
#  include <limits.h>
# endif
# if defined(_WIN32)
#  include <malloc.h>
# endif
# include <ctype.h>
# include <string.h>
# include <stdarg.h>
# ifndef MLX_SWAP_INTERVAL
#  define MLX_SWAP_INTERVAL 1
# endif
# define MLX_INVALID_FILE_EXT "Invalid file extension!"
# define MLX_INVALID_FILE "Failed to read file!"
# define MLX_INVALID_ARG "Invalid argument provided!"
# define MLX_NULL_ARG "NULL argument exception!"
# define MLX_SHADER_FAILURE "Shader failure!"
# define MLX_RENDER_FAILURE "Failed to initialize Renderer!"
# define MLX_MEMORY_FAIL "Failed to allocate enough memory!"
# define MLX_XPM_FAILURE "Failed to read XPM42 file!"
# define GLFW_INIT_FAILURE "Failed to initialize GLFW!"
# define GLFW_WIN_FAILURE "Failed to create GLFW Window!"
# define GLFW_GLAD_FAILURE "Failed to initialize GLAD!"
// TODO: Switch to error codes instead.

/**
 * The shader code is extracted from the shader files
 * and converted into a .c file as a single string at 
 * compile time. This keeps shader files external but 
 * still integrated into the program letting you use 
 * the executable anywhere without having to take the 
 * shaders with you.
 * 
 * Most modern frameworks like .NET do this by having resource files
 * instead.
 * 
 * See: https://bit.ly/3LJYG0r
 */

extern const char	*g_vert_shader;
extern const char	*g_frag_shader;

//= Types =//

/**
 * Various log types to give different verbose types of feedback.
 * 
 * @param MLX_INFO Info is for simple feedback
 * @param MLX_WARNING Something happened that shouldn't have.
 * @param MLX_INFO Critical error.
 */
typedef enum e_logtype
{
	MLX_INFO,
	MLX_WARNING,
	MLX_ERROR,
}	t_logtype;

// A single vertex, identical to the layout in the shader.
typedef struct s_vert
{
	float	x;
	float	y;
	float	z;
	float	u;
	float	v;
}	t_vert;

// Hook layout used to add generic loop hooks.
typedef struct s_mlx_hook
{
	void	*param;
	void	(*func)(void*);
}	t_mlx_hook;

// Layout for linked list.
typedef struct s_mlx_list
{
	void				*content;
	struct s_mlx_list	*next;
	struct s_mlx_list	*prev;
}	t_mlx_list;

// To maintain the drawing order we add every instance to a queue.
typedef struct s_draw_queue
{
	t_mlx_image	*image;
	int32_t		instanceid;
}	t_draw_queue;

// MLX Instance handle context used for OpenGL stuff.
typedef struct s_mlx_ctx
{
	GLuint				vao;
	GLuint				vbo;
	GLuint				shaderprogram;
	t_mlx_list			*hooks;
	t_mlx_list			*images;
	t_mlx_list			*render_queue;
	t_mlx_scrollfunc	scroll_hook;
	t_mlx_keyfunc		key_hook;
	t_mlx_resizefunc	resize_hook;
	t_mlx_closefunc		close_hook;
	int32_t				zdepth;
}	t_mlx_ctx;

// Additional OpenGL information for images/textures.
typedef struct s_mlx_image_ctx
{
	t_vert	vertices[6];
	GLuint	texture;
}	t_mlx_image_ctx;

//= Linked List Functions =//

t_mlx_list	*mlx_lstnew(void *content);
t_mlx_list	*mlx_lstlast(t_mlx_list *lst);
int32_t		mlx_lstsize(t_mlx_list *lst);
void		mlx_lstclear(t_mlx_list **lst, void (*del)(void*));
void		mlx_lstadd_back(t_mlx_list **lst, t_mlx_list *new);
void		mlx_lstadd_front(t_mlx_list **lst, t_mlx_list *new);
t_mlx_list	*mlx_lstremove(t_mlx_list **lst, void *value, \
bool (*comp)(void *, void*));

//= Misc functions =//

bool		mlx_equal_image(void *lstcontent, void *value);
bool		mlx_equal_inst(void *lstcontent, void *value);
void		mlx_xpm_putpixel(t_xpm *xpm, int32_t x, int32_t y, uint32_t color);
bool		mlx_insert_xpm_entry(t_xpm *xpm, char *line, uint32_t *ctable, \
size_t s);
uint32_t	mlx_grab_xpm_pixel(char *pixelstart, uint32_t *ctable, \
t_xpm *xpm, size_t s);

//= Error/log Handling Functions =//

bool		mlx_log(const t_logtype type, const char *msg);
bool		mlx_freen(int32_t count, ...);

//= IO Functions =//

char		*mlx_readfile(const char *FilePath);

//= OpenGL Functions =//

bool		mlx_init_shaders(t_mlx *mlx, uint32_t *shaders);
bool		mlx_compile_shader(const char *code, int32_t type, uint32_t *out);
void		mlx_draw_instance(t_mlx *mlx, t_mlx_image *img, \
t_mlx_instance *instance);

// Utils Functions =//

int32_t		mlx_rgba_to_mono(int32_t color);
int32_t		mlx_atoi_base(const char *str, int32_t base);
uint64_t	mlx_fnv_hash(char *str, size_t len);
#endif
