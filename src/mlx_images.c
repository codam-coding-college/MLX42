/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_images.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <main@w2wizard.dev>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 02:29:06 by W2Wizard      #+#    #+#                 */
/*   Updated: 2023/03/30 16:36:39 by ntamayo-      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

void mlx_flush_batch(mlx_ctx_t* mlx)
{
	if (mlx->batch_size <= 0)
		return;

	glBindBuffer(GL_ARRAY_BUFFER, mlx->vbo);
	glBufferData(GL_ARRAY_BUFFER, mlx->batch_size * sizeof(vertex_t), mlx->batch_vertices, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, mlx->batch_size);

	mlx->batch_size = 0;
	memset(mlx->bound_textures, 0, sizeof(mlx->bound_textures));
}

static int8_t mlx_bind_texture(mlx_ctx_t* mlx, mlx_image_t* img)
{
	const GLint handle = (GLint)((mlx_image_ctx_t*)img->context)->texture;

	// Attempt to bind the texture, or obtain the index if it is already bound.
	for (int8_t i = 0; i < 16; i++)
	{
		if (mlx->bound_textures[i] == handle)
			return (i);

		if (mlx->bound_textures[i] == 0)
		{
			mlx->bound_textures[i] = handle;

			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, handle);
			return (i);
		}
	}

	// If no free slot was found, flush the batch and assign the texture to the first available slot
	mlx_flush_batch(mlx);

	mlx->bound_textures[0] = handle;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, handle);
	return (0);
}

/**
 * Internal function to draw a single instance of an image
 * to the screen.
 */
void mlx_draw_instance(mlx_ctx_t* mlx, mlx_image_t* img, mlx_instance_t* instance)
{
	float w = (float) img->width;
	float h = (float) img->height;
	float x = (float) instance->x;
	float y = (float) instance->y;
	float z = (float) instance->z;
	int8_t tex = mlx_bind_texture(mlx, img);

	vertex_t vertices[6] = {
			(vertex_t){x, y, z, 0.f, 0.f, tex},
			(vertex_t){x + w, y + h, z, 1.f, 1.f, tex},
			(vertex_t){x + w, y, z, 1.f, 0.f, tex},
			(vertex_t){x, y, z, 0.f, 0.f, tex},
			(vertex_t){x, y + h, z, 0.f, 1.f, tex},
			(vertex_t){x + w, y + h, z, 1.f, 1.f, tex},
	};
	memmove(mlx->batch_vertices + mlx->batch_size, vertices, sizeof(vertices));
	mlx->batch_size += 6;

	if (mlx->batch_size >= MLX_BATCH_SIZE)
		mlx_flush_batch(mlx);
}

mlx_instance_t* mlx_grow_instances(mlx_image_t* img, bool* did_realloc)
{
	mlx_image_ctx_t* const ctx = img->context;
	if (img->count >= ctx->instances_capacity)
	{
		if (ctx->instances_capacity == 0)
			ctx->instances_capacity = img->count;
		else
			ctx->instances_capacity *= 2;
		*did_realloc = true;
		return realloc(img->instances, ctx->instances_capacity * sizeof(mlx_instance_t));
	}
	*did_realloc = false;
	return img->instances;
}

//= Public =//

void mlx_set_instance_depth(mlx_instance_t* instance, int32_t zdepth)
{
	MLX_NONNULL(instance);

	if (instance->z == zdepth)
		return;
	instance->z = zdepth;

	/**
	 * NOTE: The reason why we don't sort directly is that
	 * the user might call this function multiple times in a row and we don't
	 * want to sort for every change. Pre-loop wise that is.
	 */
	sort_queue = true;
}

