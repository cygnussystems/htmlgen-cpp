cmake_minimum_required(VERSION 3.15)
project(html_gen_cpp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/html_gen.cpp
    src/html_gen_charts.cpp
    src/resources/bootstrap_css.cpp
    src/resources/bootstrap_js.cpp
    src/resources/apexcharts_js.cpp
)

# Header files
set(HEADERS
    include/html_gen.h
    include/html_forward.h
    include/html_core.h
    include/html_basic.h
    include/html_table.h
    include/html_form.h
    include/html_semantic.h
    include/html_media.h
    include/html_interactive.h
    include/html_misc.h
    include/html_gen_charts.h
    include/html_gen_resources.h
)

# Create static library
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

# Optional testing
option(BUILD_TESTING "Build the tests" ON)
if(BUILD_TESTING)
    # Check if Catch2 is available
    find_package(Catch2 3 QUIET)
    if(Catch2_FOUND)
        include(CTest)
        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
            add_subdirectory(tests)
        endif()
    else()
        message(STATUS "Catch2 not found - tests will not be built")
        message(STATUS "To build tests, install Catch2 via vcpkg or set CMAKE_TOOLCHAIN_FILE")
        set(BUILD_TESTING OFF CACHE BOOL "Build the tests" FORCE)
    endif()
endif()
