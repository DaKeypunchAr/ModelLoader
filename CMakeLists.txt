cmake_minimum_required(VERSION 3.28...3.29)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(ModelLoader VERSION 1.0.0 LANGUAGES CXX)

add_executable(MLoader "src/Main.cpp" "src/Mesh/Mesh.cpp" "src/OGL/ShaderProgram/Program.cpp" "src/Model/Model.cpp" "src/Model/ModelFactory.cpp")

set(GLFW_LIBRARY_TYPE STATIC)
set(GLFW_BUILD_SHARED_LIBS OFF)

add_subdirectory("glew-2.1.0/build/cmake")
add_subdirectory("glfw-3.4")
add_subdirectory("glm")
add_subdirectory("JSON")

target_link_libraries(MLoader PUBLIC glew_s glfw glm json)

get_filename_component(PROJECT_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
configure_file("src/root.hpp.in" root.hpp @ONLY)

target_include_directories(MLoader PUBLIC 
    "include"
    "glew-2.1.0/include"
    "glfw-3.4/include"
    "FT/include"
    "JSON/include"
    "${CMAKE_CURRENT_BINARY_DIR}"
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(MLoader PUBLIC _DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(MLoader PUBLIC _RELEASE)
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    target_compile_definitions(MLoader PUBLIC _32BIT)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_compile_definitions(MLoader PUBLIC _64BIT)
endif()