int32_t mlx_image_to_window(mlx_t* mlx, mlx_image_t* img, int32_t x, int32_t y)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(img);

	// Allocate buffers...
	img->count++;
	bool did_realloc;
	mlx_instance_t* instances = mlx_grow_instances(img, &did_realloc);
	draw_queue_t* queue = calloc(1, sizeof(draw_queue_t));
	if (!instances || !queue)
	{
		if (did_realloc)
			free(instances);
		return (free(queue), mlx_error(MLX_MEMFAIL), -1);
	}

	// Set data...
	queue->image = img;
	int32_t index = queue->instanceid = img->count - 1;
	img->instances = instances;
	img->instances[index].x = x;
	img->instances[index].y = y;

	// NOTE: We keep updating the Z for the convenience of the user.
	// Always update Z depth to prevent overlapping images by default.
	img->instances[index].z = ((mlx_ctx_t*)mlx->context)->zdepth++;
	img->instances[index].enabled = true;

	// Add draw call...
	sort_queue = true;
	mlx_list_t* templst;
	if ((templst = mlx_lstnew(queue)))
	{
		mlx_lstadd_front(&((mlx_ctx_t*)mlx->context)->render_queue, templst);
		return (index);
	}
	return (mlx_freen(2, instances, queue), mlx_error(MLX_MEMFAIL), -1);
}

mlx_image_t* mlx_new_image(mlx_t* mlx, uint32_t width, uint32_t height)
{
	MLX_NONNULL(mlx);

	if (!width || !height || width > INT16_MAX || height > INT16_MAX)
		return ((void*)mlx_error(MLX_INVDIM));

	const mlx_ctx_t* mlxctx = mlx->context;
	mlx_image_t* newimg = calloc(1, sizeof(mlx_image_t));
	mlx_image_ctx_t* newctx = calloc(1, sizeof(mlx_image_ctx_t));
	if (!newimg || !newctx)
	{
		mlx_freen(2, newimg, newctx);
		return ((void *)mlx_error(MLX_MEMFAIL));
	}
	newimg->enabled = true;
	newimg->context = newctx;
	(*(uint32_t*)&newimg->width) = width;
	(*(uint32_t*)&newimg->height) = height;
	if (!(newimg->pixels = calloc(width * height, sizeof(int32_t))))
	{
		mlx_freen(2, newimg, newctx);
		return ((void *)mlx_error(MLX_MEMFAIL));
	}

	mlx_list_t* newentry;
	if (!(newentry = mlx_lstnew(newimg)))
	{
		mlx_freen(3, newimg->pixels, newimg->context, newimg);
		return ((void *)mlx_error(MLX_MEMFAIL));
	}

	// Generate OpenGL texture
	glGenTextures(1, &newctx->texture);
	glBindTexture(GL_TEXTURE_2D, newctx->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	mlx_lstadd_front((mlx_list_t**)(&mlxctx->images), newentry);
	return (newimg);
}

void mlx_delete_image(mlx_t* mlx, mlx_image_t* image)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(image);

	mlx_ctx_t* mlxctx = mlx->context;

	// Delete all instances in the render queue
	mlx_list_t* quelst;
	while ((quelst = mlx_lstremove(&mlxctx->render_queue, image, &mlx_equal_inst)))
		mlx_freen(2, quelst->content, quelst);

	mlx_list_t* imglst;
	if ((imglst = mlx_lstremove(&mlxctx->images, image, &mlx_equal_image)))
	{
		glDeleteTextures(1, &((mlx_image_ctx_t*)image->context)->texture);
		mlx_freen(5, image->pixels, image->instances, image->context, imglst, image);
	}
}

bool mlx_resize_image(mlx_image_t* img, uint32_t nwidth, uint32_t nheight)
{
	MLX_NONNULL(img);

	if (!nwidth || !nheight || nwidth > INT16_MAX || nheight > INT16_MAX)
		return (mlx_error(MLX_INVDIM));
	if (nwidth != img->width || nheight != img->height)
	{
		uint32_t* origin = (uint32_t*)img->pixels;
		float wstep = (float)img->width / nwidth;
		float hstep = (float)img->height / nheight;

		uint8_t* tempbuff = calloc(nwidth * nheight, BPP);
		if (!tempbuff)
			return (mlx_error(MLX_MEMFAIL));
		img->pixels = tempbuff;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nwidth, nheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);

		uint32_t* destin = (uint32_t*)img->pixels;
		for (uint32_t j = 0; j < nheight; j++)
			for (uint32_t i = 0; i < nwidth; i++)
				destin[j * nwidth + i] = origin[(uint32_t)(j * hstep) * img->width + (uint32_t)(i * wstep)];
		(*(uint32_t*)&img->width) = nwidth;
		(*(uint32_t*)&img->height) = nheight;
		free(origin);
	}
	return (true);
}
