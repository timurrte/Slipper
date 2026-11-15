add_executable(Slipper)
target_sources(Slipper
	PRIVATE
		application.cxx
)
target_link_libraries(Slipper
	PRIVATE
		GraphicsGL
)

add_custom_target(run
    COMMAND $<TARGET_FILE:Slipper>
    DEPENDS Slipper
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    USES_TERMINAL
    COMMENT "Running app..."
)
