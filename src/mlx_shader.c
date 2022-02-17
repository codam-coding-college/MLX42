/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_shader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 13:46:01 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/17 22:32:56 by w2wizard      ########   odam.nl         */
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
		return (mlx_log(MLX_ERROR, MLX_NULL_ARG));
	len = strlen(code);
	*out = glCreateShader(type);
	if (!*out)
		return (false);
	glShaderSource(*out, 1, &code, &len);
	glCompileShader(*out);
	glGetShaderiv(*out, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*out, sizeof(infolog), NULL, infolog);
		fprintf(stderr, "%s", infolog);
		return (false);
	}
	return (true);
}
