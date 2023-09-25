/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MLX42.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <main@w2wizard.dev>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:29:06 by W2Wizard      #+#    #+#                 */
/*   Updated: 2023/03/30 16:23:19 by ntamayo-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 *
 * MLX42 is a cross-platform low level and simple cross-platform graphics
 * library written in C and uses OpenGL and GLFW for it's underlying windowing
 * and rendering system.
 * 
 * It's a much more up-to-date alternative to the miniLibX which has been
 * extensively proven to be fragile, unmaintained, deprecated and just
 * plain painfully bad to work with. Also it's code quality is dubious.
 * 
 * Some structs contain potential void* which are to be ignored as they 
 * simply represent points of abstraction to the hidden internal header.
 * This abstraction is crucial as the whole point of this lib so to hide
 * all the bells and whistles in the "engine". Most user's have no need
 * for the inner workings eitherway (shaders, vertex buffer, ...).  
 */

#ifndef MLX42_H
# define MLX42_H
# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# ifdef __cplusplus
extern "C" {
# endif

//= Types =//

/**
 * The input key codes are copied straight from GLFW.
 * Any new entries should have the exact same values as defined in the glfw3.h.
 */

/**
 * A key action such as pressing or releasing a key.
 * 
 * @param RELEASE Execute when the key is being released.
 * @param PRESS Execute when the key is being pressed.
 * @param REPEAT Execute when the key is being held down.
 */
typedef enum action
{
	MLX_RELEASE = 0,
	MLX_PRESS	= 1,
	MLX_REPEAT	= 2,
}	action_t;

/**
 * Key modifiers, such as shift, control or alt.
 * These keys are flags meaning you can combine them to detect
 * key combinations such as CTRL + ALT so CTRL | ALT.
 * 
 * @param SHIFT The shift key.
 * @param CONTROL The control key.
 * @param ALT The alt key.
 * @param SUPERKEY The Superkey such as the Windows Key or Command.
 * @param CAPSLOCK The capslock key.
 * @param NUMLOCK The numlock key.
 */
typedef enum modifier_key
{
	MLX_SHIFT		= 0x0001,
	MLX_CONTROL		= 0x0002,
	MLX_ALT			= 0x0004,
	MLX_SUPERKEY	= 0x0008,
	MLX_CAPSLOCK	= 0x0010,
	MLX_NUMLOCK		= 0x0020,
}	modifier_key_t;

/**
 * The mouse button keycodes.
 * @param LEFT The left mouse button.
 * @param RIGHT The right mouse button.
 * @param MIDDLE The middle mouse button, aka the Scrollwheel.
 */
typedef enum mouse_key
{
	MLX_MOUSE_BUTTON_LEFT	= 0,
	MLX_MOUSE_BUTTON_RIGHT	= 1,
	MLX_MOUSE_BUTTON_MIDDLE	= 2,
}	mouse_key_t;

/**
 * Various mouse/cursor states.
 * @param NORMAL Simple visible default cursor.
 * @param HIDDEN The cursor is not rendered but still functions.
 * @param DISABLED The cursor is not rendered, nor is it functional.
 */
typedef enum mouse_mode
{
	MLX_MOUSE_NORMAL	= 0x00034001,
	MLX_MOUSE_HIDDEN	= 0x00034002,
	MLX_MOUSE_DISABLED	= 0x00034003,
}	mouse_mode_t;

/**
 * Various cursors that are standard.
 * @param ARROW The regular arrow cursor.
 * @param IBEAM The text input I-beam cursor shape.
 * @param CROSSHAIR The crosshair shape cursor.
 * @param HAND The hand shape cursor.
 * @param HRESIZE The horizontal resize arrow shape.
 * @param VRESIZE The vertical resize arrow shape.
 */
typedef enum cursor
{
	MLX_CURSOR_ARROW		= 0x00036001,
	MLX_CURSOR_IBEAM		= 0x00036002,
	MLX_CURSOR_CROSSHAIR	= 0x00036003,
	MLX_CURSOR_HAND			= 0x00036004,
	MLX_CURSOR_HRESIZE		= 0x00036005,
	MLX_CURSOR_VRESIZE		= 0x00036006,
}	cursor_t;

/**
 * All sorts of keyboard keycodes.
 * 
 * KP = Keypad.
 */
typedef enum keys
{
	MLX_KEY_SPACE			= 32,
	MLX_KEY_APOSTROPHE		= 39,
	MLX_KEY_COMMA			= 44,
	MLX_KEY_MINUS			= 45,
	MLX_KEY_PERIOD			= 46,
	MLX_KEY_SLASH			= 47,
	MLX_KEY_0				= 48,
	MLX_KEY_1				= 49,
	MLX_KEY_2				= 50,
	MLX_KEY_3				= 51,
	MLX_KEY_4				= 52,
	MLX_KEY_5				= 53,
	MLX_KEY_6				= 54,
	MLX_KEY_7				= 55,
	MLX_KEY_8				= 56,
	MLX_KEY_9				= 57,
	MLX_KEY_SEMICOLON		= 59,
	MLX_KEY_EQUAL			= 61,
	MLX_KEY_A				= 65,
	MLX_KEY_B				= 66,
	MLX_KEY_C				= 67,
	MLX_KEY_D				= 68,
	MLX_KEY_E				= 69,
	MLX_KEY_F				= 70,
	MLX_KEY_G				= 71,
	MLX_KEY_H				= 72,
	MLX_KEY_I				= 73,
	MLX_KEY_J				= 74,
	MLX_KEY_K				= 75,
	MLX_KEY_L				= 76,
	MLX_KEY_M				= 77,
	MLX_KEY_N				= 78,
	MLX_KEY_O				= 79,
	MLX_KEY_P				= 80,
	MLX_KEY_Q				= 81,
	MLX_KEY_R				= 82,
	MLX_KEY_S				= 83,
	MLX_KEY_T				= 84,
	MLX_KEY_U				= 85,
	MLX_KEY_V				= 86,
	MLX_KEY_W				= 87,
	MLX_KEY_X				= 88,
	MLX_KEY_Y				= 89,
	MLX_KEY_Z				= 90,
	MLX_KEY_LEFT_BRACKET	= 91,
	MLX_KEY_BACKSLASH		= 92,
	MLX_KEY_RIGHT_BRACKET	= 93,
	MLX_KEY_GRAVE_ACCENT	= 96,
	MLX_KEY_ESCAPE			= 256,
	MLX_KEY_ENTER			= 257,
	MLX_KEY_TAB				= 258,
	MLX_KEY_BACKSPACE		= 259,
	MLX_KEY_INSERT			= 260,
	MLX_KEY_DELETE			= 261,
	MLX_KEY_RIGHT			= 262,
	MLX_KEY_LEFT			= 263,
	MLX_KEY_DOWN			= 264,
	MLX_KEY_UP				= 265,
	MLX_KEY_PAGE_UP			= 266,
	MLX_KEY_PAGE_DOWN		= 267,
	MLX_KEY_HOME			= 268,
	MLX_KEY_END				= 269,
	MLX_KEY_CAPS_LOCK		= 280,
	MLX_KEY_SCROLL_LOCK		= 281,
	MLX_KEY_NUM_LOCK		= 282,
	MLX_KEY_PRINT_SCREEN	= 283,
	MLX_KEY_PAUSE			= 284,
	MLX_KEY_F1				= 290,
	MLX_KEY_F2				= 291,
	MLX_KEY_F3				= 292,
	MLX_KEY_F4				= 293,
	MLX_KEY_F5				= 294,
	MLX_KEY_F6				= 295,
	MLX_KEY_F7				= 296,
	MLX_KEY_F8				= 297,
	MLX_KEY_F9				= 298,
	MLX_KEY_F10				= 299,
	MLX_KEY_F11				= 300,
	MLX_KEY_F12				= 301,
	MLX_KEY_F13				= 302,
	MLX_KEY_F14				= 303,
	MLX_KEY_F15				= 304,
	MLX_KEY_F16				= 305,
	MLX_KEY_F17				= 306,
	MLX_KEY_F18				= 307,
	MLX_KEY_F19				= 308,
	MLX_KEY_F20				= 309,
	MLX_KEY_F21				= 310,
	MLX_KEY_F22				= 311,
	MLX_KEY_F23				= 312,
	MLX_KEY_F24				= 313,
	MLX_KEY_F25				= 314,
	MLX_KEY_KP_0			= 320,
	MLX_KEY_KP_1			= 321,
	MLX_KEY_KP_2			= 322,
	MLX_KEY_KP_3			= 323,
	MLX_KEY_KP_4			= 324,
	MLX_KEY_KP_5			= 325,
	MLX_KEY_KP_6			= 326,
	MLX_KEY_KP_7			= 327,
	MLX_KEY_KP_8			= 328,
	MLX_KEY_KP_9			= 329,
	MLX_KEY_KP_DECIMAL		= 330,
	MLX_KEY_KP_DIVIDE		= 331,
	MLX_KEY_KP_MULTIPLY		= 332,
	MLX_KEY_KP_SUBTRACT		= 333,
	MLX_KEY_KP_ADD			= 334,
	MLX_KEY_KP_ENTER		= 335,
	MLX_KEY_KP_EQUAL		= 336,
	MLX_KEY_LEFT_SHIFT		= 340,
	MLX_KEY_LEFT_CONTROL	= 341,
	MLX_KEY_LEFT_ALT		= 342,
	MLX_KEY_LEFT_SUPER		= 343,
	MLX_KEY_RIGHT_SHIFT		= 344,
	MLX_KEY_RIGHT_CONTROL	= 345,
	MLX_KEY_RIGHT_ALT		= 346,
	MLX_KEY_RIGHT_SUPER		= 347,
	MLX_KEY_MENU			= 348,
}	keys_t;

/**
 * Base object for disk loaded textures.
 * It contains rudementary information about the texture.
 * 
 * @param width The width of the texture.
 * @param height The height of the texture.
 * @param pixels The literal pixel data.
 * @param bytes_per_pixel The amount of bytes in a pixel, always 4.
 */
typedef struct mlx_texture
{
	uint32_t	width;
	uint32_t	height;
	uint8_t		bytes_per_pixel;
	uint8_t*	pixels;
}	mlx_texture_t;

/**
 * Struct containing data regarding an XPM image.
 * 
 * @param texture The texture data of the XPM.
 * @param color_count The amount of colors available.
 * @param cpp The amount of characters per pixel.
 * @param mode The color mode, either (c)olor or (m)onochrome.
 */
typedef struct xpm
{
	mlx_texture_t	texture;
	int32_t			color_count;
	int32_t			cpp;
	char			mode;
}	xpm_t;

/**
 * An image instance can be summarized as just a simple
 * x, y & z coordinate.
 * 
 * Coordinates start from the top left of the screen at 0,0 and increase
 * towards the bottom right.
 * 
 * NOTE: To change the z value, use mlx_set_instance_depth!
 * 
 * @param x The x location.
 * @param y The y location.
 * @param z The z depth, controls if the image is on the fore or background.
 * @param enabled If true, the instance is drawn, else it's not.
 */
typedef struct mlx_instance
{
	int32_t	x;
	int32_t	y;
	int32_t	z;
	bool	enabled;
}	mlx_instance_t;

/**
 * Key function callback data.
 * Data related to the mlx_key_hook function
 * 
 * @param key The key that was pressed.
 * @param action The action that was done with the key.
 * @param os_key The os_key is unique for every key, and will have a 
 * different value/keycode depending on the platform. 
 * They may be consistent on different platforms.
 * @param modifier The modifier key that was pressed, 0 if no key was pressed.
 */
typedef struct mlx_key_data
{
	keys_t			key;
	action_t		action;
	int32_t			os_key;
	modifier_key_t	modifier;
}	mlx_key_data_t;

/**
 * An image with an individual buffer that can be rendered.
 * Any value can be modified except the width/height and context.
 * 
 * @param width The width of the image.
 * @param height The height of the image.
 * @param pixels The literal pixel data.
 * @param instances An instance carrying the X, Y and Z location data.
 * @param count The element count of the instances array.
 * @param enabled If true the image is drawn onto the screen, else it's not.
 * @param context Abstracted OpenGL data.
 */
typedef struct mlx_image
{
	const uint32_t	width;
	const uint32_t	height;
	uint8_t*		pixels;
	mlx_instance_t*	instances;
	size_t			count;
	bool			enabled;
	void*			context;
}	mlx_image_t;

/**
 * Main MLX handle, carries important data in regards to the program.
 * @param window The window itself.
 * @param context Abstracted opengl data.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param delta_time The time difference between the previous frame 
 * and the current frame.
 */
typedef struct mlx
{
	void*		window;
	void*		context;
	int32_t		width;
	int32_t		height;
	double		delta_time;
}	mlx_t;

// The error codes used to identify the correct error message.
typedef enum mlx_errno
{
	MLX_SUCCESS = 0,	// No Errors
	MLX_INVEXT,			// File has an invalid extension
	MLX_INVFILE,		// File was invalid / does not exist.
	MLX_INVPNG,			// Something is wrong with the given PNG file.
	MLX_INVXPM,			// Something is wrong with the given XPM file.
	MLX_INVPOS,			// The specified X/Y positions are out of bounds.
	MLX_INVDIM,			// The specified W/H dimensions are out of bounds.
	MLX_INVIMG,			// The provided image is invalid, might indicate mismanagement of images.
	MLX_VERTFAIL,		// Failed to compile the vertex shader.
	MLX_FRAGFAIL,		// Failed to compile the fragment shader.
	MLX_SHDRFAIL,		// Failed to compile the shaders.
	MLX_MEMFAIL,		// Dynamic memory allocation has failed.
	MLX_GLADFAIL,		// OpenGL loader has failed.
	MLX_GLFWFAIL,		// GLFW failed to initialize.
	MLX_WINFAIL,		// Failed to create a window.
	MLX_STRTOOBIG,		// The string is too big to be drawn.
	MLX_ERRMAX,			// Error count
}	mlx_errno_t;

// Global error code from the MLX42 library, 0 on no error.
extern mlx_errno_t mlx_errno;

//= Global Settings =//

// Set these values, if necessary, before calling `mlx_init` as they define the behaviour of MLX42.
typedef enum mlx_settings
{
	MLX_STRETCH_IMAGE = 0,	// Should images resize with the window as it's being resized or not. Default: false
	MLX_FULLSCREEN,			// Should the window be in Fullscreen, note it will fullscreen at the given resolution. Default: false
	MLX_MAXIMIZED,			// Start the window in a maximized state, overwrites the fullscreen state if this is true. Default: false
	MLX_DECORATED,			// Have the window be decorated with a window bar. Default: true
	MLX_HEADLESS,			// Run in headless mode, no window is created. (NOTE: Still requires some form of window manager such as xvfb)
	MLX_SETTINGS_MAX,		// Setting count.
}	mlx_settings_t;

/**
 * Callback function used to handle scrolling.
 * 
 * @param[in] xdelta The mouse x delta.
 * @param[in] ydelta The mouse y delta.
 * @param[in] param Additional parameter to pass on to the function.
 */
typedef void (*mlx_scrollfunc)(double xdelta, double ydelta, void* param);

/**
 * Callback function used to handle mouse actions.
 * 
 * @param[in] button The mouse button/key pressed.
 * @param[in] action The mouse action that took place.
 * @param[in] mods The modifier keys pressed together with the mouse key.
 * @param[in] param Additional parameter to pass on to the function.
 */
typedef void (*mlx_mousefunc)(mouse_key_t button, action_t action, modifier_key_t mods, void* param);

/**
 * Callback function used to handle raw mouse movement.
 * 
 * @param[in] xpos The mouse x position.
 * @param[in] ypos The mouse y position.
 * @param[in] param Additional parameter to pass on to the function.
 */
typedef void (*mlx_cursorfunc)(double xpos, double ypos, void* param);

/**
 * Callback function used to handle key presses.
 * 
 * @param[in] keydata The callback data, contains info on key, action, ...
 * @param[in] param Additional parameter to pass on to the function.
 */
typedef void (*mlx_keyfunc)(mlx_key_data_t keydata, void* param);

/**
 * Callback function used to handle window resizing.
 * 
 * WARNING: The function is called every frame during which the window is being
 * resized, be aware!
 * 
 * @param[in] width The new width of the window.
 * @param[in] height The new height of the window. 
 * @param[in] param Additional parameter to pass on to the function.
 */
typedef void (*mlx_resizefunc)(int32_t width, int32_t height, void* param);

/**
 * Callback function used to handle window closing which is called when 
 * the user attempts to close the window, for example by clicking the 
 * close widget in the title bar.
 * 
 * @param[in] param Additional parameter to pass on to the function.
 */
typedef void (*mlx_closefunc)(void* param);

/** 
 * Typedef for a window cursor object, these eventually expand to
 * the native cursor object, but are hidden from the user.
 * 
 * Under GLFW they are named GLFWcursor and have a wrapper for each implementation.
 * You can find the ACTUAL cursor in the following files at GLFW named under *_platform.h
 */
typedef void mlx_win_cursor_t;

//= Error Functions =//

/**
 * Gets the english description of the error code.
 * 
 * @param[in] val The error code.
 * @return The error string that describes the error code.
 */
const char* mlx_strerror(mlx_errno_t val);

//= Generic Functions =//

/**
 * Initializes a new MLX42 Instance.
 * 
 * @param[in] width The width of the window.
 * @param[in] height The height of the window.
 * @param[in] title The title of the window.
 * @param[in] resize Enable window resizing.
 * @returns Ptr to the MLX handle or null on failure.
 */
mlx_t* mlx_init(int32_t width, int32_t height, const char* title, bool resize);

/**
 * Set a setting for MLX42.
 * Settings can manipulate the core behaviour of the engine.
 * 
 * @param[in] setting The settings value, See mlx_settings_t type.
 * @param[in] value Settings value to determine the state of the setting. Can be a boolean or an enum / macro.
 */
void mlx_set_setting(mlx_settings_t setting, int32_t value);

/**
 * Notifies MLX that it should stop rendering and exit the main loop.
 * This is not the same as terminate, this simply tells MLX to close the window.
 * 
 * @param[in] mlx The MLX instance handle.
 */
void mlx_close_window(mlx_t* mlx);

/**
 * Initializes the rendering of MLX, this function won't return until
 * mlx_close_window is called, meaning it will loop until the user requests that
 * the window should close.
 * 
 * @param[in] mlx The MLX instance handle.
 */
void mlx_loop(mlx_t* mlx);

/**
 * Lets you set a custom image as the program icon.
 * 
 * NOTE: In MacOS this function does nothing, you should use the bundles icon to set the dock bar icon.
 * @see: https://9to5mac.com/2021/11/08/change-mac-icons/
 * @see: https://github.com/glfw/glfw/issues/2041
 *
 * @param[in] mlx The MLX instance handle.
 * @param[in] image The image to use as icon.
 */
void mlx_set_icon(mlx_t* mlx, mlx_texture_t* image);

/**
 * Terminates MLX and cleans up any of its used resources.
 * Using any functions that require mlx afterwards will
 * be considered undefined behaviour, beware of segfaults.
 * 
 * @param[in] mlx The MLX instance handle.
 */
void mlx_terminate(mlx_t* mlx);

/**
 * Gets the elapsed time since MLX was initialized.
 * 
 * @return The amount of time elapsed in seconds.
 */
double mlx_get_time(void);

//= Window/Monitor Functions =//

/**
 * This function brings the specified window to front and sets input focus.
 * 
 * Do not use this function to steal focus from other applications unless
 * you are certain that is what the user wants. Focus stealing can be
 * extremely disruptive.
 * 
 * @param[in] mlx The MLX instance handle.
 */
void mlx_focus(mlx_t* mlx);

/**
 * Gets the size of the specified monitor.
 * 
 * @param[in] index Normally 0, in case of multiple windows, can be specified
 * @param[in] width The width of the window.
 * @param[in] height The height of the window.
 */
void mlx_get_monitor_size(int32_t index, int32_t* width, int32_t* height);

/**
 * Sets the window's position.
 * 
 *  Do not use this function to move an already visible window unless you
 *  have very good reasons for doing so, as it will confuse and annoy the user.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] xpos The x position.
 * @param[in] ypos The y position.
 */
void mlx_set_window_pos(mlx_t* mlx, int32_t xpos, int32_t ypos);

/**
 * Gets the window's position.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[out] xpos The x position.
 * @param[out] ypos The y position.
 */
void mlx_get_window_pos(mlx_t* mlx, int32_t* xpos, int32_t* ypos);

/**
 * Changes the window size to the newly specified values.
 * Use this to update the window width and height values in the mlx handle.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] new_width The new desired width.
 * @param[in] new_height The new desired height.
 */
void mlx_set_window_size(mlx_t* mlx, int32_t new_width, int32_t new_height);

/**
 * Sets the size limits of the specified window.
 * Will force the window to not be resizable past or below the given values.
 * 
 * Pass -1 for no limit to any of the min/max parameters to ignore that boundary.
 * For instance if you want a min window size but the max window size can be whatever.
 *
 * @param[in] mlx The MLX instance handle.
 * @param[in] min_w The min width of the window.
 * @param[in] max_w The max width of the window.
 * @param[in] min_h The min height of the window.
 * @param[in] max_h The max height of the window.
 */
void mlx_set_window_limit(mlx_t* mlx, int32_t min_w, int32_t min_h, int32_t max_w, int32_t max_h);

/**
 * Sets the title of the window.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] title The window title.
 */
void mlx_set_window_title(mlx_t* mlx, const char* title);

//= Input Functions =//

/**
 * Returns true or false if the key is down or not.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] key The keycode to check, use MLX_KEY_... to specify!
 * @returns True or false if the key is down or not.
 */
bool mlx_is_key_down(mlx_t* mlx, keys_t key);

/**
 * Checks whether a mouse button is pressed or not.
 * 
 * @param[in] mlx The MLX instance handle. 
 * @param[in] key A specific mouse key. e.g MLX_MOUSE_BUTTON_0
 * @returns True or false if the mouse key is down or not.
 */
bool mlx_is_mouse_down(mlx_t* mlx, mouse_key_t key);

/**
 * Returns the current, relative, mouse cursor position on the window, starting
 * from the top left corner.
 * 
 * Negative values or values greater than window width or height 
 * indicate that it is outside the window.
 * 
 * @param[in] mlx The MLX instance handle. 
 * @param[out] x The position.
 * @param[out] y The position.
 */
void mlx_get_mouse_pos(mlx_t* mlx, int32_t* x, int32_t* y);

/**
 * Sets the mouse position.
 * 
 * @param[in] mlx The MLX instance handle. 
 * @param[in] pos The position.
 */
void mlx_set_mouse_pos(mlx_t* mlx, int32_t x, int32_t y);

/**
 * Defines the state for the cursor.
 * 
 * @param[in] mlx The MLX instance handle. 
 * @param[in] mode A specified mouse mode.
 */
void mlx_set_cursor_mode(mlx_t* mlx, mouse_mode_t mode);

/**
 * Retrieves the system standard cursor.
 * 
 * @param[in] type The standard cursor type to create.
 * @return The cursor object or null on failure.
 */
mlx_win_cursor_t* mlx_create_std_cursor(cursor_t type);

/**
 * Allows for the creation of custom cursors with a given texture.
 * 
 * Use mlx_set_cursor to select the specific cursor.
 * Cursors are destroyed at mlx_terminate().
 * 
 * @param[in] texture The texture to use as cursor.
 * @returns The cursor object or null on failure.
 */
mlx_win_cursor_t* mlx_create_cursor(mlx_texture_t* texture);

/**
 * Destroys the given cursor object.
 * 
 * @param[in] cursor The cursor object to destroy.
 */
void mlx_destroy_cursor(mlx_win_cursor_t* cursor);

/**
 * Sets the current cursor to the given custom cursor. 
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] cursor The cursor object to display, if null default cursor is selected.
 */
void mlx_set_cursor(mlx_t* mlx, mlx_win_cursor_t* cursor);

//= Hooks =//

/**
 * This function sets the scroll callback, which is called when a scrolling 
 * device is used, such as a mouse wheel.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The scroll wheel callback function.
 * @param[in] param An additional optional parameter.
 */
void mlx_scroll_hook(mlx_t* mlx, mlx_scrollfunc func, void* param);

/**
 * This function sets the mouse callback, which is called when a mouse
 * does any sort of action such as pressing a key.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The mouse callback function.
 * @param[in] param An additional optional parameter.
 */
void mlx_mouse_hook(mlx_t* mlx, mlx_mousefunc func, void* param);

/**
 * This function sets the cursor callback, which is called when the
 * mouse position changes. Position is relative to the window.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The cursor callback function.
 * @param[in] param An additional optional parameter.
 */
void mlx_cursor_hook(mlx_t* mlx, mlx_cursorfunc func, void* param);

/**
 * This function sets the key callback, which is called when a key is pressed
 * on the keyboard. Useful for single keypress detection.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The keypress callback function.
 * @param[in] param An additional optional parameter.
 */
void mlx_key_hook(mlx_t* mlx, mlx_keyfunc func, void* param);

/**
 * This function sets the close callback, which is called in attempt to close 
 * the window device such as a close window widget used in the window bar.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The close callback function.
 * @param[in] param An additional optional parameter.
 */
void mlx_close_hook(mlx_t* mlx, mlx_closefunc func, void* param);

/**
 * This function sets the resize callback, which is called when the window is
 * resized
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] func The resize callback function.
 * @param[in] param An additional optional parameter.
 */
void mlx_resize_hook(mlx_t* mlx, mlx_resizefunc func, void* param);

/**
 * Generic loop hook for any custom hooks to add to the main loop. 
 * Executes a function per frame, so be careful.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] f The function.
 * @param[in] param The parameter to pass on to the function.
 * @returns Whether or not the hook was added successfully. 
 */
bool mlx_loop_hook(mlx_t* mlx, void (*f)(void*), void* param);

//= Texture Functions =//

/**
 * Decode/load a PNG file into a buffer.
 * 
 * @param[in] path Path to the PNG file.
 * @return If successful the texture data is returned, else NULL.
 */
mlx_texture_t* mlx_load_png(const char* path);

/**
 * Loads an XPM42 texture from the given file path.
 * 
 * @param[in] path The file path to the XPM texture.
 * @returns The XPM texture struct containing its information.
 */
xpm_t* mlx_load_xpm42(const char* path);

/**
 * Deletes a texture by freeing its allocated data.
 * 
 * @param[in] texture The texture to free. 
 */
void mlx_delete_texture(mlx_texture_t* texture);

/**
 * Deletes an XPM42 texture by freeing its allocated data.
 * 
 * This will not remove any already drawn XPMs, it simply
 * deletes the XPM buffer.
 * 
 * @param[in] xpm The xpm texture to delete.
 */
void mlx_delete_xpm42(xpm_t* xpm);

/**
 * Converts a given texture to an image.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] texture The texture to use to create the image from.
 * @return mlx_image_t* The image created from the texture.
 */
mlx_image_t* mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture);

