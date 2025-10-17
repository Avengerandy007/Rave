cmake_minimum_required(VERSION 4.0)
project(Rave LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all .cpp/.c files under src/ (CONFIGURE_DEPENDS makes CMake re-run when files change)
file(GLOB Rave_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

file(GLOB Rave_INCLUDE
   ${CMAKE_SOURCE_DIR}/include/*.h
   ${CMAKE_SOURCE_DIR}/include/*.hpp
   ${CMAKE_SOURCE_DIR}/GameFr/include/*.hpp
)

add_executable(Rave ${Rave_SOURCES})

add_library(GameFr STATIC IMPORTED)
set_target_properties(GameFr PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/GameFr/libGameFr.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/GameFr/include"
)

add_library(raylib_static STATIC IMPORTED)
set_target_properties(raylib_static PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/Raylib/lib/libraylib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/Raylib/include"
)

target_include_directories(Rave PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/GameFr/include
    ${CMAKE_SOURCE_DIR}/Raylib/include
)
target_link_libraries(Rave PRIVATE GameFr raylib_static)
