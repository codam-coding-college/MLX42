/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MLX42.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 00:33:01 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/17 13:27:35 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * OpenGL graphics library based on the idea on what MiniLibX
 * provides. Just quite a bit better, in terms of norme and code quality.
 * 
 * Additionally with glfw its cross-platform, unlike before.
 * 
 * As for the few void* present in some structs and why MLX is split into
 * two different headers, so to speak, is mainly for abstraction. Most users
 * won't have a need for the inner workings of MLX (shaders, ...) and it also
 * helps keep MLX nice and tidy.
 * 
 * @note Useful stuff for later:
 * https://bit.ly/3qQof6q
 * __attribute__ ((deprecated));
 * 
 * Written in accordance with norminette 3.3.51.
 */

#ifndef MLX42_H
# define MLX42_H
# include <stdint.h>
# include <stdbool.h>
# include "MLX42_Keys.h"

/**
 * Struct containing data regarding an XPM image.
 * 
 * @param width The width.
 * @param height The height.
 * @param pixels The literal pixel data.
 * @param color_count The amount of colors available.
 * @param mode The color mode, either (c)olor or (m)onochrome.
 */
typedef struct s_xpm
{
	int32_t		width;
	int32_t		height;
	uint8_t		*pixels;
	int32_t		color_count;
	char		mode;
}	t_xpm;

/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param hooks List of all the current hooks.
 * @param width The width.
 * @param height The height.
 * @param pixels The literal pixel data.
 * @param context Abstracted opengl data.
 */
typedef struct s_mlx
{
	void		*window;
	void		*hooks;
	int32_t		width;
	int32_t		height;
	uint8_t		*pixels;
	void		*context;
}	t_mlx;

/**
 * Initilizes a new MLX42 Instance.
 * 
 * @param Width The width of the window.
 * @param Height The height of the window.
 * @param Title The title of the window.
 * @param Resize EXPERIMENTAL Enable window resizing.
 * @return Ptr to the MLX handle.
 */
t_mlx	*mlx_init(int32_t Width, int32_t Height, const char *Title, \
bool Resize);

/**
 * The program loop, this will cause MLX to continously render
 * and output its content. Can be halted with mlx_quit.
 * 
 * @param mlx The MLX instance handle.
 */
void	mlx_loop(t_mlx *mlx);

/**
 * Adds a function hook to the main loop. Aka, executes a function per frame.
 * 
 * @param mlx The MLX instance handle.
 * @param f The function.
 * @param param The parameter to pass onto the function.
 * @return Wether the hook was added successfuly. 
 */
bool	mlx_loop_hook(t_mlx *mlx, void (*f)(void *), void *param);

/**
 * Terminates MLX and cleans up any of its used resources.
 * 
 * @param mlx The MLX instance handle.
 */
void	mlx_terminate(t_mlx *mlx);

/**
 * Sets / puts a pixel onto the screen using 
 * 
 * @param MLX The MLX instance handle.
 * @param X The X coordinate position.
 * @param Y The Y coordinate position.
 * @param Color The RGBA8 Color value.
 */
void	mlx_putpixel(t_mlx *MLX, int32_t X, int32_t Y, int32_t Color);

/**
 * Returns true or false if the key is down or not.
 * 
 * @param mlx The MLX instance handle.
 * @param key The keycode to check, use MLX_KEY_... to specify!
 * @return True or false if the key is down or not.
 */
bool	mlx_is_key_down(t_mlx *mlx, t_keys key);

/**
 * Defines the state for the cursor, which can be:
 * - Normal
 * - Hidden
 * - Disabled
 * 
 * @param mlx The MLX instance handle. 
 * @param mode A specified mouse mode.
 */
void	mlx_set_cursor_mode(t_mlx *mlx, t_mouse_mode mode);

/**
 * Checks whether a mouse button is pressed or not.
 * 
 * @param mlx The MLX instance handle. 
 * @param key A specific mouse key.
 * @return True or false if the mouse key is down or not.
 */
bool	mlx_is_mouse_down(t_mlx *mlx, t_mouse_key key);

/**
 * Returns the current, relative, mouse cursor position on the window, starting
 * from the top left corner.
 * 
 * Negative values or values greater than window width or height 
 * indicate that it is outside the window.
 * 
 * @param mlx The MLX instance handle. 
 * @param pos_out The position.
 */
void	mlx_get_mouse_pos(t_mlx *mlx, int32_t *x_out, int32_t *y_out);

/**
 * Sets the mouse position.
 * 
 * @param mlx The MLX instance handle. 
 * @param pos The position.
 */
void	mlx_set_mouse_pos(t_mlx *mlx, int32_t x, int32_t y);

/**
 * Tells MLX that it should stop rendering and quit the main loop.
 * Make sure to call terminate after calling this function.
 * 
 * @param mlx The MLX instance handle.
 */
void	mlx_quit(t_mlx *mlx);

#endif