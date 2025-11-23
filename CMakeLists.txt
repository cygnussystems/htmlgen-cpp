cmake_minimum_required(VERSION 3.15)
project(CPP_HTML_GEN VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# vcpkg toolchain (for Catch2)
set(CMAKE_TOOLCHAIN_FILE "C:/Users/ritte/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    source/html_tags.cpp
    source/bootstrap.cpp
)

# Header files
set(HEADERS
    include/html_tags.h
    include/bootstrap.h
)

# Create static library
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Testing
include(CTest)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
endif()
