/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/18 10:19:40 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/07/18 14:59:06 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.h""
#include "MLX42/MLX42.h"

//////////////////////////

int32_t main(void)
{
	TEST_DECLARE("mlx_init");
	TEST_EXPECT(PASS);

	// DO YOUR TESTING
	assert(sizeof(int) == sizeof(short));

	TEST_EXIT(EXIT_SUCCESS);
}
