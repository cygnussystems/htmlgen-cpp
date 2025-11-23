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
    src/html_tags.cpp
    src/bootstrap.cpp
    src/html_resources.cpp
)

# Header files
set(HEADERS
    include/html_tags.h
    include/html_forward.h
    include/html_core.h
    include/html_basic.h
    include/html_table.h
    include/html_form.h
    include/html_semantic.h
    include/html_media.h
    include/html_interactive.h
    include/html_misc.h
    include/bootstrap.h
    include/html_resources.h
)

# Create static library
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Testing
include(CTest)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
endif()
