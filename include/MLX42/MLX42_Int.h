/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MLX42_Int.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/27 23:55:34 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 17:55:09 by lde-la-h      ########   odam.nl         */
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
#  include <malloc.h> /* alloca */
# endif
# include <ctype.h> /* isspace, isprint, ... */
# include <string.h> /* strlen, memmove, ... */
# include <stdarg.h> /* va_arg, va_end, ... */
# ifndef MLX_SWAP_INTERVAL
#  define MLX_SWAP_INTERVAL 1
# endif

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

// A single vertex, identical to the layout in the shader.
typedef struct s_vert
{
	float	x;
	float	y;
	float	z;
	float	u;
	float	v;
}	t_vert;

// Layout for linked list.
typedef struct s_mlx_list
{
	void				*content;
	struct s_mlx_list	*next;
	struct s_mlx_list	*prev;
}	t_mlx_list;

//= Hook structs =//
/**
 * There are 2 types of hooks, special and generics.
 * 
 * Specials: Are specific callback functions to a specific action
 * such as window resizing or key presses. These are attached to the
 * callbacks of glfw. In case MLX itself needs the callback we call
 * the specials in that callback since there can only ever be a single
 * callback.
 * 
 * Generics: Generics are MLX42 specific hooks and can have multiple
 * hooks at the same time, these are executed every frame and can be
 * used as an alternative for key presses or animations for instance.
 * 
 * NOTE: Hooks could be achieved with va_args to have any amount
 * of args sized functor but we can't/don't want to let the user
 * deal with va_args and having to look up what args are what, etc...
 * 
 * We want to keep it straight forward with functors already describing
 * what params they have.
 */

typedef struct s_mlx_srcoll
{
	void				*param;
	t_mlx_scrollfunc	func;
}	t_mlx_scroll;

typedef struct s_mlx_close
{
	void				*param;
	t_mlx_closefunc		func;
}	t_mlx_close;

typedef struct s_mlx_resize
{
	void				*param;
	t_mlx_resizefunc	func;
}	t_mlx_resize;

typedef struct s_mlx_key
{
	void				*param;
	t_mlx_keyfunc		func;
}	t_mlx_key;

typedef struct s_mlx_hook
{
	void	*param;
	void	(*func)(void*);
}	t_mlx_hook;

//= Rendering =//
/**
 * For rendering we need to store most of OpenGLs stuff
 * such as the vertex array object, vertex buffer object &
 * the shader program. As well as hooks and the zdepth level.
 * 
 * Additionally we represent draw calls with a linked list
 * queue that point to the image and the index of which instance.
 * Again, instances only carry xyz data so coupled with the image it
 * lets us know which image and where to draw a copy.
 * 
 * Texture contexts are kept in a struct purely for convience of
 * expanding the variables in potential later updates. As well as
 * having had more variables before now just one.
 */

// MLX instance context.
typedef struct s_mlx_ctx
{
	GLuint				vao;
	GLuint				vbo;
	GLuint				shaderprogram;
	t_mlx_list			*hooks;
	t_mlx_list			*images;
	t_mlx_list			*render_queue;
	t_mlx_scroll		scroll_hook;
	t_mlx_key			key_hook;
	t_mlx_resize		resize_hook;
	t_mlx_close			close_hook;
	int32_t				zdepth;
}	t_mlx_ctx;

// Draw call queue entry.
typedef struct s_draw_queue
{
	t_mlx_image	*image;
	int32_t		instanceid;
}	t_draw_queue;

// Image context.
typedef struct s_mlx_image_ctx
{
	GLuint	texture;
}	t_mlx_image_ctx;

//= Functions =//
/**
 * All sorts of internal functions shared in the library that
 * should not be accessible to the user! No touch!
 */

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

void		mlx_xpm_putpixel(t_xpm *xpm, int32_t x, int32_t y, uint32_t color);
bool		mlx_equal_image(void *lstcontent, void *value);
bool		mlx_equal_inst(void *lstcontent, void *value);
bool		mlx_insert_xpm_entry(t_xpm *xpm, char *line, uint32_t *ctable, \
size_t s);
uint32_t	mlx_grab_xpm_pixel(char *pixelstart, uint32_t *ctable, \
t_xpm *xpm, size_t s);

//= Error/log Handling Functions =//

bool		mlx_error(t_mlx_errno val);
bool		mlx_freen(int32_t count, ...);

//= OpenGL Functions =//

void		mlx_on_resize(GLFWwindow *window, int32_t width, int32_t height);
bool		mlx_init_shaders(t_mlx *mlx, uint32_t *shaders);
bool		mlx_compile_shader(const char *code, int32_t type, uint32_t *out);
void		mlx_draw_instance(t_mlx_image *img, t_mlx_inst *instance);

// Utils Functions =//

int32_t		mlx_rgba_to_mono(int32_t color);
int32_t		mlx_atoi_base(const char *str, int32_t base);
uint64_t	mlx_fnv_hash(char *str, size_t len);
bool		mlx_parse_font_atlas(t_mlx *mlx);
#endif
