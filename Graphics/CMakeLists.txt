add_library(GraphicsGL)
target_sources(GraphicsGL
	PRIVATE
		GraphicsGL.cxx
	PUBLIC
		FILE_SET HEADERS
		FILES
			GraphicsGL.h
)