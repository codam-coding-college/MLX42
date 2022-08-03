/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_test.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/18 10:19:40 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/08/03 10:28:20 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.h"
#include "MLX42/MLX42.h"

int32_t main(void)
{
	TEST_DECLARE("mlx_init");
	TEST_EXPECT(PASS);

	mlx_set_setting(MLX_HEADLESS, true);
	mlx_t* mlx = mlx_init(32, 32, "TEST", false);
	assert(mlx);
	assert(mlx_errno == MLX_SUCCESS);
	mlx_terminate(mlx);
	TEST_EXIT(EXIT_SUCCESS);
}
