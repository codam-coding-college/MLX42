/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 00:24:30 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/28 20:52:09 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	framebuffer_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

static bool	mlx_create_buffers(t_mlx *mlx)
{
	t_mlx_ctx		*context;

	context = mlx->context;
	context->zdepth = 0;
	glActiveTexture(GL_TEXTURE0);
	glGenVertexArrays(1, &(context->vao));
	glGenVertexArrays(1, &(context->vao));
	glGenBuffers(1, &(context->vbo));
	glBindVertexArray(context->vao);
	glBindBuffer(GL_ARRAY_BUFFER, context->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(t_vert), NULL);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(t_vert), \
	(void *)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUniform1i(glGetUniformLocation(context->shaderprogram, "OutTexture"), 0);
	glfwSetWindowSizeCallback(mlx->window, &mlx_on_resize);
	mlx_on_resize(mlx->window, mlx->width, mlx->height);
	return (true);
}

static bool	mlx_init_render(t_mlx *mlx)
{
	uint32_t	s[3];

	if (!mlx->window)
		return (mlx_error(MLX_WINFAIL));
	glfwMakeContextCurrent(mlx->window);
	glfwSetFramebufferSizeCallback(mlx->window, framebuffer_callback);
	glfwSetWindowUserPointer(mlx->window, mlx);
	glfwSwapInterval(MLX_SWAP_INTERVAL);
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			return (mlx_error(MLX_GLADFAIL));
		if (!mlx_compile_shader(g_vert_shader, GL_VERTEX_SHADER, &s[0]) || \
			!mlx_compile_shader(g_frag_shader, GL_FRAGMENT_SHADER, &s[1]))
			return (false);
	}
	s[2] = 0;
	if (!mlx_init_shaders(mlx, s))
		return (false);
	glDeleteShader(s[0]);
	glDeleteShader(s[1]);
	glUseProgram(((t_mlx_ctx *)mlx->context)->shaderprogram);
	return (mlx_create_buffers(mlx));
}

t_mlx	*mlx_init(int32_t Width, int32_t Height, const char *Title, bool Resize)
{
	t_mlx		*mlx;
	const bool	init = glfwInit();

	g_mlx_errno = 0;
	mlx = calloc(1, sizeof(t_mlx));
	if (!mlx || !init)
		return (free(mlx), (void *)mlx_error(MLX_GLFWFAIL));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (IS_APPLE)
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, Resize);
	mlx->width = Width;
	mlx->height = Height;
	mlx->window = glfwCreateWindow(Width, Height, Title, NULL, NULL);
	mlx->context = calloc(1, sizeof(t_mlx_ctx));
	if (!mlx->context || !mlx_init_render(mlx))
	{
		mlx_terminate(mlx);
		return (NULL);
	}
	return (mlx);
}
