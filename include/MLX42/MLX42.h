/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MLX42.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 00:33:01 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/01 22:12:02 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
/**
 * New OpenGL graphics library based on the idea on what MiniLibX
 * provides. Just quite a bit better, hopefully.
 * 
 * Written in accordance with norminette 3.3.51 as of 2021.
 */

#ifndef MLX42_H
# define MLX42_H
# include <stdint.h>
# include <stdbool.h>
# include "MLX_Keys.h"
# include "MLX_Vec.h"

/**
 * Main MLX handle, carries important data in regard to the program.
 * @param window The window itself.
 * @param hooks List of all the current hooks.
 * @param title The title of the window.
 * @param width The width.
 * @param height The height.
 */
typedef struct s_MLX
{
	void		*window;
	void		*hooks;
	int32_t		width;
	int32_t		height;
	uint32_t	shaderprogram;
	uint32_t	vao;
}	t_MLX;

typedef struct s_Pixel
{
	t_IVec2	postion;
	int32_t	color;
}	t_Pixel;

/**
 * Initilizes a new MLX42 Instance.
 * 
 * @param Width The width of the window.
 * @param Height The height of the window.
 * @param Title The title of the window.
 * @return Ptr to the MLX handle.
 */
t_MLX	*mlx_init(int32_t Width, int32_t Height, const char *Title, \
bool Resize);

bool	mlx_loop_hook(t_MLX *mlx, void (*f)(void *), void *param);

void	mlx_terminate(t_MLX *mlx);

void	mlx_putpixel(t_MLX *MLX, int32_t X, int32_t Y, int32_t Color);

bool	mlx_is_key_down(t_MLX *mlx, int32_t key);

/**
 * Main program loop, call this last.
 * 
 */
void	mlx_loop(t_MLX *mlx);

#endif