cmake_minimum_required(VERSION 3.10)
project(GfxEngine LANGUAGES C CXX)

# Use C++20 for modern features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable modern MSVC runtime selection
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

# Locate GLFW
# Note: Using physical paths as provided by user
set(GLFW_ROOT "${CMAKE_SOURCE_DIR}/third_party/glfw-3.4/glfw-3.4")
set(GLFW_INCLUDE_DIRS "${GLFW_ROOT}/include")
set(GLFW_LIBRARY_PATH "${GLFW_ROOT}/lib-vc2022")

# Include directories
# We use target_include_directories for better scoping
include_directories(include ${GLFW_INCLUDE_DIRS})

# Library directories
link_directories(${GLFW_LIBRARY_PATH})

# Define the executable
add_executable(GfxEngine 
    src/main.cpp 
    src/Engine.cpp
    src/glad.c
    include/Engine.h
)

# Provide the specific library name
# Usually glfw3 for static, glfw3dll for DLL
set(GLFW_LIBS "glfw3")

# Link the libraries to your executable
target_link_libraries(GfxEngine PRIVATE ${GLFW_LIBS} opengl32)
