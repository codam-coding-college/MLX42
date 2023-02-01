<!----------------------------------------------------------------------------
Copyright @ 2021-2022 Codam Coding College. All rights reserved.
See copyright and license notice in the root project for more information.
----------------------------------------------------------------------------->

# Input methods

MLX42 provides various ways of detecting input, you can read about all the available hooks on the [Hooks](./Hooks.md) page.

## Key Detection

### Generic Hook + function

The easiest way of detecting continuous keypressing is via a generic hook and then checking if the specific key is down.
This is the 'traditional' way of detecting if a key is down even in modern game engines. It provides the quickest feedback and if it's used to, say, move a character, the smoothest result.

```c
void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
	if (mlx_is_key_down(param, MLX_KEY_UP))
		g_img->instances[0].y -= 5;
	if (mlx_is_key_down(param, MLX_KEY_DOWN))
		g_img->instances[0].y += 5;
	if (mlx_is_key_down(param, MLX_KEY_LEFT))
		g_img->instances[0].x -= 5;
	if (mlx_is_key_down(param, MLX_KEY_RIGHT))
		g_img->instances[0].x += 5;
}
```

### Hook Function

For more exact input detection such as checking if the key was pressed with `Alt` or `ctrl` you should use the actual Key hook.
Keep in mind that using a keyhook results in a slower feedback compared to using a generic hook but grants you more control in key detection.

```c
void	key_hook(mlx_key_data_t keydata, void* param)
{
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE && keydata.modifier == MLX_CONTROL)
		puts("Gotta grab it all!");
}
```