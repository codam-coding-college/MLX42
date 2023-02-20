# -----------------------------------------------------------------------------
# Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
# See README in the root project for more information.
# -----------------------------------------------------------------------------

# CMake specifications
# -----------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.18.0)
project(mlx42 VERSION 2.3.0)
message(STATUS "MLX42 @ ${CMAKE_PROJECT_VERSION}")

# Variables
# -----------------------------------------------------------------------------
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TOOLS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tools)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Options
set(DEBUG		OFF CACHE BOOL "Build MLX42 in debug mode, enabling assertions")
set(GLFW_FETCH	ON CACHE BOOL "Clone and install GLFW")

# Compile Options
# -----------------------------------------------------------------------------

# Reduce the size of LodePNG, we don't need these things.
add_definitions(-D LODEPNG_NO_COMPILE_ENCODER)
add_definitions(-D LODEPNG_NO_COMPILE_ANCILLARY_CHUNKS)

if(UNIX)
	set(CCSHADER ${PROJECT_SOURCE_DIR}/tools/compile_shader.sh)
	add_compile_options(
		-Wextra
		-Wall
		-Werror
		-Wunreachable-code
		
		# Some low priority warnings that are annoying.
		-Wno-char-subscripts
		-Wno-sign-compare
		-Wno-unused-parameter
		-Wno-missing-field-initializers
	)
	if(DEBUG)
		message(STATUS "Building in DEBUG mode")
		add_compile_options(-g)
	else()
		message(STATUS "Building in RELEASE mode")
		add_definitions(-D NDEBUG)
		add_compile_options(-Ofast)
	endif(DEBUG)
else()
	# TODO: Figure out what we need for windows.
	set(CCSHADER ${PROJECT_SOURCE_DIR}/tools/compile_shader.bat)
endif()

# Build specific files
# @see https://cmake.org/cmake/help/latest/command/add_custom_command.html
# -----------------------------------------------------------------------------

add_custom_command(
	COMMENT "Building fragment shader"
	DEPENDS ${PROJECT_SOURCE_DIR}/shaders/default.frag
	OUTPUT mlx_frag_shader.c
	COMMAND ${CCSHADER} ${PROJECT_SOURCE_DIR}/shaders/default.frag > mlx_frag_shader.c
	VERBATIM
	PRE_BUILD
	USES_TERMINAL
)

add_custom_command(
	COMMENT "Building vertex shader"
	DEPENDS ${PROJECT_SOURCE_DIR}/shaders/default.vert
	OUTPUT mlx_vert_shader.c
	COMMAND ${CCSHADER} ${PROJECT_SOURCE_DIR}/shaders/default.vert > mlx_vert_shader.c
	VERBATIM
	PRE_BUILD
	USES_TERMINAL
)

# Sources
# -----------------------------------------------------------------------------
add_library(mlx42 STATIC

	# Root
	${SOURCE_DIR}/mlx_cursor.c
	${SOURCE_DIR}/mlx_exit.c
	${SOURCE_DIR}/mlx_images.c
	${SOURCE_DIR}/mlx_init.c
	${SOURCE_DIR}/mlx_keys.c
	${SOURCE_DIR}/mlx_loop.c
	${SOURCE_DIR}/mlx_monitor.c
	${SOURCE_DIR}/mlx_mouse.c
	${SOURCE_DIR}/mlx_put_pixel.c
	${SOURCE_DIR}/mlx_window.c

	# Utils
	${SOURCE_DIR}/utils/mlx_error.c
	${SOURCE_DIR}/utils/mlx_list.c
	${SOURCE_DIR}/utils/mlx_utils.c
	${SOURCE_DIR}/utils/mlx_compare.c

	# Textures
	${SOURCE_DIR}/font/mlx_font.c
	${SOURCE_DIR}/textures/mlx_png.c
	${SOURCE_DIR}/textures/mlx_texture.c
	${SOURCE_DIR}/textures/mlx_xpm42.c

	# Libs
	lib/png/lodepng.c
	lib/glad/glad.c

	mlx_vert_shader.c
	mlx_frag_shader.c
)
target_include_directories(mlx42 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Dependencies
# -----------------------------------------------------------------------------

find_package(glfw3)
find_package(OpenGL REQUIRED)

if (NOT glfw3_FOUND AND GLFW_FETCH)
	message(STATUS "Install GLFW to supress this message")
	message(STATUS "Please wait, fetching GLFW ...")
	include(${CMAKE_DIR}/LinkGLFW.cmake)
	LinkGLFW(mlx42)
elseif(NOT glfw3_FOUND AND NOT GLFW_FETCH)
	message(FATAL_ERROR "Unable to build: GLFW can't be found nor fetched.")
endif()

# add correct frameworks for macOS
if(APPLE)
target_link_libraries(mlx42 "-framework Cocoa" "-framework IOKit")
endif()

target_link_libraries(mlx42 OpenGL::GL glfw)
