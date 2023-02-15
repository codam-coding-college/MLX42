# -----------------------------------------------------------------------------
# Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
# See README in the root project for more information.
# -----------------------------------------------------------------------------

# Try to find GLFW3 library and include path.
# Once done this will define:
# - GLFW3_FOUND
# - GLFW3_INCLUDE_PATH
# - GLFW3_LIBRARY

# Possbile header locations
set(_glfw3_HEADER_SEARCH_DIRS
"/usr/include"
"/usr/local/include"
"C:/Program Files/glfw/include"
"$ENV{HOME}/.brew/include/"
)

# Possbile library locations
set(_glfw3_LIB_SEARCH_DIRS
"/usr/lib"
"/usr/local/lib"
"C:/Program Files/glfw"
"$ENV{HOME}/.brew/lib/"
)

# Search for the header
find_path(GLFW3_INCLUDE_PATH "GLFW/glfw3.h" PATHS ${_glfw3_HEADER_SEARCH_DIRS})

# Search for the library
find_library(GLFW3_LIBRARY NAMES glfw3 glfw PATHS ${_glfw3_LIB_SEARCH_DIRS})

if (GLFW3_INCLUDE_PATH AND GLFW3_LIBRARY)
	set(glfw3_FOUND "YES")
	include_directories(${GLFW3_INCLUDE_PATH})
	message(STATUS "Found GLFW: ${GLFW3_LIBRARY}")
else()
	set(glfw3_FOUND "NO")
	message(WARNING "Unable to find dependency: GLFW\nDid you install it?")
endif()
