# Find Catch2
find_package(Catch2 3 REQUIRED)
include(Catch)

# Test executable
add_executable(test_html_tags test_html_tags.cpp)
target_link_libraries(test_html_tags
    PRIVATE
    CPP_HTML_GEN
    Catch2::Catch2WithMain  # Provides main() automatically
)
target_include_directories(test_html_tags PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Register with CTest
catch_discover_tests(test_html_tags)
