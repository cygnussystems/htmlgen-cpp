/*  ===================================================================
*                      HTML Generator Library - Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#include <catch2/catch_all.hpp>
#include "../include/html_tags.h"

using namespace html;

TEST_CASE("10000: Element basics", "[elements][basic]") {
    SECTION("default element is a container") {
        element e;
        CHECK(e.m_is_container == true);
    }
    SECTION("element has closing tag by default") {
        element e;
        CHECK(e.m_has_closing_tag == true);
    }
}

TEST_CASE("10010: Div element", "[elements][basic][div]") {
    SECTION("empty div") {
        html::div d;
        std::string html = d.html_string();
        CHECK(html.find("<div>") != std::string::npos);
        CHECK(html.find("</div>") != std::string::npos);
    }
    SECTION("div with content") {
        html::div d;
        d << text("Hello");
        std::string html = d.html_string();
        CHECK(html.find("Hello") != std::string::npos);
    }
}

TEST_CASE("10020: Span element", "[elements][basic][span]") {
    span s("test text");
    std::string html = s.html_string();
    CHECK(html.find("<span>test text</span>") != std::string::npos);
}

TEST_CASE("10030: Paragraph element", "[elements][basic][p]") {
    SECTION("empty paragraph") {
        p para;
        CHECK(para.html_string() == "<p></p>");
    }
    SECTION("paragraph with text") {
        p para("Hello World");
        CHECK(para.html_string() == "<p>Hello World</p>");
    }
}

TEST_CASE("10040: Heading elements", "[elements][basic][headings]") {
    SECTION("h1") {
        h1 heading("Title");
        std::string html = heading.html_string();
        CHECK(html.find("<h1>Title</h1>") != std::string::npos);
    }
    SECTION("h2") {
        h2 heading("Subtitle");
        std::string html = heading.html_string();
        CHECK(html.find("<h2>Subtitle</h2>") != std::string::npos);
    }
    SECTION("h3") {
        h3 heading("Section");
        std::string html = heading.html_string();
        CHECK(html.find("<h3>Section</h3>") != std::string::npos);
    }
    SECTION("h4 through h6") {
        h4 h4_("H4");
        h5 h5_("H5");
        h6 h6_("H6");
        CHECK(h4_.html_string().find("<h4>H4</h4>") != std::string::npos);
        CHECK(h5_.html_string().find("<h5>H5</h5>") != std::string::npos);
        CHECK(h6_.html_string().find("<h6>H6</h6>") != std::string::npos);
    }
}

TEST_CASE("10050: Text formatting elements", "[elements][basic][formatting]") {
    SECTION("em") {
        em e("emphasized");
        CHECK(e.html_string() == "<em>emphasized</em>");
    }
    SECTION("strong") {
        strong s("bold");
        CHECK(s.html_string() == "<strong>bold</strong>");
    }
    SECTION("small") {
        small_ s("small text");
        CHECK(s.html_string() == "<small>small text</small>");
    }
    SECTION("b") {
        b bold("bold");
        CHECK(bold.html_string() == "<b>bold</b>");
    }
}

TEST_CASE("10060: List elements", "[elements][basic][lists]") {
    SECTION("unordered list") {
        ul list(li("Item 1"), li("Item 2"));
        std::string html = list.html_string();
        CHECK(html.find("<ul>") != std::string::npos);
        CHECK(html.find("<li>Item 1</li>") != std::string::npos);
        CHECK(html.find("<li>Item 2</li>") != std::string::npos);
        CHECK(html.find("</ul>") != std::string::npos);
    }
    SECTION("ordered list") {
        ol list(li("First"), li("Second"));
        std::string html = list.html_string();
        CHECK(html.find("<ol>") != std::string::npos);
        CHECK(html.find("</ol>") != std::string::npos);
    }
}

TEST_CASE("10070: Container elements", "[elements][basic][container]") {
    SECTION("nav") {
        nav n;
        n << anchor("#", "Link");
        std::string html = n.html_string();
        CHECK(html.find("<nav>") != std::string::npos);
        CHECK(html.find("</nav>") != std::string::npos);
    }
}

TEST_CASE("10080: Element groups", "[elements][basic][groups]") {
    element_group group;
    group << p("Para 1") << p("Para 2");
    std::string html = group.html();
    CHECK(html.find("<p>Para 1</p>") != std::string::npos);
    CHECK(html.find("<p>Para 2</p>") != std::string::npos);
}

TEST_CASE("10085: Div with multiple children using variadic", "[elements][basic][div]") {
    html::div container(
        h1("Welcome"),
        p("Introduction text"),
        ul(li("First"), li("Second"), li("Third"))
    );
    std::string html = container.html_string();
    CHECK(html.find("<div>") != std::string::npos);
    CHECK(html.find("<h1>Welcome</h1>") != std::string::npos);
    CHECK(html.find("<p>Introduction text</p>") != std::string::npos);
    CHECK(html.find("<ul>") != std::string::npos);
}

TEST_CASE("10090: Element attributes", "[elements][basic][attributes]") {
    SECTION("id attribute") {
        html::div d;
        d.id("myDiv");
        CHECK(d.html_string().find("id=\"myDiv\"") != std::string::npos);
    }
    SECTION("class attribute") {
        html::div d;
        d.cl("container");
        CHECK(d.html_string().find("class=\"container\"") != std::string::npos);
    }
    SECTION("style attribute") {
        html::div d;
        d.style("color: red");
        CHECK(d.html_string().find("style=\"color: red\"") != std::string::npos);
    }
}

TEST_CASE("10100: Find elements by ID", "[elements][basic][find]") {
    html::div container;
    container.id("container");
    html::div child;
    child.id("child");
    container << child;

    CHECK(container.exists("child") == true);
    CHECK(container.exists("nonexistent") == false);
}

TEST_CASE("10110: Page generation", "[elements][basic][page]") {
    page p;
    p.head << title("Test Page");
    p << h1("Hello");

    std::string html = p.html();
    CHECK(html.find("<html>") != std::string::npos);
    CHECK(html.find("<head>") != std::string::npos);
    CHECK(html.find("<title>Test Page</title>") != std::string::npos);
    CHECK(html.find("<body>") != std::string::npos);
    CHECK(html.find("<h1>Hello</h1>") != std::string::npos);
}

TEST_CASE("10120: Link and image elements", "[elements][basic][media]") {
    SECTION("anchor") {
        anchor a("https://example.com", "Click here");
        std::string html = a.html_string();
        CHECK(html.find("href=\"https://example.com\"") != std::string::npos);
        CHECK(html.find("Click here") != std::string::npos);
    }
    SECTION("image") {
        img i("image.jpg", "100");
        std::string html = i.html_string();
        CHECK(html.find("src=\"image.jpg\"") != std::string::npos);
        CHECK(html.find("width=\"100\"") != std::string::npos);
    }
}

TEST_CASE("10130: Style and anchor elements", "[elements][basic][style]") {
    SECTION("style element") {
        style s("body { margin: 0; }");
        std::string html = s.html_string();
        CHECK(html.find("<style>") != std::string::npos);
        CHECK(html.find("body { margin: 0; }") != std::string::npos);
    }
}

TEST_CASE("10140: Variadic constructors", "[elements][basic][variadic]") {
    SECTION("div with multiple children") {
        auto d = html::div(h1("Title"), p("Paragraph"), span("Text"));
        std::string html = d.html_string();
        CHECK(html.find("<div>") != std::string::npos);
        CHECK(html.find("<h1>Title</h1>") != std::string::npos);
        CHECK(html.find("<p>Paragraph</p>") != std::string::npos);
        CHECK(html.find("<span>Text</span>") != std::string::npos);
    }
    SECTION("nested variadic constructors") {
        auto d = html::div(
            h1("Title"),
            ul(li("Item 1"), li("Item 2"), li("Item 3"))
        );
        std::string html = d.html_string();
        CHECK(html.find("<h1>Title</h1>") != std::string::npos);
        CHECK(html.find("<ul>") != std::string::npos);
        CHECK(html.find("<li>Item 1</li>") != std::string::npos);
        CHECK(html.find("<li>Item 2</li>") != std::string::npos);
        CHECK(html.find("<li>Item 3</li>") != std::string::npos);
    }
    SECTION("table with variadic constructors") {
        auto t = table(
            tr(th("Name"), th("Age")),
            tr(td("Alice"), td("28")),
            tr(td("Bob"), td("35"))
        );
        std::string html = t.html_string();
        CHECK(html.find("<table>") != std::string::npos);
        CHECK(html.find("Name") != std::string::npos);
        CHECK(html.find("Alice") != std::string::npos);
        CHECK(html.find("<tr>") != std::string::npos);
    }
    SECTION("semantic elements with variadic") {
        auto h = header(
            h1("Site Title"),
            nav(anchor("#", "Home"), anchor("/about", "About"))
        );
        std::string html = h.html_string();
        CHECK(html.find("<header>") != std::string::npos);
        CHECK(html.find("<h1>Site Title</h1>") != std::string::npos);
        CHECK(html.find("<nav>") != std::string::npos);
    }
    SECTION("chaining with variadic") {
        auto d = html::div(p("Para 1"), p("Para 2")).cl("container").id("main");
        std::string html = d.html_string();
        CHECK(html.find("class=\"container\"") != std::string::npos);
        CHECK(html.find("id=\"main\"") != std::string::npos);
    }
}
