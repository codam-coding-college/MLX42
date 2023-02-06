// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "test.h"

// Init
// -----------------------------------------------------------------------------

// Simply initializing the lib with nothing.
CTEST(init, basic)
{
	mlx_set_setting(MLX_HEADLESS, true);

	mlx_t* mlx = mlx_init(32, 32, "Trololo", false);
	if (!mlx) ASSERT_FAIL();

	ASSERT_EQUAL(MLX_SUCCESS, mlx_errno);
	mlx_terminate(mlx);
}

CTEST(init, allSettings)
{
	mlx_set_setting(MLX_HEADLESS, true);
	mlx_set_setting(MLX_DECORATED, true);
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_set_setting(MLX_FULLSCREEN, true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);

	mlx_t* mlx = mlx_init(32, 32, "Trololo", false);
	if (!mlx) ASSERT_FAIL();

	ASSERT_EQUAL(MLX_SUCCESS, mlx_errno);
	mlx_terminate(mlx);
}

// Some basic image creation
// -----------------------------------------------------------------------------

CTEST(images, singleImage)
{
	mlx_set_setting(MLX_HEADLESS, true);
	mlx_t* mlx = mlx_init(32, 32, "Trololo", false);
	ASSERT_NOT_NULL(mlx);

	mlx_image_t* img = mlx_new_image(mlx, 32, 32);
	ASSERT_NOT_NULL(img);

	int32_t val = mlx_image_to_window(mlx, img, 0, 0);
	ASSERT_EQUAL(0, val);

	mlx_delete_image(mlx, img);

	ASSERT_EQUAL(MLX_SUCCESS, mlx_errno);
	mlx_terminate(mlx);
}

CTEST(images, twoImages)
{
	mlx_set_setting(MLX_HEADLESS, true);
	mlx_t* mlx = mlx_init(32, 32, "Trololo", false);
	ASSERT_NOT_NULL(mlx);

	mlx_image_t* img = mlx_new_image(mlx, 32, 32);
	ASSERT_NOT_NULL(img);
	mlx_image_t* img2 = mlx_new_image(mlx, 32, 32);
	ASSERT_NOT_NULL(img2);

	int32_t val0 = mlx_image_to_window(mlx, img, 0, 0);
	ASSERT_EQUAL(0, val0);

	int32_t val1 = mlx_image_to_window(mlx, img2, 0, 0);
	ASSERT_EQUAL(0, val1);

	mlx_delete_image(mlx, img);
	mlx_delete_image(mlx, img2);

	ASSERT_EQUAL(MLX_SUCCESS, mlx_errno);
	mlx_terminate(mlx);
}
