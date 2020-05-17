cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(gta2 VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_program(CMAKE cmake)
if(NOT CMAKE)
    message(FATAL_ERROR "CMake binary not found!")
endif()

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})

set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        )
foreach(CompilerFlag ${CompilerFlags})
  string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
  string(REPLACE "/W3" "" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


add_subdirectory(3rdParty)
add_subdirectory(Source/Framework)
add_subdirectory(Source/Gta2Dll)

if(WIN32)
    # On Windows generate ZIP packages
    SET(CPACK_GENERATOR "ZIP")
endif()

INCLUDE(CPack)
