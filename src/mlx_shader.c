/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_shader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 13:46:01 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/30 20:57:11 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

/**
 * Glues together all shaders to the shader program.
 * 
 * @param mlx The MLX instance.
 * @param shaders The array of shaders
 * @return Wether initilization was successful.
 */
bool	mlx_init_shaders(t_mlx *mlx, uint32_t *shaders)
{
	uint32_t	i;
	int			success;
	char		infolog[512];
	t_mlx_ctx	*context;

	i = 0;
	context = mlx->context;
	context->shaderprogram = glCreateProgram();
	if (!context->shaderprogram)
		return (false);
	while (shaders[i])
		glAttachShader(context->shaderprogram, shaders[i++]);
	glLinkProgram(context->shaderprogram);
	glGetProgramiv(context->shaderprogram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(context->shaderprogram, sizeof(infolog), \
		NULL, infolog);
		fprintf(stderr, "%s", infolog);
		return (false);
	}
	i = 0;
	while (shaders[i])
		glDeleteShader(shaders[i++]);
	return (true);
}

/**
 * Opens the shader file and compiles it.
 * 
 * @param Path File path to the shader.
 * @param Type GL_VERTEX_SHADER or GL_FRAGMENT_SHADER or ...
 * @return Whether it managed to compile the shader or not.
 */
bool	mlx_compile_shader(const char *Path, int32_t Type, uint32_t *out)
{
	GLint		len;
	int32_t		success;
	char		infolog[512];
	const char	*shader_source = mlx_readfile(Path);

	if (!shader_source)
		return (mlx_error(MLX_INVALID_FILE));
	len = strlen(shader_source);
	*out = glCreateShader(Type);
	if (!*out)
		return (false);
	glShaderSource(*out, 1, &shader_source, &len);
	glCompileShader(*out);
	glGetShaderiv(*out, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*out, sizeof(infolog), NULL, infolog);
		fprintf(stderr, "%s", infolog);
		free((void *)shader_source);
		return (false);
	}
	free((void *)shader_source);
	return (true);
}
