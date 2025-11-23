/*  ===================================================================
*                      HTML Generator Library - Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#include <catch2/catch_all.hpp>
#include "../include/html_tags.h"
#include "../include/bootstrap.h"

TEST_CASE("31000: Line chart", "[chart][line]") {
    chart::line_chart chart;
    chart.m_sID = "test_chart";
    chart.m_sColor = "#ff0000";
    chart.add(10.0);
    chart.add(20.0);
    chart.add(15.0);

    std::string html = chart.html();
    CHECK(html.find("test_chart") != std::string::npos);
    CHECK(html.find("c3.generate") != std::string::npos);
    CHECK(html.find("#ff0000") != std::string::npos);
}

TEST_CASE("31010: Bar chart", "[chart][bar]") {
    chart::bar_chart chart;
    chart.m_sID = "bar_chart";
    chart.add("Jan", 100.0);
    chart.add("Feb", 150.0);
    chart.add("Mar", 120.0);

    std::string html = chart.html();
    CHECK(html.find("bar_chart") != std::string::npos);
    CHECK(html.find("c3.generate") != std::string::npos);
    CHECK(html.find("'Jan'") != std::string::npos);
    CHECK(html.find("'Feb'") != std::string::npos);
    CHECK(html.find("'Mar'") != std::string::npos);
}

TEST_CASE("31020: Timeseries line chart", "[chart][timeseries]") {
    chart::timeseries_line_chart chart;
    chart.m_sID = "ts_chart";
    chart.m_sColor = "#0000ff";

    auto now = std::chrono::system_clock::now();
    chart.add(now, 100.0);
    chart.add(now + std::chrono::hours(1), 110.0);
    chart.add(now + std::chrono::hours(2), 105.0);

    std::string html = chart.html();
    CHECK(html.find("ts_chart") != std::string::npos);
    CHECK(html.find("c3.generate") != std::string::npos);
    CHECK(html.find("timeseries") != std::string::npos);
}
