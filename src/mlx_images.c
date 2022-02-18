/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_images.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 15:34:45 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/02/18 12:28:15 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

// Reference: https://bit.ly/3KuHOu1 (Matrix View Projection)
static void	mlx_render_texture(t_mlx *mlx, t_mlx_image *img, uint8_t *pixels, \
t_vert *vertices)
{
	t_mlx_ctx		*mlxctx;
	const int32_t	w = img->width;
	const int32_t	h = img->height;
	const float		matrix[16] = {
		2.f / mlx->width, 0, 0, 0,
		0, 2. / -mlx->height, 0, 0,
		0, 0, -2. / (1000. - -1000.), 0,
		-1, -(mlx->height / -mlx->height),
		-((1000. + -1000.) / (1000. - -1000.)), 1
	};

	mlxctx = mlx->context;
	glUseProgram(mlxctx->shaderprogram);
	glUniformMatrix4fv(glGetUniformLocation(mlxctx->shaderprogram, \
	"ProjMatrix"), 1, GL_FALSE, matrix);
	glUniform1i(glGetUniformLocation(mlxctx->shaderprogram, "OutTexture"), 0);
	glBindVertexArray(mlxctx->vao);
	glBindBuffer(GL_ARRAY_BUFFER, mlxctx->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vert) * 6, vertices, \
	GL_STATIC_DRAW);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, \
	GL_UNSIGNED_BYTE, pixels);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

/**
 * Internal function to draw a single instance of an image
 * to the screen.
 */
void	mlx_draw_instance(t_mlx *mlx, t_mlx_image *img, \
t_mlx_instance *instance)
{
	t_mlx_image_ctx	*imgctx;
	const int32_t	w = img->width;
	const int32_t	h = img->height;	
	const int32_t	x = instance->x;
	const int32_t	y = instance->y;

	imgctx = img->context;
	imgctx->vertices[0] = (t_vert){x, y, instance->z, 0.f, 0.f};
	imgctx->vertices[1] = (t_vert){x + w, y + h, instance->z, 1.f, 1.f};
	imgctx->vertices[2] = (t_vert){x + w, y, instance->z, 1.f, 0.f};
	imgctx->vertices[3] = (t_vert){x, y, instance->z, 0.f, 0.f};
	imgctx->vertices[4] = (t_vert){x, y + h, instance->z, 0.f, 1.f};
	imgctx->vertices[5] = (t_vert){x + w, y + h, instance->z, 1.f, 1.f};
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, imgctx->texture);
	mlx_render_texture(mlx, img, img->pixels, imgctx->vertices);
}

//= Exposed =//

t_mlx_inst	*mlx_image_to_window(t_mlx *mlx, t_mlx_image *img, int32_t x, \
int32_t y)
{
	int32_t			index;
	t_mlx_ctx		*mlxctx;
	t_draw_queue	*queue;
	t_mlx_instance	*temp;

	if (!mlx || !img)
		return ((void *)mlx_log(MLX_WARNING, MLX_NULL_ARG));
	mlxctx = mlx->context;
	temp = realloc(img->instances, (++img->count) * sizeof(t_mlx_instance));
	queue = calloc(1, sizeof(t_draw_queue));
	if (!queue || !temp)
	{
		mlx_log(MLX_ERROR, MLX_MEMORY_FAIL);
		return ((void *)mlx_freen(2, temp, queue));
	}
	index = img->count - 1;
	img->instances = temp;
	img->instances[index].x = x;
	img->instances[index].y = y;
	img->instances[index].z = mlxctx->zdepth++;
	queue->image = img;
	queue->instanceid = index;
	mlx_lstadd_back(&mlxctx->render_queue, mlx_lstnew(queue));
	return (&img->instances[index]);
}

t_mlx_image	*mlx_new_image(t_mlx *mlx, uint32_t width, uint32_t height)
{
	t_mlx_image		*newimg;
	t_mlx_image_ctx	*newctx;
	const t_mlx_ctx	*mlxctx = mlx->context;

	newimg = calloc(1, sizeof(t_mlx_image));
	newctx = calloc(1, sizeof(t_mlx_image_ctx));
	if (!newimg || !newctx)
		return ((void *)mlx_freen(2, newimg, newctx));
	(*(uint32_t *)&newimg->width) = width;
	(*(uint32_t *)&newimg->height) = height;
	newimg->context = newctx;
	newimg->pixels = calloc(width * height, sizeof(int32_t));
	if (!newimg->pixels)
		return ((void *)mlx_freen(2, newimg, newctx));
	glGenTextures(1, &newctx->texture);
	glBindTexture(GL_TEXTURE_2D, newctx->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, \
	GL_UNSIGNED_BYTE, newimg->pixels);
	mlx_lstadd_back((t_mlx_list **)(&mlxctx->images), mlx_lstnew(newimg));
	return (newimg->enabled = true, newimg);
}

void	mlx_delete_image(t_mlx *mlx, t_mlx_image *image)
{
	t_mlx_list		*imglst;
	t_mlx_list		*quelst;
	t_mlx_ctx		*mlxctx;

	mlxctx = mlx->context;
	imglst = mlx_lstremove(&mlxctx->images, image, &mlx_equal_image);
	if (imglst)
	{
		glDeleteTextures(1, &((t_mlx_image_ctx *)image->context)->texture);
		mlx_freen(3, image->pixels, image->instances, image->context);
		free(imglst);
	}
	quelst = mlx_lstremove(&mlxctx->render_queue, image, &mlx_equal_inst);
	if (quelst)
	{
		free(quelst->content);
		free(quelst);
	}
	free(image);
}
