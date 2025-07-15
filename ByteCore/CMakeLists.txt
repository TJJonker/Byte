cmake_minimum_required(VERSION 3.16)
project(ByteCore)

set(CMAKE_CXX_STANDARD 17)

# ImGui
file(GLOB IMGUI_SOURCES vendor/imgui/*.cpp)
add_library(imgui STATIC ${IMGUI_SOURCES})

# Collect source and header files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# Define executable
add_executable(ByteCore ${SOURCES} ${HEADERS})

# Include headers
target_include_directories(ByteCore PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(imgui PUBLIC vendor/imgui)

target_link_libraries(ByteCore 
	imgui
)

# Use C++17
target_compile_features(ByteCore PRIVATE cxx_std_17)

# (Optional) make headers visible in IDE:
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include/ByteCore" PREFIX "Header Files" FILES ${HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${SOURCES})
