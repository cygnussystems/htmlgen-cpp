# Find Catch2
find_package(Catch2 3 REQUIRED)
include(Catch)

# Test source files - automatically find all test_*.cpp files
file(GLOB TEST_SOURCES "test_*.cpp")

# Test executable
add_executable(test_html_tags ${TEST_SOURCES})
target_link_libraries(test_html_tags
    PRIVATE
    CPP_HTML_GEN
    Catch2::Catch2  # We provide our own main in test_main.cpp
)
target_include_directories(test_html_tags PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Register with CTest
catch_discover_tests(test_html_tags)
