cmake_minimum_required(VERSION 3.16)
project(ByteCore)

set(CMAKE_CXX_STANDARD 17)

# Collect source and header files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# Define executable
add_executable(ByteCore ${SOURCES} ${HEADERS})

# Include your local headers
target_include_directories(ByteCore 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Use C++17
target_compile_features(ByteCore PRIVATE cxx_std_17)

# (Optional) make headers visible in IDE:
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include/ByteCore" PREFIX "Header Files" FILES ${HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${SOURCES})
