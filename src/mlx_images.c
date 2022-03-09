/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_images.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/21 15:34:45 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/03/09 13:36:41 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

//= Private =//

/**
 * Internal function to draw a single instance of an image
 * to the screen.
 */
void mlx_draw_instance(mlx_image_t* img, mlx_instance_t* instance)
{
	vertex_t vertices[6];
	const int32_t w = img->width;
	const int32_t h = img->height;
	const int32_t x = instance->x;
	const int32_t y = instance->y;

	vertices[0] = (vertex_t){x, y, instance->z, 0.f, 0.f};
	vertices[1] = (vertex_t){x + w, y + h, instance->z, 1.f, 1.f};
	vertices[2] = (vertex_t){x + w, y, instance->z, 1.f, 0.f};
	vertices[3] = (vertex_t){x, y, instance->z, 0.f, 0.f};
	vertices[4] = (vertex_t){x, y + h, instance->z, 0.f, 1.f};
	vertices[5] = (vertex_t){x + w, y + h, instance->z, 1.f, 1.f};

	glBindTexture(GL_TEXTURE_2D, ((mlx_image_ctx_t*)img->context)->texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * 6, vertices, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

//= Public =//

void mlx_set_instance_depth(mlx_instance_t* instance, int32_t zdepth)
{
	if (!instance)
	{
		mlx_error(MLX_NULLARG);
		return;
	}
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
	if (!mlx || !img)
		return (mlx_error(MLX_NULLARG), -1);
	
	// Allocate buffers...
	mlx_instance_t* temp = realloc(img->instances, (++img->count) * sizeof(mlx_instance_t));
	draw_queue_t* queue = calloc(1, sizeof(draw_queue_t));
	if (!queue || !temp)
		return (mlx_freen(2, temp, queue), mlx_error(MLX_MEMFAIL), -1);

	// Set data...
	queue->image = img;
	int32_t index = queue->instanceid = img->count - 1;
	img->instances = temp;
	img->instances[index].x = x;
	img->instances[index].y = y;

	// NOTE: We keep updating the Z for the convenience of the user. 
	// Always update Z depth to prevent overlapping images by default.
	img->instances[index].z = ((mlx_ctx_t*)mlx->context)->zdepth++;

	// Add draw call...
	mlx_list_t* templst;
	if ((templst = mlx_lstnew(queue)))
	{
		mlx_lstadd_back(&((mlx_ctx_t*)mlx->context)->render_queue, templst);
		return (index);
	}
	return (mlx_freen(2, temp, queue), mlx_error(MLX_MEMFAIL), -1);
}

mlx_image_t* mlx_new_image(mlx_t* mlx, uint32_t width, uint32_t height)
{
	if (!mlx)
		return ((void*)mlx_error(MLX_NULLARG));
	if (width > INT16_MAX || height > INT16_MAX)
		return ((void*)mlx_error(MLX_IMGTOBIG));
	if (!width || !height)
		return ((void*)mlx_error(MLX_IMGTOSML));

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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, newimg->pixels);
	mlx_lstadd_back((mlx_list_t**)(&mlxctx->images), newentry);
	return (newimg);
}

void mlx_delete_image(mlx_t* mlx, mlx_image_t* image)
{
	if (!mlx || !image)
	{
		mlx_error(MLX_NULLARG);
		return;
	}
	mlx_ctx_t* mlxctx = mlx->context;
	mlx_list_t* imglst = mlx_lstremove(&mlxctx->images, image, &mlx_equal_image);
	mlx_list_t* quelst = mlx_lstremove(&mlxctx->render_queue, image, &mlx_equal_inst);
	if (quelst)
		mlx_freen(2, quelst->content, quelst);
	if (imglst)
	{
		glDeleteTextures(1, &((mlx_image_ctx_t*)image->context)->texture);
		mlx_freen(4, image->pixels, image->instances, image->context, imglst, image);
	}
}

bool mlx_resize_image(mlx_image_t* img, uint32_t nwidth, uint32_t nheight)
{
	if (!img)
		return (mlx_error(MLX_NULLARG));
	if (nwidth > INT16_MAX || nheight > INT16_MAX)
		return (mlx_error(MLX_IMGTOBIG));
	if (!nwidth || !nheight)
		return ((void*)mlx_error(MLX_IMGTOSML));
	if (nwidth != img->width || nheight != img->height)
	{
		uint8_t* tempbuff = realloc(img->pixels, (nwidth * nheight) * BPP);
		if (!tempbuff)
			return (mlx_error(MLX_MEMFAIL));
		img->pixels = tempbuff;
		(*(uint32_t*)&img->width) = nwidth;
		(*(uint32_t*)&img->height) = nheight;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, nwidth, nheight, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
	}
	return (true);
}