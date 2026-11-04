cmake_minimum_required(VERSION 3.16)
project(ray_caster VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(myapp ${SOURCES})


target_include_directories(myapp PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(myapp PRIVATE ${CURSES_LIBRARIES})


target_compile_options(myapp PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)
