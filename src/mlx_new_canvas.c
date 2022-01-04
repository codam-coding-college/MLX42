/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_new_canvas.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <w2.wizzard@gmail.com>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/28 03:41:55 by W2Wizard      #+#    #+#                 */
/*   Updated: 2022/01/03 16:26:16 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.h"

/*
void	mlx_gl_draw_img:(mlx_img_list_t *)img andCtx:(mlx_img_ctx_t *)imgctx andX:(int)x andY:(int)y
{

  if (pixel_nb >0)
	[self mlx_gl_draw];

  glUseProgram(glsl.image_program);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, imgctx->texture);
  glUniform1i(glsl.loc_image_texture, 0);

  glUniform2f(glsl.loc_image_winhalfsize, size_x/2, size_y/2);
  glUniform2f(glsl.loc_image_pos, x, size_y - y);
  glUniform2f(glsl.loc_image_size, img->width, -img->height);

  glBindBuffer(GL_ARRAY_BUFFER, imgctx->vbuffer);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
  glBlendEquation(GL_FUNC_ADD);

  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  glDisableVertexAttribArray(0);

}
*/

/*
mlx_img_ctx_t	*add_img_to_ctx(mlx_img_list_t *img, mlx_win_list_t *win)
{
  mlx_img_ctx_t	*imgctx;

  imgctx = win->img_list;
  while (imgctx)
	{
	  if (imgctx->img == img)
	return (imgctx);
	  imgctx = imgctx->next;
	}

  imgctx = malloc(sizeof(*imgctx));
  imgctx->img = img;
  imgctx->next = win->img_list;
  win->img_list = imgctx;

  glGenTextures(1, &(imgctx->texture));
  glBindTexture(GL_TEXTURE_2D, imgctx->texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);
  glTexImage2D(
		   GL_TEXTURE_2D, 0,
		   GL_RGBA8,
		   img->width, img->height, 0,
		   GL_BGRA, GL_UNSIGNED_BYTE,
		   img->buffer
		   );

  glGenBuffers(1, &(imgctx->vbuffer));
  glBindBuffer(GL_ARRAY_BUFFER, imgctx->vbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(img->vertexes), img->vertexes, GL_DYNAMIC_DRAW); // 4 points buff

  return (imgctx);
}
*/

/*
static t_mlx_img_ctx	*mlx_create_img_ctx(t_mlx_canvas *img)
{
	t_mlx_img_ctx	*imgctx;

	imgctx = malloc(sizeof(t_mlx_img_ctx));
	imgctx->img = img;
	glGenTextures(1, &(imgctx->texture));
	glBindTexture(GL_TEXTURE_2D, imgctx->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img->width, img->height, 0, \
	GL_BGRA, GL_INT, img->pixels);
	glGenBuffers(1, &(imgctx->vbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, imgctx->vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(img->vertices), img->vertices, \
	GL_DYNAMIC_DRAW);
	return (imgctx);
}
*/

void	mlx_put_image_to_window(t_MLX *mlx, t_mlx_canvas *img, int x, int y)
{
	(void) mlx;
	(void) img;
	(void) x;
	(void) y;
	return ;
}

/*
static void	mlx_init_image()
{
	glGenTextures(1, &(imgctx->texture));
	glBindTexture(GL_TEXTURE_2D, imgctx->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, img->width, img->height, 0, \
	GL_BGRA, GL_INT, img->buffer);
	glGenBuffers(1, &(imgctx->vbuffer));
	glBindBuffer(GL_ARRAY_BUFFER, imgctx->vbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(img->vertexes), img->vertexes, \
	GL_DYNAMIC_DRAW);
}
*/
void	mlx_delete_canvas(void *Img)
{
	(void) Img;
	return ;
}

void	*mlx_new_canvas(t_IVec2 Size)
{
	t_mlx_canvas	*canvas = NULL;
	(void)Size;
	/*
	const int32_t	pixel_count = (Size.x * Size.y) * sizeof(int32_t);
	const GLfloat	rectangle_vertices[8] = {
		+1.0,	+1.0,	// Top Right
		+1.0,	-1.0,	// Bottom Right
		-1.0,	-1.0,	// Bottom Left
		-1.0,	+1.0,	// Top Left
	};
	canvas = malloc(sizeof(t_mlx_canvas));
	if (!canvas)
		return (NULL);
	canvas->width = Size.x;
	canvas->height = Size.y;
	memcpy(canvas->vertices, rectangle_vertices, sizeof(rectangle_vertices));
	canvas->pixels = malloc(pixel_count);
	if (!canvas->pixels)
	{
		free(canvas);
		return (NULL);
	}
	bzero(canvas->pixels, pixel_count);
	*/
	return (canvas);
}
