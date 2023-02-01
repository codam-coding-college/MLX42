// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include <stdlib.h>
#include "ctest/ctest.h"
#include "MLX42/MLX42.h"

// Init
// -----------------------------------------------------------------------------

// Simply initializing the lib with nothing.
CTEST(mlx, init)
{
	mlx_set_setting(MLX_HEADLESS, true);

	mlx_t* mlx = mlx_init(32, 32, "Trololo", false);
	if (!mlx) ASSERT_FAIL();

	ASSERT_EQUAL(MLX_SUCCESS, mlx_errno);
	mlx_terminate(mlx);
}

// Some basic image creation
// -----------------------------------------------------------------------------

CTEST(mlx, image)
{
	mlx_set_setting(MLX_HEADLESS, true);
	mlx_t* mlx = mlx_init(32, 32, "Trololo", false);
	ASSERT_NOT_NULL(mlx);

	mlx_image_t* img = mlx_new_image(mlx, 32, 32);
	ASSERT_NOT_NULL(img);
	mlx_image_t* img2 = mlx_new_image(mlx, 32, 32);
	ASSERT_NOT_NULL(img2);

	mlx_image_to_window(mlx, img, 0, 0);
	mlx_delete_image(mlx, img);
	mlx_delete_image(mlx, img2);

	ASSERT_EQUAL(MLX_SUCCESS, mlx_errno);
	mlx_terminate(mlx);
}
