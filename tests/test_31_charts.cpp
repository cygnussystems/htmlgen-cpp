/*  ===================================================================
*                      HTML Generator Library - Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*
*  Chart Tests - ApexCharts Integration
*  Comprehensive tests for line_chart, bar_chart, and timeseries_line_chart
*/

#include <catch2/catch_all.hpp>
#include "../include/html_gen.h"
#include "../include/html_gen_charts.h"

//=============================================================================
// BASIC FUNCTIONALITY TESTS
//=============================================================================

TEST_CASE("31000: Line chart - basic functionality", "[chart][line]") {
    chart::line_chart chart;
    chart.m_id = "test_chart";
    chart.m_color = "#ff0000";
    chart.add(10.0);
    chart.add(20.0);
    chart.add(15.0);

    std::string html = chart.html();
    CHECK(html.find("test_chart") != std::string::npos);
    CHECK(html.find("ApexCharts") != std::string::npos);
    CHECK(html.find("#ff0000") != std::string::npos);
}

TEST_CASE("31010: Bar chart - basic functionality", "[chart][bar]") {
    chart::bar_chart chart;
    chart.m_id = "bar_chart";
    chart.add("Jan", 100.0);
    chart.add("Feb", 150.0);
    chart.add("Mar", 120.0);

    std::string html = chart.html();
    CHECK(html.find("bar_chart") != std::string::npos);
    CHECK(html.find("ApexCharts") != std::string::npos);
    CHECK(html.find("'Jan'") != std::string::npos);
    CHECK(html.find("'Feb'") != std::string::npos);
    CHECK(html.find("'Mar'") != std::string::npos);
}

TEST_CASE("31020: Timeseries line chart - basic functionality", "[chart][timeseries]") {
    chart::timeseries_line_chart chart;
    chart.m_id = "ts_chart";
    chart.m_color = "#0000ff";

    auto now = std::chrono::system_clock::now();
    chart.add(now, 100.0);
    chart.add(now + std::chrono::hours(1), 110.0);
    chart.add(now + std::chrono::hours(2), 105.0);

    std::string html = chart.html();
    CHECK(html.find("ts_chart") != std::string::npos);
    CHECK(html.find("ApexCharts") != std::string::npos);
    CHECK(html.find("datetime") != std::string::npos);
}

//=============================================================================
// AUTO-REGISTRATION TESTS
//=============================================================================

TEST_CASE("31100: Line chart auto-registers apexcharts dependency", "[chart][line][dependency]") {
    html::page pg;

    chart::line_chart chart;
    chart.m_id = "chart1";
    chart.add(10.0);

    // Chart should auto-register dependency when html() is called
    pg << chart.html();

    std::string page_output = pg.html();
    // Should have apexcharts in the output
    CHECK(page_output.find("apexcharts") != std::string::npos);
}

TEST_CASE("31110: Bar chart auto-registers apexcharts dependency", "[chart][bar][dependency]") {
    html::page pg;

    chart::bar_chart chart;
    chart.m_id = "chart2";
    chart.add("A", 10.0);

    pg << chart.html();

    CHECK(pg.has_dependency(html::dependency::apexcharts_js));
}

TEST_CASE("31120: Multiple charts don't duplicate dependency", "[chart][dependency]") {
    html::page pg;

    chart::line_chart chart1;
    chart1.m_id = "chart1";
    chart1.add(10.0);

    chart::bar_chart chart2;
    chart2.m_id = "chart2";
    chart2.add("A", 20.0);

    pg << chart1.html() << chart2.html();

    // Should only have one apexcharts dependency
    std::string output = pg.html();
    size_t first = output.find("apexcharts");
    size_t second = output.find("apexcharts", first + 1);

    // Check we found it at least once
    CHECK(first != std::string::npos);
    // If we find it again, it should be in the chart code, not duplicate CDN link
    // The CDN link pattern is more specific
    size_t cdn_first = output.find("cdn.jsdelivr.net/npm/apexcharts");
    size_t cdn_second = output.find("cdn.jsdelivr.net/npm/apexcharts", cdn_first + 1);
    CHECK(cdn_first != std::string::npos);
    CHECK(cdn_second == std::string::npos); // Should not find duplicate CDN link
}

//=============================================================================
// ERROR HANDLING TESTS
//=============================================================================

TEST_CASE("31200: Line chart throws when no data added", "[chart][line][error]") {
    chart::line_chart chart;
    chart.m_id = "empty_chart";

    CHECK_THROWS_AS(chart.html(), std::runtime_error);
    CHECK_THROWS_WITH(chart.html(), "line_chart: no data added");
}

TEST_CASE("31210: Bar chart throws when no data added", "[chart][bar][error]") {
    chart::bar_chart chart;
    chart.m_id = "empty_bar";

    CHECK_THROWS_AS(chart.html(), std::runtime_error);
    CHECK_THROWS_WITH(chart.html(), "bar_chart: no data added");
}

TEST_CASE("31220: Timeseries chart throws when no data added", "[chart][timeseries][error]") {
    chart::timeseries_line_chart chart;
    chart.m_id = "empty_ts";

    CHECK_THROWS_AS(chart.html(), std::runtime_error);
    CHECK_THROWS_WITH(chart.html(), "timeseries_line_chart: no data added");
}

//=============================================================================
// OUTPUT VALIDATION TESTS
//=============================================================================

