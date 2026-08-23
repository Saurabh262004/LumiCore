cmake_minimum_required(VERSION 3.12)
project(GLib LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)
find_package(OpenGL REQUIRED)

# Library

file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS
	"src/*.cpp"
	"src/*.c"
	"external/glad/glad.c"
)

add_library(GLib STATIC ${LIB_SOURCES})

target_include_directories(GLib
	PUBLIC
		include
		external
)

target_link_libraries(GLib
	PUBLIC
		glfw
		OpenGL::GL
		assimp
)

target_compile_options(GLib PRIVATE
	$<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra>
)

# Example application

add_executable(app
	example/Main.cpp
)

target_link_libraries(app
	PRIVATE
		GLib
)
