add_library(GraphicsGL)

target_sources(GraphicsGL
    PRIVATE
        GraphicsGL.cxx
    PUBLIC
        FILE_SET HEADERS
        FILES
            GraphicsGL.h
)
target_include_directories(GraphicsGL
    PRIVATE
        "C:/include"
)
target_link_libraries(GraphicsGL
    PRIVATE
        "C:/libs/GLFW/glfw3.lib"
)