TEST_CASE("31300: Line chart creates div with correct ID", "[chart][line][output]") {
    chart::line_chart chart;
    chart.m_id = "my_unique_chart";
    chart.add(5.0);

    std::string html = chart.html();
    CHECK(html.find("id=\"my_unique_chart\"") != std::string::npos);
}

TEST_CASE("31310: Line chart generates valid ApexCharts config", "[chart][line][output]") {
    chart::line_chart chart;
    chart.m_id = "validation_chart";
    chart.m_data_name = "Sales";
    chart.add(10.0);
    chart.add(20.0);

    std::string html = chart.html();

    // Check for key ApexCharts config elements
    CHECK(html.find("chart: {") != std::string::npos);
    CHECK(html.find("type: 'line'") != std::string::npos);
    CHECK(html.find("series: [") != std::string::npos);
    CHECK(html.find("name: 'Sales'") != std::string::npos);
    CHECK(html.find("data: [10") != std::string::npos);
}

TEST_CASE("31320: Bar chart categories are properly quoted", "[chart][bar][output]") {
    chart::bar_chart chart;
    chart.m_id = "cat_chart";
    chart.add("Category A", 100.0);
    chart.add("Category B", 200.0);

    std::string html = chart.html();

    // Categories should be in quotes
    CHECK(html.find("'Category A'") != std::string::npos);
    CHECK(html.find("'Category B'") != std::string::npos);
    CHECK(html.find("categories: [") != std::string::npos);
}

TEST_CASE("31330: Timeseries has datetime xaxis", "[chart][timeseries][output]") {
    chart::timeseries_line_chart chart;
    chart.m_id = "time_chart";

    auto now = std::chrono::system_clock::now();
    chart.add(now, 50.0);

    std::string html = chart.html();

    CHECK(html.find("xaxis: {") != std::string::npos);
    CHECK(html.find("type: 'datetime'") != std::string::npos);
}

TEST_CASE("31340: Chart script tag is created", "[chart][output]") {
    chart::line_chart chart;
    chart.m_id = "script_test";
    chart.add(1.0);

    std::string html = chart.html();

    CHECK(html.find("<script>") != std::string::npos);
    CHECK(html.find("</script>") != std::string::npos);
    CHECK(html.find(".render()") != std::string::npos);
}

TEST_CASE("31350: Colors array contains custom color", "[chart][line][output]") {
    chart::line_chart chart;
    chart.m_id = "color_test";
    chart.m_color = "#ff00ff";
    chart.add(10.0);

    std::string html = chart.html();

    CHECK(html.find("colors: ['#ff00ff']") != std::string::npos);
}

//=============================================================================
// CONFIGURATION TESTS
//=============================================================================

TEST_CASE("31400: Line chart default values", "[chart][line][config]") {
    chart::line_chart chart;

    CHECK(chart.m_id == "chart");
    CHECK(chart.m_data_name == "data");
    CHECK(chart.m_height == "350");
    CHECK(chart.m_color == "#3498db");
}

TEST_CASE("31410: Bar chart default values", "[chart][bar][config]") {
    chart::bar_chart chart;

    CHECK(chart.m_id == "chart");
    CHECK(chart.m_data_name == "data");
    CHECK(chart.m_height == "350");
}

TEST_CASE("31420: Custom height appears in output", "[chart][line][config]") {
    chart::line_chart chart;
    chart.m_id = "height_test";
    chart.m_height = "500";
    chart.add(10.0);

    std::string html = chart.html();

    CHECK(html.find("height: 500") != std::string::npos);
}

TEST_CASE("31430: Custom data name appears in series", "[chart][bar][config]") {
    chart::bar_chart chart;
    chart.m_id = "name_test";
    chart.m_data_name = "Revenue";
    chart.add("Q1", 1000.0);

    std::string html = chart.html();

    CHECK(html.find("name: 'Revenue'") != std::string::npos);
}

//=============================================================================
// INTEGRATION TESTS
//=============================================================================

TEST_CASE("31500: Chart within page includes apexcharts CDN", "[chart][page][integration]") {
    html::page pg;

    chart::line_chart chart;
    chart.m_id = "page_chart";
    chart.add(10.0);

    pg << chart.html();

    std::string output = pg.html();

    // Should have apexcharts CDN link in head
    CHECK(output.find("cdn.jsdelivr.net/npm/apexcharts") != std::string::npos);
    // Should have chart div in body
    CHECK(output.find("page_chart") != std::string::npos);
}

TEST_CASE("31510: Multiple different chart types on same page", "[chart][page][integration]") {
    html::page pg;

    chart::line_chart line;
    line.m_id = "line1";
    line.add(10.0);

    chart::bar_chart bar;
    bar.m_id = "bar1";
    bar.add("A", 20.0);

    chart::timeseries_line_chart ts;
    ts.m_id = "ts1";
    ts.add(std::chrono::system_clock::now(), 30.0);

    pg << line.html() << bar.html() << ts.html();

    std::string output = pg.html();

    // All three charts should be present
    CHECK(output.find("line1") != std::string::npos);
    CHECK(output.find("bar1") != std::string::npos);
    CHECK(output.find("ts1") != std::string::npos);

    // Should have line, bar, and datetime in output
    CHECK(output.find("type: 'line'") != std::string::npos);
    CHECK(output.find("type: 'bar'") != std::string::npos);
    CHECK(output.find("type: 'datetime'") != std::string::npos);
}
