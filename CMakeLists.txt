cmake_minimum_required(VERSION 3.20)

project(skgl)

set(SRCS
	"external/glad/glad.c"
	"src/shader.cpp"
	"src/texture.cpp" 
	"src/window.cpp"
	"src/camera.cpp"
	"src/model.cpp"
	"src/log.cpp"

	# IMGUI
	"external/imgui/imgui.cpp"
	"external/imgui/imgui_draw.cpp"
	"external/imgui/imgui_tables.cpp"
	"external/imgui/imgui_widgets.cpp"
	
	"external/imgui/backends/imgui_impl_glfw.cpp"
	"external/imgui/backends/imgui_impl_opengl3.cpp"


	# Examples
	"examples/imgui_test/main.cpp"
	#"examples/billboard/main.cpp"
	#"examples/model/main.cpp"
	#"examples/texture/main.cpp"
)

#add_library(skgl ${SRCS})
add_executable(skgl ${SRCS})

set_property(TARGET skgl PROPERTY CXX_STANDARD 20)


# Assimp
set(ASSIMP_DIRECTORY "${PROJECT_SOURCE_DIR}/external/assimp")
set(ASSIMP_INCLUDE_DIRS "${ASSIMP_DIRECTORY}/include" "${ASSIMP_DIRECTORY}/build/include")

set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE INTERNAL "" FORCE)
configure_file(
	"${ASSIMP_DIRECTORY}/include/assimp/config.h.in"
	"${ASSIMP_DIRECTORY}/include/assimp/config.h"
)
configure_file(
	"${ASSIMP_DIRECTORY}/contrib/zlib/zconf.h.cmakein"
	"${ASSIMP_DIRECTORY}/contrib/zlib/zconf.h"
)


# GLFW
add_subdirectory("external/glfw")

# GLM
add_subdirectory("external/glm")

# Assimp 
add_subdirectory("${ASSIMP_DIRECTORY}")

# INCLUDE DIRECTORIES
target_include_directories("${PROJECT_NAME}"
	PUBLIC "headers"
	PUBLIC "external/glfw/include"
	PUBLIC "external/glm"
	PUBLIC "external/glad/include"
	PUBLIC "external/stb"
	PUBLIC "${ASSIMP_DIRECTORY}/include"

	PUBLIC "external/imgui"
	PUBLIC "external/imgui/backends"
)

# LINK DIRECTORIES
target_link_directories(${PROJECT_NAME}
	PRIVATE "external/glfw/src"
)

# LINK LIBRARIES
target_link_libraries(${PROJECT_NAME}
	glfw
	assimp
)