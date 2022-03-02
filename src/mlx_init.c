/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 00:24:30 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/02 02:28:30 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

static void	framebuffer_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

static bool	mlx_create_buffers(mlx_t *mlx)
{
	mlx_ctx_t* context = mlx->context;

	context->zdepth = 0;
	glActiveTexture(GL_TEXTURE0);
	glGenVertexArrays(1, &(context->vao));
	glGenVertexArrays(1, &(context->vao));
	glGenBuffers(1, &(context->vbo));
	glBindVertexArray(context->vao);
	glBindBuffer(GL_ARRAY_BUFFER, context->vbo);

	// Vertex XYZ coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), NULL);
	glEnableVertexAttribArray(0);

	// UV Coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void *)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUniform1i(glGetUniformLocation(context->shaderprogram, "OutTexture"), 0);

	// NOTE: Call manually once to calculate View Projection Matrix
	glfwSetWindowSizeCallback(mlx->window, &mlx_on_resize);
	mlx_on_resize(mlx->window, mlx->width, mlx->height);
	return (true);
}

static bool	mlx_init_render(mlx_t *mlx)
{
	uint32_t shaders[3] = {0};

	glfwMakeContextCurrent(mlx->window);
	glfwSetFramebufferSizeCallback(mlx->window, framebuffer_callback);
	glfwSetWindowUserPointer(mlx->window, mlx);
	glfwSwapInterval(MLX_SWAP_INTERVAL);

	// Load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (mlx_error(MLX_GLADFAIL));

	if (!mlx_compile_shader(vert_shader, GL_VERTEX_SHADER, &shaders[0]) || \
		!mlx_compile_shader(frag_shader, GL_FRAGMENT_SHADER, &shaders[1]))
		return (mlx_error(MLX_SHDRFAIL));

	if (!mlx_init_shaders(mlx, shaders))
		return (false);

	glDeleteShader(shaders[0]);
	glDeleteShader(shaders[1]);
	glUseProgram(((mlx_ctx_t*)mlx->context)->shaderprogram);
	return (mlx_create_buffers(mlx));
}

mlx_t* mlx_init(int32_t width, int32_t height, const char* title, bool resize)
{
	mlx_errno = 0;
	if (width <= 0 || height <= 0 || !title)
		return ((void*)mlx_error(MLX_NULLARG));
	
	bool init;
	if (!(init = glfwInit()))
		return ((void*)mlx_error(MLX_GLFWFAIL));

	mlx_t* mlx;
	if (!(mlx = calloc(1, sizeof(mlx_t))))
		return ((void*)mlx_error(MLX_MEMFAIL));
	if (!(mlx->context = calloc(1, sizeof(mlx_ctx_t))))
	{
		free(mlx);
		return ((void*)mlx_error(MLX_MEMFAIL));
	}
	mlx->width = width;
	mlx->height = height;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_RESIZABLE, resize);
	if (!(mlx->window = glfwCreateWindow(width, height, title, NULL, NULL)))
	{
		mlx_terminate(mlx);
		return ((void*)mlx_error(MLX_WINFAIL));
	}
	if (!mlx_init_render(mlx))
	{
		mlx_terminate(mlx);
		return (NULL);
	}
	return (mlx);
}
