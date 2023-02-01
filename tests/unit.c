// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

// See See README.md for details
#define CTEST_MAIN
#define CTEST_SEGFAULT
#define CTEST_COLOR_OK
#include "ctest/ctest.h"

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, const char* argv[])
{
	return (ctest_main(argc, argv) > 0 ? EXIT_FAILURE : EXIT_SUCCESS);
}
