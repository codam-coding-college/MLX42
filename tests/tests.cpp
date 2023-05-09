// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by Jelle van Kraaij.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

// If your new to gtest follow the following documentation:
// http://google.github.io/googletest/primer.html

#include "WindowFixture.hpp"

// --------------------------------------------
// Fixture for window tests
// For every TEST_F(window, ...) the SetUp() and TearDown() functions are called
// MLX can be accessed via the mlx variable in each test
// For the implementation of the fixture see tests/windowFixture.hpp
// --------------------------------------------

TEST_F(Window, Basic)
{
	// Basic window is already tested in the fixture
}


// NOTE: This test cannot be run with a fixture because the settings need to be set before the window is created
TEST(MWindow, Settings)
{
	mlx_errno = MLX_SUCCESS;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_set_setting(MLX_DECORATED, true);
	mlx_set_setting(MLX_FULLSCREEN, true);
	
	mlx_set_setting(MLX_HEADLESS, true);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);
	mlx_t *mlx = mlx_init(400, 400, "MLX42", false);
	ASSERT_NE(mlx, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_terminate(mlx);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	// Set all settings to default
	mlx_set_setting(MLX_STRETCH_IMAGE, false);
	mlx_set_setting(MLX_FULLSCREEN, false);
	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx_set_setting(MLX_DECORATED, true);
}

TEST_F(Window, SingleImage)
{
	mlx_image_t* img = mlx_new_image(mlx, Window::width / 2, Window::height / 2);
	ASSERT_NE(img, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);
	
	int32_t val = mlx_image_to_window(mlx, img, Window::width / 4 , Window::height / 4);
	EXPECT_GE(val, 0);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_delete_image(mlx, img);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);
}

TEST_F(Window, MultipleImages)
{
	mlx_image_t* img1 = mlx_new_image(mlx, Window::width / 2, Window::height / 2);
	ASSERT_NE(img1, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_image_t* img2 = mlx_new_image(mlx, Window::width, Window::height);
	ASSERT_NE(img2, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);
	
	int32_t val1 = mlx_image_to_window(mlx, img1, Window::width / 4, Window::height / 4);
	EXPECT_GE(val1, 0);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	int32_t val2 = mlx_image_to_window(mlx, img2, 0, 0);
	EXPECT_GE(val2, 0);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_delete_image(mlx, img1);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_delete_image(mlx, img2);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);
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

TEST_F(Window, stringTortureTest)
{
	mlx_image_t *img = mlx_new_image(mlx, Window::width / 2, Window::height / 2);
	ASSERT_NE(img, nullptr);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	memset(img->pixels, 255, sizeof(int32_t) * img->width * img->height);

	int32_t val_window = mlx_image_to_window(mlx, img, Window::width / 4 , Window::height / 4);
	EXPECT_GE(val_window, 0);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	bool val_hook = mlx_loop_hook(mlx, ft_draw, mlx);
	EXPECT_EQ(val_hook, true);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);
	
	mlx_loop(mlx);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);

	mlx_delete_image(mlx, img);
	ASSERT_EQ(mlx_errno, MLX_SUCCESS);
}
