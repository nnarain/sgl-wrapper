
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

# set src and include directories
set(INCL "include")
set(SRC  "src")
include_directories(${INCL})

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})

# find header & source
file(GLOB_RECURSE HEADER "${INCL}/*.h")
file(GLOB_RECURSE SOURCE "src/*.cpp")

# Get sub folder headers

file(GLOB_RECURSE GLHeaders ${INCL}/SGL/GL/*.h)
file(GLOB_RECURSE GLSources ${SRC}/GL/*.cpp)

file(GLOB_RECURSE UtilHeaders ${INCL}/SGL/Util/*.h)
file(GLOB_RECURSE UtilSources ${SRC}/Util/*.cpp)

file(GLOB_RECURSE 2DHeaders ${INCL}/SGL/2D/*.h)
file(GLOB_RECURSE 2DSources ${SRC}/2D/*.cpp)

file(GLOB_RECURSE TypeHeaders ${INCL}/SGL/Type/*.h)


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

# include groups
source_group("Header Files/GL" FILES ${GLHeaders})
source_group("Header Files/Util"    FILES ${UtilHeaders})
source_group("Header Files/2D"      FILES ${2DHeaders})
source_group("Header Files/Type"    FILES ${TypeHeaders})

# source file groups
source_group("Source Files/GL" FILES ${GLSources})
source_group("Source Files/Util"    FILES ${UtilSources})
source_group("Source Files/2D"      FILES ${2DSources})

# libs
target_link_libraries(${libName} ${OPENGL_gl_LIBRARY})
target_link_libraries(${libName} ${GLEW_LIBRARIES})