//= Image Functions =//

/**
 * Sets / puts a pixel onto an image.
 * 
 * NOTE: It is considered undefined behaviour when putting a pixel 
 * beyond the bounds of an image.
 * 
 * @param[in] image The MLX instance handle.
 * @param[in] x The X coordinate position.
 * @param[in] y The Y coordinate position.
 * @param[in] color The color value to put.
 */
void mlx_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);

/**
 * Creates and allocates a new image buffer.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] width The desired width of the image.
 * @param[in] height The desired height of the image.
 * @return Pointer to the image buffer, if it failed to allocate then NULL.
 */
mlx_image_t* mlx_new_image(mlx_t* mlx, uint32_t width, uint32_t height);

/**
 * Draws a new instance of an image, it will then share the same
 * pixel buffer as the image.
 * 
 * NOTE: Keep in mind that the instance array gets reallocated, try
 * to store the return value to the instance! 
 * NOT the pointer! It will become invalid!
 * 
 * WARNING: Try to display as few images on the window as possible,
 * drawing too many images will cause a loss in performance!
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] img The image to draw on the screen.
 * @param[in] x The X position.
 * @param[in] y The Y position.
 * @return Index to the instance, or -1 on failure.
 */
int32_t mlx_image_to_window(mlx_t* mlx, mlx_image_t* img, int32_t x, int32_t y);

