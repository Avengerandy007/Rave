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

target_include_directories(Rave PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/GameFr/include
    ${CMAKE_SOURCE_DIR}/Raylib/include
)
target_link_libraries(Rave PRIVATE 
	${CMAKE_SOURCE_DIR}/GameFr/libGameFr.a
	${CMAKE_SOURCE_DIR}/Raylib/lib/libraylib.a
)
