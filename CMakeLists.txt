cmake_minimum_required(VERSION 3.20)

project(skgl)

set(SRCS
	external/glad/glad.c 
	src/shader.cpp 
	src/texture.cpp 
	src/window.cpp
)

add_library(skgl ${SRCS})

set_property(TARGET skgl PROPERTY CXX_STANDARD 20)

# GLFW
add_subdirectory(external/glfw)

# GLM
add_subdirectory(external/glm)

# INCLUDE 
target_include_directories(${PROJECT_NAME}
	PUBLIC headers
	PUBLIC "external/glfw/include"
	PUBLIC "external/glm"
	PUBLIC "external/glad/include"
	PUBLIC "external/stb"
)

# LINK
target_link_directories(${PROJECT_NAME}
	PRIVATE "external/glfw/src"
)

target_link_libraries(${PROJECT_NAME}
	glfw
)