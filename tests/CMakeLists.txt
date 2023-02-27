# -----------------------------------------------------------------------------
# Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
# See README in the root project for more information.
# -----------------------------------------------------------------------------

set(TEST_EXECUTABLE_NAME unit_tests)
set_property(TARGET ${TEST_EXECUTABLE_NAME} PROPERTY CXX_STANDARD 14)

# Download GoogleTest
# --------------------------------------------------
include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
	googletest
	DOWNLOAD_EXTRACT_TIMESTAMP
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG v1.13.0
)

FetchContent_MakeAvailable(googletest)

# --------------------------------------------------
add_executable(
	${TEST_EXECUTABLE_NAME}
	tests.cpp
)

target_link_libraries(
	${TEST_EXECUTABLE_NAME}
	GTest::gtest_main
	mlx42
)

# Add tests to CTest
# --------------------------------------------------
gtest_discover_tests(${TEST_EXECUTABLE_NAME})
enable_testing()
