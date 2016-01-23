# Find GLEW
# ---------
#
# @author Natesh Narain
#


find_path(GLEW_INCLUDE_DIR 
	NAMES
		GL/glew.h
	PATHS
		/usr/include
		/usr/include/glew/include
		/usr/local/include
		/usr/local/include/glew/include
		
		C:/
		C:/glew
		C:/glew/include
)

find_library(GLEW_LIBRARY 
	NAMES 
		glew32.lib
		
	PATHS
		# TODO Linux paths
		
		C:/glew
		C:/glew/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
	GLEW
	DEFAULT_MSG
	GLEW_INCLUDE_DIR
	GLEW_LIBRARY
)
