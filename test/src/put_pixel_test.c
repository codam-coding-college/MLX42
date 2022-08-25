/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_pixel_test.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/18 10:19:40 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/08/03 10:28:45 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.h"
#include "MLX42/MLX42.h"

int32_t main(void)
{
	TEST_DECLARE("put_pixel");

	mlx_set_setting(MLX_HEADLESS, true);
	mlx_t* mlx = mlx_init(32, 32, "TEST", false);
	mlx_image_t* img = mlx_new_image(mlx, 32, 32);

	assert(mlx_errno == MLX_SUCCESS);

	// Test within bounds.
	TEST_EXPECT(PASS);
	mlx_put_pixel(img, 0, 0, 0xFFFFFFFF);

	// Test out of bounds.
	TEST_EXPECT(FAIL);
	mlx_put_pixel(img, 69, 69, 0xFFFFFFFF);

	// Put pixel passed when it should have failed...
	mlx_terminate(mlx);
	TEST_EXIT(EXIT_FAILURE);
}
