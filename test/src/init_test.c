/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_test.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/18 10:19:40 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/07/20 12:21:04 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.h"
#include "MLX42/MLX42.h"

int main(void)
{
	TEST_DECLARE("mlx_init");

	mlx_t* mlx;
	mlx_set_setting(MLX_HEADLESS, true);

	// Test with valid set
	TEST_EXPECT(PASS);

	mlx = mlx_init(32, 32, "TEST", false);
	assert(mlx);
	mlx_terminate(mlx);

	// Test with bad params.
	TEST_EXPECT(FAIL);
	
	mlx = mlx_init(-1, -1, NULL, false);
	assert(mlx == NULL);
}
