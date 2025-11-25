/*  ===================================================================
*                      HTML Generator Library - Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#include <catch2/catch_all.hpp>
#include "../include/html_gen.h"

using namespace html;

TEST_CASE("20000: Table elements", "[elements][table]") {
    SECTION("basic table") {
        table t;
        t << tr(td("Cell 1"), td("Cell 2"));
        std::string html = t.html_string();
        CHECK(html.find("<table>") != std::string::npos);
        CHECK(html.find("<tr>") != std::string::npos);
        CHECK(html.find("<td>Cell 1</td>") != std::string::npos);
        CHECK(html.find("</table>") != std::string::npos);
    }
}

TEST_CASE("20010: Table colspan and rowspan", "[elements][table]") {
    SECTION("td colspan") {
        td cell("Header");
        cell.colspan(3);
        std::string html = cell.html_string();
        CHECK(html.find("colspan=\"3\"") != std::string::npos);
    }
    SECTION("td rowspan") {
        td cell("Left");
        cell.rowspan(2);
        std::string html = cell.html_string();
        CHECK(html.find("rowspan=\"2\"") != std::string::npos);
    }
}

TEST_CASE("20020: Table header elements", "[elements][table][th]") {
    SECTION("th scope") {
        th header("Name");
        header.scope("col");
        std::string html = header.html_string();
        CHECK(html.find("scope=\"col\"") != std::string::npos);
    }
    SECTION("th with text") {
        th header("Header Text");
        std::string html = header.html_string();
        CHECK(html.find("<th>") != std::string::npos);
        CHECK(html.find("Header Text") != std::string::npos);
    }
    SECTION("th colspan and rowspan") {
        th header("Merged");
        header.colspan(2).rowspan(3);
        std::string html = header.html_string();
        CHECK(html.find("colspan=\"2\"") != std::string::npos);
        CHECK(html.find("rowspan=\"3\"") != std::string::npos);
    }
    SECTION("th abbr") {
        th header("Population");
        header.abbr("Pop.");
        std::string html = header.html_string();
        CHECK(html.find("abbr=\"Pop.\"") != std::string::npos);
    }
}

TEST_CASE("20030: Colgroup and col", "[elements][table][colgroup]") {
    SECTION("colgroup with span") {
        colgroup cg;
        cg.span(3);
        std::string html = cg.html_string();
        CHECK(html.find("<colgroup") != std::string::npos);
        CHECK(html.find("span=\"3\"") != std::string::npos);
    }
    SECTION("col element") {
        col c;
        c.span(2).style("background-color: yellow");
        std::string html = c.html_string();
        CHECK(html.find("<col") != std::string::npos);
        CHECK(html.find("span=\"2\"") != std::string::npos);
    }
    SECTION("colgroup with col children") {
        colgroup cg;
        cg << col().style("width: 100px") << col().style("width: 200px");
        std::string html = cg.html_string();
        CHECK(html.find("<colgroup>") != std::string::npos);
        CHECK(html.find("<col") != std::string::npos);
    }
}

TEST_CASE("20040: Table sections", "[elements][table][sections]") {
    SECTION("thead") {
        thead th(tr(td("Header")));
        std::string html = th.html_string();
        CHECK(html.find("<thead>") != std::string::npos);
        CHECK(html.find("</thead>") != std::string::npos);
    }
    SECTION("tbody") {
        tbody tb(tr(td("Data")));
        std::string html = tb.html_string();
        CHECK(html.find("<tbody>") != std::string::npos);
        CHECK(html.find("</tbody>") != std::string::npos);
    }
    SECTION("tfoot") {
        tfoot tf(tr(td("Footer")));
        std::string html = tf.html_string();
        CHECK(html.find("<tfoot>") != std::string::npos);
        CHECK(html.find("</tfoot>") != std::string::npos);
    }
}
