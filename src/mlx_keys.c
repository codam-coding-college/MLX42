/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_keys.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 21:06:45 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/02 02:58:17 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

static void mlx_key_callback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
{
	const mlx_t* mlx = glfwGetWindowUserPointer(window);
	const mlx_key_t key_hook = ((mlx_ctx_t*)mlx->context)->key_hook;
	const mlx_key_data_t callback_data = {
		key,
		scancode,
		action,
		mods,
	};

	key_hook.func(callback_data, key_hook.param);
}

//= Public =//

void mlx_key_hook(mlx_t* mlx, mlx_keyfunc func, void* param)
{
	if (!mlx || !func)
	{
		mlx_error(MLX_NULLARG);
		return;
	}
	mlx_ctx_t* mlxctx = mlx->context;
	mlxctx->key_hook.func = func;
	mlxctx->key_hook.param = param;
	glfwSetKeyCallback(mlx->window, mlx_key_callback);
}

bool mlx_is_key_down(mlx_t* mlx, keys_t key)
{
	return (glfwGetKey(mlx->window, key) == GLFW_PRESS);
}
