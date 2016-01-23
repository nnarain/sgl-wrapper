
#
# SGL Build Configuration
#
# @author Natesh Narain

cmake_minimum_required(VERSION 2.8)

project(sgl)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# find packages
find_package(OpenGL)
find_package(GLEW)

# set src and include directories
set(INCL "include")
set(SRC  "src")

include_directories(
	${INCL}
	
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIR}
)

# find header & source
file(GLOB_RECURSE HEADER "${INCL}/*.h")
file(GLOB_RECURSE SOURCE "src/*.cpp")

# Get sub folder headers

file(GLOB_RECURSE GLHeaders ${INCL}/SGL/GL/*.h)
file(GLOB_RECURSE GLSources ${SRC}/GL/*.cpp)

file(GLOB_RECURSE UtilHeaders ${INCL}/SGL/Util/*.h)
file(GLOB_RECURSE UtilSources ${SRC}/Util/*.cpp)

file(GLOB_RECURSE GraphicsHeaders ${INCL}/SGL/Graphics/*.h)
file(GLOB_RECURSE GraphicsSources ${SRC}/Graphics/*.cpp)

file(GLOB_RECURSE MathHeaders "${INCL}/SGL/Math/*.h")
file(GLOB_RECURSE MathSources "${SRC}/Math/*.cpp")

file(GLOB_RECURSE TypeHeaders ${INCL}/SGL/Type/*.h)


# compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# create
add_library(
	${PROJECT_NAME}
	SHARED
	${SOURCE}
	${HEADER}
)

# include groups
source_group("Header Files/GL"       FILES ${GLHeaders})
source_group("Header Files/Util"     FILES ${UtilHeaders})
source_group("Header Files/Graphics" FILES ${GraphicsHeaders})
source_group("Header Files/Type"     FILES ${TypeHeaders})
source_group("Header Files/Math"     FILES ${MathHeaders})

# source file groups
source_group("Source Files/GL"       FILES ${GLSources})
source_group("Source Files/Util"     FILES ${UtilSources})
source_group("Source Files/Graphics" FILES ${GraphicsSources})
source_group("Source Files/Math"     FILES ${MathSources})

# libs
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARY})
