include(FetchContent)

macro(LinkGLFW TARGET)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.3.2
    )

    FetchContent_GetProperties(glfw)

    if (NOT glfw_POPULATED)
        FetchContent_Populate(glfw)

        # Just configure GLFW only
        set(GLFW_BUILD_EXAMPLES     OFF CACHE BOOL "Build Examples" FORCE)
        set(GLFW_BUILD_TESTS        OFF CACHE BOOL "Build tests" FORCE)
        set(GLFW_BUILD_DOCS         OFF CACHE BOOL "Build docs" FORCE)
        set(GLFW_INSTALL            ON CACHE BOOL "Configure an install" FORCE)

        # This excludes glfw from being rebuilt when ALL_BUILD is built
        # it will only be built when a target is built that has a dependency on glfw
        add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR} EXCLUDE_FROM_ALL)

        # Set the target's folders
        set_target_properties(glfw PROPERTIES FOLDER ${PROJECT_NAME}/thirdparty)
    endif()

    target_include_directories(${TARGET} PRIVATE ${glfw_SOURCE_DIR}/include)
    target_link_libraries(${TARGET} glfw)

    add_dependencies(${TARGET} glfw)
endmacro()