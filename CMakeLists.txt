cmake_minimum_required(VERSION 3.5)
project(shadermania)
set (TARGET shadermania)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${shadermania_SOURCE_DIR}/cmake")
set (CMAKE_CXX_FLAGS "-std=c++14 -O2 -Wall -Wunused-variable -Wunused-parameter -Wextra -Woverloaded-virtual -pedantic -g")

file(GLOB SOURCES "src/*.c*")
add_executable(${TARGET} ${SOURCES})

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-lX11 -lpthread -lXrandr -lXi")

target_include_directories(
  ${TARGET} PUBLIC
  ${SDL2_INCLUDE_DIR}
  ${OPENGL_gl_INCLUDE_DIR}
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(${TARGET} ${SDL2_LIBRARY}
								${CMAKE_DL_LIBS}
								${OPENGL_gl_LIBRARY})
