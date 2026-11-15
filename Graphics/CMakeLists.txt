add_library(GraphicsGL)

target_sources(GraphicsGL
    PRIVATE
        GraphicsGL.cxx
        glad.c
    PUBLIC
        FILE_SET HEADERS
        FILES
            GraphicsGL.h
)

# 1. Find GLFW (installed via Homebrew)
find_package(glfw3 REQUIRED)

# 2. Find system OpenGL framework (macOS default)
find_package(OpenGL REQUIRED)

# 3. Include directories for GLAD and public headers
target_include_directories(GraphicsGL
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

# 4. Link dependencies portably
target_link_libraries(GraphicsGL
    PRIVATE
        glfw
        OpenGL::GL
)