/**
 * Deleting an image will remove it from the render queue as well as any and all
 * instances it might have. Additionally, just as extra measures sets all the
 * data to NULL.
 * 
 * If you simply wish to stop rendering an image without de-allocation
 * set the 'enabled' boolean in the image struct.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] image The image to delete.
 */
void mlx_delete_image(mlx_t* mlx, mlx_image_t* image);

/**
 * Allows you to resize an image, a new pixel buffer is allocated
 * to fit & the previous data is scaled to fit the new size.
 * 
 * @param[in] img The image to resize.
 * @param[in] nwidth The new width.
 * @param[in] nheight The new height.
 * @return True if image was resized or false on error.
 */
bool mlx_resize_image(mlx_image_t* img, uint32_t nwidth, uint32_t nheight);

/**
 * Sets the depth / Z axis value of an instance.
 * 
 * NOTE: Keep in mind that images that are on the same Z layer cut each other off.
 * so if you don't see your image anymore make sure it's not conflicting by being on
 * the same layer as another image.
 * 
 * @param[in] instance The instance on which to change the depth.
 * @param[in] zdepth The new depth value.
 */
void mlx_set_instance_depth(mlx_instance_t* instance, int32_t zdepth);

//= String Functions =//

/**
 * Draws a string on an image and then outputs it to the window.
 * 
 * @param[in] mlx The MLX instance handle.
 * @param[in] str The string to draw.
 * @param[in] x The X location.
 * @param[in] y The Y location.
 * @return Image ptr to the string.
 */
mlx_image_t* mlx_put_string(mlx_t* mlx, const char* str, int32_t x, int32_t y);

/**
 * Retrieve the texture data for the built-in font.
 * 
 * @return Pointer to the built-in font texture.
 */
const mlx_texture_t* mlx_get_font(void);

/**
 * This function lets you retrieve the X offset 
 * of the given char in the font texture.
 * 
 * NOTE: A single character is 10 * 20 in pixels!
 * 
 * @param[in] c The character to get the offset from.
 * @return Non-negative if found or -1 if not found.
 */
int32_t mlx_get_texoffset(char c);

# ifdef __cplusplus
}
# endif
#endif
