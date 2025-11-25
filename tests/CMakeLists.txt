# Find Catch2
find_package(Catch2 3 REQUIRED)
include(Catch)

# Test source files - explicitly listed for better IDE support
set(TEST_SOURCES
    test_main.cpp
    test_10_basic_elements.cpp
    test_11_attributes.cpp
    test_20_table_elements.cpp
    test_21_form_elements.cpp
    test_22_semantic_elements.cpp
    test_25_media_elements.cpp
    test_30_page_context.cpp
    test_31_charts.cpp
    test_70_output_pages.cpp
    test_80_playground_report.cpp
    test_81_playground_generated.cpp
)

# Test executable
add_executable(test_html_tags ${TEST_SOURCES})
target_link_libraries(test_html_tags
    PRIVATE
    html_gen_cpp
    Catch2::Catch2  # We provide our own main in test_main.cpp
)
target_include_directories(test_html_tags PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Register with CTest
catch_discover_tests(test_html_tags)
