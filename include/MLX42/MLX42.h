/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MLX42.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 00:33:01 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/21 18:28:51 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * An OpenGL graphics library based on the idea on what MiniLibX
 * provides. Just quite a bit better, in terms of norme and code quality.
 * 
 * Additionally with glfw its cross-platform, unlike MiniLibX.
 * 
 * As for the few void* present in some structs and functions and 
 * why MLX is split into two different headers, so to speak, 
 * is mainly for abstraction. Most users won't have a need for the inner 
 * workings of MLX (shaders, ...) and it also helps keep MLX nice and tidy.
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
 * An image with an individual buffer that can be rendered.
 * 
 * @param width The width.
 * @param height The height.
 * @param pixels The literal pixel data.
 * @param context Abstracted data.
 */
typedef struct s_mlx_image
{
	int32_t	width;
	int32_t	height;
	uint8_t	*pixels;
	void	*context;
}	t_mlx_image;

/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param hooks List of all the current hooks.
 * @param images List of all the current images.
 * @param context Abstracted opengl data.
 * @param width The width.
 * @param height The height.
 * @param pixels The literal pixel data.
 */
typedef struct s_mlx
{
	void		*window;
	void		*hooks;
	void		*images;
	void		*context;
	int32_t		width;
	int32_t		height;
	uint8_t		*pixels;
	double		delta_time;
}	t_mlx;

/**
 * Callback function used to handle scrolling.
 * 
 * @param[in] x The mouse x delta.
 * @param[in] y The mouse y delta.
 * @param[in] param The parameter to pass onto the function.
 */
typedef void (*	t_MLXscrollfun)(double xdelta, double ydelta, void *param);

//= Generic Functions =//

/**
 * Initilizes a new MLX42 Instance.
 * 
 * @param[in] Width The width of the window.
 * @param[in] Height The height of the window.
 * @param[in] Title The title of the window.
 * @param[in] Resize Enable window resizing.
 * @returns Ptr to the MLX handle.
 */
t_mlx	*mlx_init(int32_t Width, int32_t Height, const char *Title, \
bool Resize);

/**
 * Tells MLX that it should stop rendering and quit the main loop.
 * Make sure to call terminate after calling this function.
 * 
 * @param[in] mlx The MLX instance handle.
 */
void	mlx_quit(t_mlx *mlx);

/**
 * The program loop, this will cause MLX to continously render
 * and output its content. Can be halted with mlx_quit.
 * 
 * @param[in] mlx The MLX instance handle.
 */
void	mlx_loop(t_mlx *mlx);

/**
 * Adds a function hook to the main loop. Aka, executes a function per frame.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] f The function.
 * @param[in] param The parameter to pass onto the function.
 * @returns Wether the hook was added successfuly. 
 */
bool	mlx_loop_hook(t_mlx *mlx, void (*f)(void *), void *param);

/**
 * Terminates MLX and cleans up any of its used resources.
 * 
 * @param[in] mlx The MLX instance handle.
 */
void	mlx_terminate(t_mlx *mlx);

//= Window/Monitor Functions

/**
 * This function brings the specified window to front and sets input focus.
 * 
 * Do not use this function to steal focus from other applications unless
 * you are certain that is what the user wants.  Focus stealing can be
 * extremely disruptive.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] request Request focus instead of forcing it.
 */
void	mlx_focus(t_mlx *mlx, bool request);

/**
 * Gets the size of the specified monitor.
 * 
 * @param[in] index Normally 0, incase of multiple windows, can be specified
 * @param[in] width The width of the window.
 * @param[in] height The height of the window.
 */
void	mlx_get_monitor_size(int32_t index, int32_t *width, int32_t *height);

/**
 * Sets the windows position.
 * 
 *  Do not use this function to move an already visible window unless you
 *  have very good reasons for doing so, as it will confuse and annoy the user.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] xpos The x position.
 * @param[in] ypos The y position.
 */
