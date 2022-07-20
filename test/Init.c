/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/18 10:19:40 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/07/20 10:13:13 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Tester.h"

int main(void)
{
	TEST_DECLARE("test");
	TEST_EXPECT(FAIL);

	TEST_EXIT(EXIT_SUCCESS);
}
