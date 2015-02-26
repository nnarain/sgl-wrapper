
#
# SGL Build Configuration
#
# @author Natesh Narain

cmake_minimum_required(VERSION 2.8)

project("sgl")
set(libName sgl)

# create output folder
set(bin "bin")
file(MAKE_DIRECTORY ${bin})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${bin})

# find packages
find_package(OpenGL)
find_package(GLEW)
find_package(GLM)

# includes
set(INCL "include/")
include_directories(${INCL})

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})

# find header & source
file(GLOB_RECURSE HEADER "${INCL}*.h")
file(GLOB_RECURSE SOURCE "src/*.cpp")

# compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# define macros
add_definitions(-DGLM_FORCE_RADIANS)

# create
add_library(
	${libName}
	SHARED
	${SOURCE}
	${HEADER}
)

# libs
target_link_libraries(${libName} ${OPENGL_gl_LIBRARY})
target_link_libraries(${libName} ${GLEW_LIBRARIES})
