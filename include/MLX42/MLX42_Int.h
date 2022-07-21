/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MLX42_Int.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/27 23:55:34 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/07/21 10:46:43 by sbos          ########   odam.nl         */
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
#  include <windows.h>
# else
#  include <err.h>
# endif
# include <ctype.h> /* isspace, isprint, ... */
# include <string.h> /* strlen, memmove, ... */
# include <stdarg.h> /* va_arg, va_end, ... */
# include <assert.h> /* assert, static_assert, ... */
# ifndef MLX_SWAP_INTERVAL
#  define MLX_SWAP_INTERVAL 1
# endif
# ifndef MLX_BATCH_SIZE
#  define MLX_BATCH_SIZE 12000
# endif
# define BPP sizeof(int32_t) /* Only support RGBA */
# define GETLINE_BUFF 1280
# define MLX_MAX_STRING 512 /* Arbitrary string limit */
# define MLX_ASSERT(cond, msg) assert(cond && msg);
# define MLX_NONNULL(var) MLX_ASSERT(var, "Value can't be null"); /* Assert instead of attribute */

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

extern const char* vert_shader;
extern const char* frag_shader;

// Flag to indicate if the render queue has to be sorted.
extern bool sort_queue;

// Settings array, use the enum 'key' to get the value.
extern int32_t mlx_settings[MLX_SETTINGS_MAX];

//= Types =//

// A single vertex, identical to the layout in the shader.
typedef struct vertex
{
	float	x;
	float	y;
	float	z;
	float	u;
	float	v;
	int8_t	tex;
}	vertex_t;

// Layout for linked list.
typedef struct mlx_list
{
	void*				content;
	struct mlx_list*	next;
	struct mlx_list*	prev;
}	mlx_list_t;

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

typedef struct mlx_srcoll
{
	void*			param;
	mlx_scrollfunc	func;
}	mlx_scroll_t;

typedef struct mlx_mouse
{
	void*			param;
	mlx_mousefunc	func;
}	mlx_mouse_t;

typedef struct mlx_cursor
{
	void*			param;
	mlx_cursorfunc	func;
}	mlx_cursor_t;

typedef struct mlx_close
{
	void*			param;
	mlx_closefunc	func;
}	mlx_close_t;

typedef struct mlx_resize
{
	void*			param;
	mlx_resizefunc	func;
}	mlx_resize_t;

typedef struct mlx_key
{
	void*			param;
	mlx_keyfunc		func;
}	mlx_key_t;

typedef struct mlx_hook
{
	void*	param;
	void	(*func)(void*);
}	mlx_hook_t;

//= Rendering =//
/**
 * For rendering we need to store most of OpenGLs stuff
 * such as the vertex array object, vertex buffer object &
 * the shader program. As well as hooks and the zdepth level.
 *
 * Additionally we represent draw calls with a linked list
 * queue that point to the image and the index of which instance.
 * Again, instances only carry xyz data, so coupled with the image it
 * lets us know where to draw a copy of the image.
 *
 * Texture contexts are kept in a struct alongside the capacity
 * of the array of instances, since the array is realloced like a vector.
 */

// MLX instance context.
typedef struct mlx_ctx
{
	GLuint			vao;
	GLuint			vbo;
	GLuint			shaderprogram;

	uint32_t		initialWidth;
	uint32_t		initialHeight;

	mlx_list_t*		hooks;
	mlx_list_t*		images;
	mlx_list_t*		render_queue;

	mlx_scroll_t	scroll_hook;
	mlx_mouse_t		mouse_hook;
	mlx_cursor_t	cursor_hook;
	mlx_key_t		key_hook;
	mlx_resize_t	resize_hook;
	mlx_close_t		close_hook;

	int32_t			zdepth;
	int32_t			bound_textures[16];
	int32_t			batch_size;
	vertex_t		batch_vertices[MLX_BATCH_SIZE];
}	mlx_ctx_t;

// Draw call queue entry.
typedef struct draw_queue
{
	mlx_image_t*	image;
	int32_t			instanceid;
}	draw_queue_t;

// Image context.
typedef struct mlx_image_ctx
{
	GLuint	texture;
	size_t	instances_capacity;
}	mlx_image_ctx_t;

//= Functions =//
/**
 * All sorts of internal functions shared in the library that
 * should not be accessible to the user! No touch!
 */

//= Linked List Functions =//

mlx_list_t* mlx_lstnew(void* content);
mlx_list_t* mlx_lstlast(mlx_list_t* lst);
int32_t mlx_lstsize(mlx_list_t* lst);
void mlx_lstclear(mlx_list_t** lst, void (*del)(void*));
void mlx_lstadd_back(mlx_list_t** lst, mlx_list_t* new);
void mlx_lstadd_front(mlx_list_t** lst, mlx_list_t* new);
mlx_list_t* mlx_lstremove(mlx_list_t** lst, void* value, bool (*comp)(void*, void*));
void mlx_sort_renderqueue(mlx_list_t** lst);

//= Misc functions =//

bool mlx_equal_image(void* lstcontent, void* value);
bool mlx_equal_inst(void* lstcontent, void* value);
void mlx_draw_pixel(uint8_t* pixel, uint32_t color);

//= Error/log Handling Functions =//

bool mlx_error(mlx_errno_t val);
bool mlx_freen(int32_t count, ...);

//= OpenGL Functions =//

void mlx_update_matrix(const mlx_t* mlx, int32_t width, int32_t height);
void mlx_draw_instance(mlx_ctx_t* mlx, mlx_image_t* img, mlx_instance_t* instance);
void mlx_flush_batch(mlx_ctx_t* mlx);

// Utils Functions =//

bool mlx_getline(char** out, size_t* out_size, FILE* file);
uint32_t mlx_rgba_to_mono(uint32_t color);
int32_t mlx_atoi_base(const char* str, int32_t base);
uint64_t mlx_fnv_hash(char* str, size_t len);
#endif
