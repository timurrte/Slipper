add_library(GraphicsGL)

target_sources(GraphicsGL
    PRIVATE
        GraphicsGL.cxx
    PUBLIC
        FILE_SET HEADERS
        FILES
            GraphicsGL.h
)
find_package(OpenGL REQUIRED)

target_link_libraries(GraphicsGL
    PRIVATE
        glfw
        glad::glad
        OpenGL::GL
)
