/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_shader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 13:46:01 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/02 00:28:52 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

/**
 * Converts an ARGB value to a float component/vector.
 * 
 * @note Because norminette is so good! We need to do * without spaces :)
 * @param color The input RGBA value.
 * @param out Float buffer to apply the converted color values to.
 */
void	mlx_rgba_to_float(int32_t color, t_FVec4 *RGBA_Out)
{
	RGBA_Out->x = (float)(1.0f / UINT8_MAX) *((color >> 24) & 0xFF);
	RGBA_Out->y = (float)(1.0f / UINT8_MAX) *((color >> 16) & 0xFF);
	RGBA_Out->z = (float)(1.0f / UINT8_MAX) *((color >> 8) & 0xFF);
	RGBA_Out->w = (float)(1.0f / UINT8_MAX) *((color >> 0) & 0xFF);
}

/**
 * Reads an entire file into a single allocated string.
 * 
 * @param FilePath The path to the file to read.
 * @return The files content in a single string.
 */
static char	*mlx_readfile(const char *FilePath)
{
	char		*shader;
	int64_t		filesize;
	FILE		*file;

	file = fopen(FilePath, "r");
	if (!file)
		return (NULL);
	fseek(file, 0L, SEEK_END);
	filesize = ftell(file);
	fseek(file, 0L, SEEK_SET);
	shader = calloc(filesize, sizeof(char));
	if (!shader)
		return (NULL);
	fread(shader, sizeof(char), filesize, file);
	fclose(file);
	return (shader);
}

/**
 * Glues together all shaders to the shader program.
 * 
 * @param mlx The MLX instance.
 * @param shaders The array of shaders
 * @return Wether initilization was successful.
 */
bool	mlx_init_shaders(t_MLX *mlx, uint32_t *shaders)
{
	uint32_t	i;
	int			success;
	char		infolog[512];

	i = 0;
	mlx->shaderprogram = glCreateProgram();
	if (!mlx->shaderprogram)
		return (false);
	while (shaders[i])
		glAttachShader(mlx->shaderprogram, shaders[i++]);
	glLinkProgram(mlx->shaderprogram);
	glGetProgramiv(mlx->shaderprogram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(mlx->shaderprogram, sizeof(infolog), NULL, infolog);
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
 * @return uint32_t 
 */
bool	mlx_compile_shader(const char *Path, int32_t Type, uint32_t *out)
{
	int32_t		success;
	char		infolog[512];
	const char	*shader_source = mlx_readfile(Path);

	if (!shader_source)
		return (false);
	*out = glCreateShader(Type);
	if (!*out)
		return (false);
	glShaderSource(*out, 1, &shader_source, NULL);
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

/*
	unsigned VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer
	(
		0,					// Location = 0
		3,					// Size of vertex attribute
		GL_FLOAT,			// Type of the data
		GL_FALSE,			// Normalize data?
		3 * sizeof(float),	// Stride
		(void*)0			// Offset
	);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	unsigned int shader;
	shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);
	
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		fprintf(stderr, infoLog);
		return false;
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		fprintf(stderr, infoLog);
		return false;
	}

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, shader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_shaderProgram, sizeof(infoLog), NULL, infoLog);
		fprintf(stderr, infoLog);
		return false;
	}
	glDeleteShader(shader);
	glDeleteShader(fragmentShader);

	glUseProgram(m_shaderProgram);
	glBindVertexArray(VAO);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
*/