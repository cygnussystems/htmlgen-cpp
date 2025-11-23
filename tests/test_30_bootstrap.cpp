/*  ===================================================================
*                      HTML Generator Library - Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#include <catch2/catch_all.hpp>
#include "../include/html_tags.h"
#include "../include/bootstrap.h"

namespace bs = web::html::bootstrap;

TEST_CASE("30000: Bootstrap container", "[bootstrap][container]") {
    bs::container c;
    std::string html = c.html_string();
    CHECK(html.find("class=\"container\"") != std::string::npos);
}

TEST_CASE("30010: Bootstrap row", "[bootstrap][row]") {
    bs::row r;
    std::string html = r.html_string();
    CHECK(html.find("class=\"row clearfix\"") != std::string::npos);
}

TEST_CASE("30020: Bootstrap column", "[bootstrap][column]") {
    SECTION("column with size") {
        bs::column c(6);
        std::string html = c.html_string();
        CHECK(html.find("class=\"column col-md-6\"") != std::string::npos);
    }
}

TEST_CASE("30030: Bootstrap grid layout", "[bootstrap][grid]") {
    bs::container cont;
    bs::row r;
    r << bs::column(4) << bs::column(4) << bs::column(4);
    cont << r;

    std::string html = cont.html_string();
    CHECK(html.find("class=\"container\"") != std::string::npos);
    CHECK(html.find("class=\"row clearfix\"") != std::string::npos);
    CHECK(html.find("class=\"column col-md-4\"") != std::string::npos);
}
