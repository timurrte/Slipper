cmake_minimum_required(VERSION 4.3.1)
project(Slipper LANGUAGES C CXX)

include(FetchContent)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.5.1
)

FetchContent_MakeAvailable(glfw)

add_subdirectory(vendors/glad)
add_subdirectory(src/Application)
add_subdirectory(src/Graphics)
