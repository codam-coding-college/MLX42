/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_shader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 13:46:01 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/23 12:07:14 by lde-la-h      ########   odam.nl         */
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
		return (mlx_error(MLX_SHDRFAIL));
	while (shaders[i])
		glAttachShader(context->shaderprogram, shaders[i++]);
	glLinkProgram(context->shaderprogram);
	glGetProgramiv(context->shaderprogram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(context->shaderprogram, sizeof(infolog), \
		NULL, infolog);
		fprintf(stderr, "%s", infolog);
		return (mlx_error(MLX_SHDRFAIL));
	}
	i = 0;
	while (shaders[i])
		glDeleteShader(shaders[i++]);
	return (true);
}

/**
 * Compiles the given shader source code, of a given shader type.
 * Returns shader object via param.
 * 
 * @param code The shader source code.
 * @param Type GL_VERTEX_SHADER or GL_FRAGMENT_SHADER or ...
 * @param out The created shader object. 
 * @return Whether it managed to compile the shader or not.
 */
bool	mlx_compile_shader(const char *code, int32_t type, uint32_t *out)
{
	GLint		len;
	int32_t		success;
	char		infolog[512];

	if (!code)
		return (mlx_error(MLX_NULLARG));
	len = strlen(code);
	*out = glCreateShader(type);
	if (!*out)
		return (mlx_error(MLX_SHDRFAIL));
	glShaderSource(*out, 1, &code, &len);
	glCompileShader(*out);
	glGetShaderiv(*out, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*out, sizeof(infolog), NULL, infolog);
		fprintf(stderr, "%s", infolog);
		return (mlx_error(MLX_SHDRFAIL));
	}
	return (true);
}
