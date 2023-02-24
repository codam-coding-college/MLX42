#include <gtest/gtest.h>
#include <MLX42/MLX42.h>

TEST(MLX42, init_basic)
{
	mlx_set_setting(MLX_HEADLESS, true);

	mlx_t* mlx = mlx_init(32, 32, "Trololo", false);
	ASSERT_NE(mlx, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);
	mlx_terminate(mlx);
}

TEST(MLX42, init_allSettings)
{
	mlx_set_setting(MLX_HEADLESS, true);
	mlx_set_setting(MLX_DECORATED, true);
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_set_setting(MLX_FULLSCREEN, true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);

	mlx_t* mlx = mlx_init(32, 32, "Trololo", false);
	ASSERT_NE(mlx, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_terminate(mlx);
}

TEST(MLX42, image_single)
{
	mlx_set_setting(MLX_HEADLESS, true);

	mlx_t* mlx = mlx_init(32, 32, "Trololo", false);
	ASSERT_NE(mlx, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_image_t* img = mlx_new_image(mlx, 32, 32);
	ASSERT_NE(img, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);
	
	int32_t val = mlx_image_to_window(mlx, img, 0, 0);
	EXPECT_EQ(val, 0);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_delete_image(mlx, img);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);
	
	mlx_terminate(mlx);
}

TEST(MLX42, image_multiple)
{
	mlx_set_setting(MLX_HEADLESS, true);

	mlx_t* mlx = mlx_init(32, 32, "Trololo", false);
	ASSERT_NE(mlx, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_image_t* img1 = mlx_new_image(mlx, 32, 32);
	ASSERT_NE(img1, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_image_t* img2 = mlx_new_image(mlx, 32, 32);
	ASSERT_NE(img2, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);
	
	int32_t val1 = mlx_image_to_window(mlx, img1, 0, 0);
	EXPECT_EQ(val1, 0);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	int32_t val2 = mlx_image_to_window(mlx, img2, 0, 0);
	EXPECT_EQ(val2, 0);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_delete_image(mlx, img1);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_delete_image(mlx, img2);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);
	
	mlx_terminate(mlx);
}

static void ft_draw(void* param)
{
	static char buf[256];
	static int32_t count = 0;
	static mlx_image_t* img = nullptr;
	mlx_t* mlx = (mlx_t*)param;

	if (img == nullptr) 
	{
		mlx_delete_image(mlx, img);
		ASSERT_EQ(mlx_errno, MLX_SUCCESS);
	}

	// Cheap itoa lol
	memset(buf, '\0', sizeof(buf));
	snprintf(buf, sizeof(buf), "%d", count);
	
	img = mlx_put_string(mlx, buf, 0, 0);
	ASSERT_NE(img, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	if (count >= 420)
	{
		mlx_close_window(mlx);
		ASSERT_EQ(mlx_errno, MLX_SUCCESS);
	}
	count++;
}

TEST(MLX42, string_draw)
{
	mlx_set_setting(MLX_HEADLESS, true);

	mlx_t* mlx = mlx_init(400, 400, "Trololo", false);
	ASSERT_NE(mlx, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_image_t *img = mlx_new_image(mlx, 200, 200);
	ASSERT_NE(img, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	memset(img->pixels, 255, sizeof(int32_t) * img->width * img->height);

	int32_t val_window = mlx_image_to_window(mlx, img, 150, 150);
	EXPECT_EQ(val_window, 0);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	bool val_hook = mlx_loop_hook(mlx, ft_draw, mlx);
	EXPECT_EQ(val_hook, true);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);
	
	mlx_loop(mlx);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_delete_image(mlx, img);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_terminate(mlx);
}
