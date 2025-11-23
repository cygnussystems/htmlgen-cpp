/*  ===================================================================
*                      HTML Generator Library - Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#include <catch2/catch_all.hpp>
#include "../include/html_tags.h"

using namespace html;

TEST_CASE("22000: Header element", "[elements][semantic]") {
    header h;
    h << h1("Site Title");
    std::string html = h.html_string();
    CHECK(html.find("<header>") != std::string::npos);
    CHECK(html.find("</header>") != std::string::npos);
    CHECK(html.find("<h1>Site Title</h1>") != std::string::npos);
}

TEST_CASE("22010: Footer element", "[elements][semantic]") {
    footer f;
    f << p("Copyright 2024");
    std::string html = f.html_string();
    CHECK(html.find("<footer>") != std::string::npos);
    CHECK(html.find("</footer>") != std::string::npos);
}

TEST_CASE("22020: Section element", "[elements][semantic]") {
    section s;
    s << h2("Section Title");
    std::string html = s.html_string();
    CHECK(html.find("<section>") != std::string::npos);
    CHECK(html.find("</section>") != std::string::npos);
}

TEST_CASE("22030: Article element", "[elements][semantic]") {
    article a;
    a << h2("Article Title") << p("Content");
    std::string html = a.html_string();
    CHECK(html.find("<article>") != std::string::npos);
    CHECK(html.find("</article>") != std::string::npos);
}

TEST_CASE("22040: Aside element", "[elements][semantic]") {
    aside a;
    a << p("Sidebar content");
    std::string html = a.html_string();
    CHECK(html.find("<aside>") != std::string::npos);
    CHECK(html.find("</aside>") != std::string::npos);
}

TEST_CASE("22050: Main element", "[elements][semantic]") {
    main m;
    m << p("Main content");
    std::string html = m.html_string();
    CHECK(html.find("<main>") != std::string::npos);
    CHECK(html.find("</main>") != std::string::npos);
}

TEST_CASE("22060: Details and summary", "[elements][semantic][interactive]") {
    SECTION("closed details") {
        details d;
        d << summary("Click to expand") << p("Hidden content");
        std::string html = d.html_string();
        CHECK(html.find("<details>") != std::string::npos);
        CHECK(html.find("<summary>Click to expand</summary>") != std::string::npos);
        CHECK(html.find("Hidden content") != std::string::npos);
    }
    SECTION("open details") {
        details d;
        d.open();
        d << summary("Expanded") << p("Visible content");
        std::string html = d.html_string();
        CHECK(html.find("open=\"open\"") != std::string::npos);
    }
}

TEST_CASE("22070: Dialog element", "[elements][semantic][interactive]") {
    dialog dlg;
    dlg.open();
    dlg << p("Dialog content");
    std::string html = dlg.html_string();
    CHECK(html.find("<dialog") != std::string::npos);
    CHECK(html.find("open=\"open\"") != std::string::npos);
    CHECK(html.find("</dialog>") != std::string::npos);
}

TEST_CASE("22080: Template element", "[elements][semantic][interactive]") {
    template_ t;
    t << html::div().cl("template-content");
    std::string result = t.html_string();
    CHECK(result.find("<template>") != std::string::npos);
    CHECK(result.find("</template>") != std::string::npos);
}

TEST_CASE("22090: Figure and figcaption", "[elements][semantic]") {
    figure fig;
    fig << img("image.jpg") << figcaption("Image caption");
    std::string html = fig.html_string();
    CHECK(html.find("<figure>") != std::string::npos);
    CHECK(html.find("<figcaption>Image caption</figcaption>") != std::string::npos);
    CHECK(html.find("</figure>") != std::string::npos);
}

TEST_CASE("22100: Time element", "[elements][semantic]") {
    time_ t("November 23, 2024");
    t.datetime("2024-11-23");
    std::string html = t.html_string();
    CHECK(html.find("<time") != std::string::npos);
    CHECK(html.find("datetime=\"2024-11-23\"") != std::string::npos);
    CHECK(html.find("November 23, 2024") != std::string::npos);
}

TEST_CASE("22110: Mark element", "[elements][semantic]") {
    mark m("highlighted text");
    std::string html = m.html_string();
    CHECK(html.find("<mark>highlighted text</mark>") != std::string::npos);
}

TEST_CASE("22120: Code and pre elements", "[elements][semantic]") {
    SECTION("code") {
        code c("console.log('hello')");
        std::string html = c.html_string();
        CHECK(html.find("<code>console.log('hello')</code>") != std::string::npos);
    }
    SECTION("pre") {
        pre p("line 1\nline 2");
        std::string html = p.html_string();
        CHECK(html.find("<pre>") != std::string::npos);
        CHECK(html.find("</pre>") != std::string::npos);
    }
    SECTION("pre with code") {
        pre p;
        p << code("function() { return 42; }");
        std::string html = p.html_string();
        CHECK(html.find("<pre>") != std::string::npos);
        CHECK(html.find("<code>") != std::string::npos);
    }
}

TEST_CASE("22130: Technical text elements", "[elements][semantic]") {
    SECTION("kbd") {
        kbd k("Ctrl+C");
        CHECK(k.html_string() == "<kbd>Ctrl+C</kbd>");
    }
    SECTION("samp") {
        samp s("Output text");
        CHECK(s.html_string() == "<samp>Output text</samp>");
    }
    SECTION("var") {
        var v("x");
        CHECK(v.html_string() == "<var>x</var>");
    }
}

TEST_CASE("22140: Quotation elements", "[elements][semantic]") {
    SECTION("blockquote") {
        blockquote bq("Famous quote");
        bq.cite("https://example.com");
        std::string html = bq.html_string();
        CHECK(html.find("<blockquote") != std::string::npos);
        CHECK(html.find("cite=\"https://example.com\"") != std::string::npos);
    }
    SECTION("q") {
        q quote("inline quote");
        std::string html = quote.html_string();
        CHECK(html.find("<q>inline quote</q>") != std::string::npos);
    }
}

TEST_CASE("22150: Abbreviation element", "[elements][semantic]") {
    abbr a("HTML");
    a.title("HyperText Markup Language");
    std::string html = a.html_string();
    CHECK(html.find("<abbr") != std::string::npos);
    CHECK(html.find("title=\"HyperText Markup Language\"") != std::string::npos);
}

TEST_CASE("22160: Subscript and superscript", "[elements][semantic]") {
    SECTION("sub") {
        sub s("2");
        CHECK(s.html_string() == "<sub>2</sub>");
    }
    SECTION("sup") {
        sup s("2");
        CHECK(s.html_string() == "<sup>2</sup>");
    }
}

TEST_CASE("22170: Ins and del elements", "[elements][semantic]") {
    SECTION("ins") {
        ins i("new text");
        i.datetime("2024-01-01");
        std::string html = i.html_string();
        CHECK(html.find("<ins") != std::string::npos);
        CHECK(html.find("datetime=\"2024-01-01\"") != std::string::npos);
    }
    SECTION("del") {
        del d("old text");
        std::string html = d.html_string();
        CHECK(html.find("<del>old text</del>") != std::string::npos);
    }
}

TEST_CASE("22180: S and u elements", "[elements][semantic]") {
    SECTION("s") {
        s strike("strikethrough");
        CHECK(strike.html_string() == "<s>strikethrough</s>");
    }
    SECTION("u") {
        u underline("underlined");
        CHECK(underline.html_string() == "<u>underlined</u>");
    }
}

TEST_CASE("22190: Address element", "[elements][semantic]") {
    address addr;
    addr << text("Contact us at info@example.com");
    std::string html = addr.html_string();
    CHECK(html.find("<address>") != std::string::npos);
    CHECK(html.find("</address>") != std::string::npos);
}
