/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prim_str_draw.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 09:43:26 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/08/03 10:30:23 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.h"
#include "MLX42/MLX42.h"

bool once = false;
void function(mlx_t* mlx)
{
	if (once == false)
	{
		mlx_image_t* img2 = mlx_new_image(mlx, 64, 24);
		memset(img2->pixels, 255, img2->width * img2->height * sizeof(int32_t));
		mlx_image_to_window(mlx, img2, 64, 32);
		mlx_delete_image(mlx, img2);
	}
	once = true;	
}

// Primitive method of updating a string
void ft_draw(void* param)
{
	static char buf[256];
	static int32_t count = 0;
	static mlx_image_t* img = NULL;
	mlx_t *const mlx = param;
	//mlx_ctx_t *const mlxctx = mlx->context;

	if (img) 
		mlx_delete_image(mlx, img);
	// Cheap itoa
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%d", count);
	img = mlx_put_string(mlx, buf, 0, 0);
	count++;

	// Some function modifies the render queue and image list
	function(mlx);
	if (count >= 420)
		mlx_close_window(mlx);
	assert(mlx_errno == MLX_SUCCESS);
}

int32_t main(void)
{
	TEST_DECLARE("prim_str_draw");
	TEST_EXPECT(PASS);

	mlx_set_setting(MLX_HEADLESS, true);
	mlx_t* mlx = mlx_init(128, 64, "TEST", false);
	assert(mlx);

	// Just because we want to do something messed up
	mlx_image_t* img2 = mlx_new_image(mlx , 24, 24);
	memset(img2->pixels, 255, img2->width * img2->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img2, 32, 18);

	mlx_image_t* img3 = mlx_new_image(mlx , 24, 24);
	memset(img3->pixels, 255, img3->width * img3->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img3, 48, 32);

	mlx_image_t* img4 = mlx_new_image(mlx , 24, 24);
	memset(img4->pixels, 255, img4->width * img4->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img4, 32, 48);

	mlx_delete_image(mlx, img3);
	mlx_loop_hook(mlx, ft_draw, mlx);
	mlx_loop(mlx);
	assert(mlx_errno == MLX_SUCCESS);
	TEST_EXIT(EXIT_SUCCESS);
}
