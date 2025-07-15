cmake_minimum_required(VERSION 3.16)
project(ByteCore)

set(CMAKE_CXX_STANDARD 17)

# ImGui
file(GLOB IMGUI_SOURCES 
    vendor/imgui/*.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})

# GLAD
add_library(glad STATIC vendor/glad/src/glad.c)

# GLFW
add_subdirectory(vendor/glfw)
include_directories(vendor/glfw/include)

# Collect source and header files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# Define executable
add_executable(ByteCore ${SOURCES} ${HEADERS})

# Include headers
target_include_directories(ByteCore PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(imgui PUBLIC vendor/imgui)
target_include_directories(glad PUBLIC vendor/glad/include)

target_link_libraries(ByteCore 
	imgui
	glad
	glfw
	opengl32
)

# Use C++17
target_compile_features(ByteCore PRIVATE cxx_std_17)

# (Optional) make headers visible in IDE:
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include/ByteCore" PREFIX "Header Files" FILES ${HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${SOURCES})
