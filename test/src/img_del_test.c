/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   img_del_test.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/03 09:30:25 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/08/03 10:28:27 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.h"
#include "MLX42/MLX42.h"

int32_t main(void)
{
	TEST_DECLARE("img_del");
	TEST_EXPECT(PASS);

	mlx_set_setting(MLX_HEADLESS, true);
	mlx_t* mlx = mlx_init(32, 32, "TEST", false);
	assert(mlx);

	mlx_image_t* img = mlx_new_image(mlx, 32, 32);
	assert(img);
	mlx_image_t* img2 = mlx_new_image(mlx, 32, 32);
	assert(img2);
	
	// Display then delete
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_delete_image(mlx, img);

	// Delete
	mlx_delete_image(mlx, img2);

	// Check errno just to make absolutely sure
	assert(mlx_errno == MLX_SUCCESS);

	mlx_terminate(mlx);
	TEST_EXIT(EXIT_SUCCESS);
}