void	mlx_set_window_pos(t_mlx *mlx, int32_t xpos, int32_t ypos);

/**
 * Gets the windows position.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] xpos The x position.
 * @param[in] ypos The y position.
 */
void	mlx_get_window_pos(t_mlx *mlx, int32_t *xpos, int32_t *ypos);

//= Pixel Functions =//

/**
 * Sets / puts a pixel onto the screen using 
 * 
 * @param[in] MLX The MLX instance handle.
 * @param[in] X The X coordinate position.
 * @param[in] Y The Y coordinate position.
 * @param[in] Color The RGBA8 Color value.
 */
void	mlx_putpixel(t_mlx *MLX, int32_t X, int32_t Y, int32_t Color);

//= Input Functions =//

/**
 * Returns true or false if the key is down or not.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] key The keycode to check, use MLX_KEY_... to specify!
 * @returns True or false if the key is down or not.
 */
bool	mlx_is_key_down(t_mlx *mlx, t_keys key);

/**
 * Checks whether a mouse button is pressed or not.
 * 
 * @param[in] mlx The MLX instance handle. 
 * @param[in] key A specific mouse key. e.g MLX_MOUSE_BUTTON_0
 * @returns True or false if the mouse key is down or not.
 */
bool	mlx_is_mouse_down(t_mlx *mlx, t_mouse_key key);

/**
 * Returns the current, relative, mouse cursor position on the window, starting
 * from the top left corner.
 * 
 * Negative values or values greater than window width or height 
 * indicate that it is outside the window.
 * 
 * @param[in] mlx The MLX instance handle. 
 * @param[in] pos_out The position.
 */
void	mlx_get_mouse_pos(t_mlx *mlx, int32_t *x_out, int32_t *y_out);

/**
 * Sets the mouse position.
 * 
 * @param[in] mlx The MLX instance handle. 
 * @param[in] pos The position.
 */
void	mlx_set_mouse_pos(t_mlx *mlx, int32_t x, int32_t y);

/**
 * This function sets the scroll callback, which is called when a scrolling 
 * device is used, such as a mouse wheel.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The scroll wheel callback.
 */
void	mlx_scroll_hook(t_mlx *mlx, t_MLXscrollfun func, void *param);

//= Cursor Functions =//

/**
 * Defines the state for the cursor, which can be:
 * - Normal
 * - Hidden
 * - Disabled
 * 
 * @param[in] mlx The MLX instance handle. 
 * @param[in] mode A specified mouse mode.
 */
void	mlx_set_cursor_mode(t_mlx *mlx, t_mouse_mode mode);

/**
 * Allows for the creation of custom cursors with a given
 * XPM image.
 * 
 * Use mlx_set_cursor to select the specific cursor.
 * Cursors are destroyed at mlx_terminate().
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] image The XPM image to use as cursor.
 * @returns The cursor pointer.
 */
void	*mlx_create_cursor(t_mlx *mlx, t_xpm *image);

/**
 * Sets the current cursor to the given custom cursor.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] cursor The cursor to display.
 */
void	mlx_set_cursor(t_mlx *mlx, void *cursor);

/**
 * TODO: NOT WORKING!
 * 
 * Loads an XPM42 image from the given file path.
 * 
 * @param[in] path The file path to the XPM image.
 * @returns The XPM image struct containing its information.
 */
t_xpm	*mlx_load_xpm42(const char *path);

/**
 * Creates and allocates a new image buffer.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] width The desired width of the image.
 * @param[in] height The desired height of the image.
 * @return Pointer to the image buffer, if it failed to allocate then NULL.
 */
t_mlx_image	*mlx_new_image(t_mlx *mlx, uint16_t width, uint16_t height);

void	mlx_draw_image(t_mlx *mlx, t_mlx_image *img, uint16_t x, uint16_t y);

//void	mlx_draw_xpm(t_mlx *mlx, t_xpm *xpm, int32_t X, int32_t Y);

#endif