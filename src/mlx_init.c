/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 00:24:30 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/05 02:28:33 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	framebuffer_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

static void	mlx_draw_frame(t_MLX *mlx)
{
	t_mlx_ctx		*context;

	context = mlx->context;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, NULL);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, (void *)12);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, (void *)24);
	glEnableVertexAttribArray(2);
	glGenTextures(1, &(context->texture));
	glBindTexture(GL_TEXTURE_2D, context->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	mlx->pixels = malloc((mlx->width * mlx->height) * sizeof(int32_t));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mlx->width, mlx->height, 0, \
	GL_BGRA, GL_UNSIGNED_BYTE, mlx->pixels);
	glUniform1i(glGetUniformLocation(context->shaderprogram, "texture"), 0);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
}

static bool	mlx_init_frame(t_MLX *mlx)
{
	t_mlx_ctx		*context;
	const float		vertices[] = {
		// positions            // colors           // texture coords
		-1.0f, +1.0f, 0.0f,		1.0f, 1.0f, 0.0f,	0.0f, 0.0f, // top left 
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f, // bottom left
		+1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f, // bottom right
		+1.0f, +1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f, // top right
	};
	const uint32_t	index[] = {
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	context = mlx->context;
	glGenVertexArrays(1, &(context->vao));
	glGenBuffers(1, &(context->vbo));
	glGenBuffers(1, &(context->ebo));
	glBindVertexArray(context->vao);
	glBindBuffer(GL_ARRAY_BUFFER, context->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, context->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	mlx_draw_frame(mlx);
	return (true);
}

static bool	mlx_init_render(t_MLX *mlx)
{
	uint32_t	s[3];

	if (!mlx->window)
		return (mlx_error(GLFW_WIN_FAILURE));
	glfwMakeContextCurrent(mlx->window);
	glfwSetFramebufferSizeCallback(mlx->window, framebuffer_callback);
	glfwSwapInterval(true);
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			return (mlx_error(GLFW_GLAD_FAILURE));
		if (!mlx_compile_shader(VERTEX_PATH, GL_VERTEX_SHADER, &s[0]) || \
			!mlx_compile_shader(FRAGMENT_PATH, GL_FRAGMENT_SHADER, &s[1]))
			return (mlx_error(MLX_SHADER_FAILURE));
	}
	s[2] = 0;
	if (!mlx_init_shaders(mlx, s))
		return (mlx_error(MLX_SHADER_FAILURE));
	glDeleteShader(s[0]);
	glDeleteShader(s[1]);
	glUseProgram(((t_mlx_ctx *)mlx->context)->shaderprogram);
	return (mlx_init_frame(mlx));
}

t_MLX	*mlx_init(int32_t Width, int32_t Height, const char *Title, bool Resize)
{
	t_MLX		*mlx;
	const bool	init = glfwInit();

	mlx = calloc(1, sizeof(t_MLX));
	if (!mlx || !init)
	{
		free(mlx);
		return ((void *)mlx_error(GLFW_INIT_FAILURE));
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (IS_APPLE)
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, Resize);
	mlx->width = Width;
	mlx->height = Height;
	mlx->window = glfwCreateWindow(Width, Height, Title, NULL, NULL);
	mlx->context = malloc(sizeof(t_mlx_ctx));
	if (!mlx->context || !mlx_init_render(mlx))
	{
		free(mlx);
		return ((void *)mlx_error(MLX_RENDER_FAILURE));
	}
	return (mlx);
}
