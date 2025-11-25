/*  ===================================================================
*                      HTML Generator Library - Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*
*  Page Context and Dependency Management Tests
*  Tests for thread-local page context, dependency registration,
*  embedded mode, and script injection capabilities.
*/

#include <catch2/catch_all.hpp>
#include "../include/html_gen.h"

//=============================================================================
// PAGE CONTEXT AND DEPENDENCY MANAGEMENT TESTS
//=============================================================================

TEST_CASE("30100: Page context - basic dependency registration", "[page][dependency]") {
    html::page pg;

    // Manually register dependencies
    pg.require(html::dependency::bootstrap_css);
    pg.require(html::dependency::bootstrap_js);

    CHECK(pg.has_dependency(html::dependency::bootstrap_css));
    CHECK(pg.has_dependency(html::dependency::bootstrap_js));
    CHECK_FALSE(pg.has_dependency(html::dependency::apexcharts_js));

    std::string output = pg.html();
    CHECK(output.find("bootstrap@5.3.0/dist/css/bootstrap.min.css") != std::string::npos);
    CHECK(output.find("bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js") != std::string::npos);
}

TEST_CASE("30110: Page context - bundle dependency", "[page][dependency]") {
    html::page pg;

    // Register bundle should add both CSS and JS
    pg.require(html::dependency::bootstrap_bundle);

    CHECK(pg.has_dependency(html::dependency::bootstrap_bundle));
    CHECK(pg.has_dependency(html::dependency::bootstrap_css));
    CHECK(pg.has_dependency(html::dependency::bootstrap_js));

    std::string output = pg.html();
    CHECK(output.find("bootstrap.min.css") != std::string::npos);
    CHECK(output.find("bootstrap.bundle.min.js") != std::string::npos);
}

TEST_CASE("30120: Page context - init scripts", "[page][scripts]") {
    html::page pg;

    pg.add_on_ready("console.log('Hello');");
    pg.add_on_ready("initTooltips();");

    std::string output = pg.html();
    CHECK(output.find("DOMContentLoaded") != std::string::npos);
    CHECK(output.find("console.log('Hello');") != std::string::npos);
    CHECK(output.find("initTooltips();") != std::string::npos);
}

TEST_CASE("30130: Page context - init script deduplication", "[page][scripts]") {
    html::page pg;

    // Add same script multiple times with same key
    pg.add_on_ready("initTooltips();", "tooltip_init");
    pg.add_on_ready("initTooltips();", "tooltip_init");
    pg.add_on_ready("initTooltips();", "tooltip_init");

    std::string output = pg.html();
    // Should only appear once
    size_t first = output.find("initTooltips();");
    size_t second = output.find("initTooltips();", first + 1);
    CHECK(first != std::string::npos);
    CHECK(second == std::string::npos);
}

TEST_CASE("30140: Page context - thread local access", "[page][context]") {
    // Create page - this should set thread-local context
    html::page pg;

    // Verify thread-local is set
    CHECK(html::detail::current_page == &pg);

    // Create another page - should update context
    {
        html::page pg2;
        CHECK(html::detail::current_page == &pg2);
    }
    // pg2 destroyed, but pg is still alive - context might be cleared
    // This tests the destructor behavior
}

TEST_CASE("30150: Page context - body and head scripts", "[page][scripts]") {
    html::page pg;

    pg.add_head_script("var CONFIG = {debug: true};");
    pg.add_body_script("initApp();");

    std::string output = pg.html();

    // Head script should be in head section
    size_t head_pos = output.find("<head>");
    size_t head_script_pos = output.find("var CONFIG = {debug: true};");
    size_t head_end_pos = output.find("</head>");
    CHECK(head_script_pos > head_pos);
    CHECK(head_script_pos < head_end_pos);

    // Body script should be after body content but before </body>
    size_t body_script_pos = output.find("initApp();");
    size_t body_end_pos = output.find("</body>");
    CHECK(body_script_pos < body_end_pos);
}

TEST_CASE("30160: Page context - ApexCharts dependencies", "[bootstrap][page][dependency]") {
    html::page pg;

    pg.require(html::dependency::apexcharts_js);

    std::string output = pg.html();
    CHECK(output.find("apexcharts") != std::string::npos);
}

TEST_CASE("30170: Page context - add_style for inline CSS", "[page][styles]") {
    html::page pg;

    pg.add_style("body { margin: 0; padding: 0; }");
    pg.add_style(".container { max-width: 1200px; }");

    std::string output = pg.html();
    CHECK(output.find("<style>") != std::string::npos);
    CHECK(output.find("body { margin: 0; padding: 0; }") != std::string::npos);
    CHECK(output.find(".container { max-width: 1200px; }") != std::string::npos);
}

TEST_CASE("30180: Page context - embedded mode for self-contained output", "[page][dependency][embedded]") {
    html::page pg;

    pg.set_dependency_mode(html::dependency_mode::embedded);
    pg.require(html::dependency::bootstrap_css);

    CHECK(pg.get_dependency_mode() == html::dependency_mode::embedded);

    std::string output = pg.html();
    // Should NOT have CDN link
    CHECK(output.find("cdn.jsdelivr.net") == std::string::npos);
    // Should have inline style with Bootstrap CSS content
    CHECK(output.find("<style>") != std::string::npos);
    // Check for some Bootstrap CSS content (this is from the actual Bootstrap CSS)
    bool has_bootstrap_content = (output.find("bootstrap") != std::string::npos) ||
                                  (output.find(".btn") != std::string::npos) ||
                                  (output.find(":root") != std::string::npos);
    CHECK(has_bootstrap_content);
}

TEST_CASE("30190: Page context - embedded mode with Bootstrap JS", "[page][dependency][embedded]") {
    html::page pg;

    pg.set_dependency_mode(html::dependency_mode::embedded);
    pg.require(html::dependency::bootstrap_js);

    std::string output = pg.html();
    // Should NOT have CDN link for JS
    CHECK(output.find("cdn.jsdelivr.net") == std::string::npos);
    // Should have inline script with Bootstrap content
    CHECK(output.find("<script>") != std::string::npos);
}

TEST_CASE("30200: Page context - CDN mode is default", "[page][dependency]") {
    html::page pg;

    CHECK(pg.get_dependency_mode() == html::dependency_mode::cdn);

    pg.require(html::dependency::bootstrap_css);

    std::string output = pg.html();
    // Should have CDN link
    CHECK(output.find("cdn.jsdelivr.net") != std::string::npos);
    CHECK(output.find("bootstrap@5.3.0") != std::string::npos);
}
