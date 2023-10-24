// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by Jelle van Kraaij.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

// If your new to gtest follow the following documentation:
// http://google.github.io/googletest/primer.html

#include "WindowFixture.hpp"
#include <MLX42/MLX42_Int.h>

// --------------------------------------------
// Fixture for window tests
// For every TEST_F(window, ...) the SetUp() and TearDown() functions are called
// MLX can be accessed via the mlx variable in each test
// For the implementation of the fixture see tests/windowFixture.hpp
// --------------------------------------------

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

static int32_t mlx_getzdata(mlx_list_t* entry)
{
	const draw_queue_t* queue = entry->content;

	return (queue->image->instances[queue->instanceid].z);
}

TEST(listTest, testsort)
{
	mlx_instance_t inst[6];
	inst[0].z = 4;
	inst[1].z = 2;
	inst[2].z = 87;
	inst[3].z = 3;
	inst[4].z = 9;
	inst[5].z = 7;
	mlx_image_t image;
	image.instances = inst;
	draw_queue_t dqueue[6];
	int i;
	for (i = 0; i < 6; i++)
	{
		dqueue[i].instanceid = i;
		dqueue[i].image = &image;
	}
	mlx_list_t *lst = NULL;
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 1));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 2));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 3));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 4));
	mlx_lstadd_back(&lst, mlx_lstnew(dqueue + 5));
	mlx_sort_renderqueue(&lst);
	int res[6];
	i = 0;
	while (lst)
	{
		res[i] = mlx_getzdata(lst);
		printf("%i\n", res[i]);
		++i;
		lst = lst->next;
	}
}
