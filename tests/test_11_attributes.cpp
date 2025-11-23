/*  ===================================================================
*                      HTML Generator Library - Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#include <catch2/catch_all.hpp>
#include "../include/html_tags.h"

using namespace html;

TEST_CASE("11050: HTML escape utility", "[utility][escape]") {
    SECTION("no escaping needed") {
        CHECK(html_escape("hello world") == "hello world");
    }
    SECTION("escape ampersand") {
        CHECK(html_escape("a & b") == "a &amp; b");
    }
    SECTION("escape less than") {
        CHECK(html_escape("a < b") == "a &lt; b");
    }
    SECTION("escape greater than") {
        CHECK(html_escape("a > b") == "a &gt; b");
    }
    SECTION("escape double quote") {
        CHECK(html_escape("say \"hello\"") == "say &quot;hello&quot;");
    }
    SECTION("escape single quote") {
        CHECK(html_escape("it's") == "it&#39;s");
    }
    SECTION("multiple escapes") {
        CHECK(html_escape("<script>alert('xss')</script>") ==
              "&lt;script&gt;alert(&#39;xss&#39;)&lt;/script&gt;");
    }
}

TEST_CASE("11060: Data attributes", "[attributes][data]") {
    html::div d;
    d.data("id", "123").data("name", "test");
    std::string result = d.html_string();
    CHECK(result.find("data-id=\"123\"") != std::string::npos);
    CHECK(result.find("data-name=\"test\"") != std::string::npos);
}

TEST_CASE("11070: ARIA attributes", "[attributes][aria]") {
    SECTION("aria-label") {
        button b("Close");
        b.aria_label("Close dialog");
        std::string html = b.html_string();
        CHECK(html.find("aria-label=\"Close dialog\"") != std::string::npos);
    }
    SECTION("aria-hidden") {
        html::div d;
        d.aria_hidden(true);
        std::string result = d.html_string();
        CHECK(result.find("aria-hidden=\"true\"") != std::string::npos);
    }
    SECTION("aria-expanded") {
        button b;
        b.aria_expanded(false);
        std::string html = b.html_string();
        CHECK(html.find("aria-expanded=\"false\"") != std::string::npos);
    }
    SECTION("aria-controls") {
        button b;
        b.aria_controls("menu1");
        std::string html = b.html_string();
        CHECK(html.find("aria-controls=\"menu1\"") != std::string::npos);
    }
    SECTION("aria-labelledby") {
        html::div d;
        d.aria_labelledby("title1");
        std::string html = d.html_string();
        CHECK(html.find("aria-labelledby=\"title1\"") != std::string::npos);
    }
    SECTION("aria-describedby") {
        html::div d;
        d.aria_describedby("desc1");
        std::string html = d.html_string();
        CHECK(html.find("aria-describedby=\"desc1\"") != std::string::npos);
    }
}

TEST_CASE("11080: Global attributes", "[attributes][global]") {
    SECTION("hidden") {
        html::div d;
        d.hidden();
        std::string result = d.html_string();
        CHECK(result.find("hidden=\"hidden\"") != std::string::npos);
    }
    SECTION("contenteditable") {
        html::div d;
        d.contenteditable(true);
        std::string result = d.html_string();
        CHECK(result.find("contenteditable=\"true\"") != std::string::npos);
    }
    SECTION("tabindex") {
        html::div d;
        d.tabindex(0);
        std::string result = d.html_string();
        CHECK(result.find("tabindex=\"0\"") != std::string::npos);
    }
    SECTION("title") {
        html::div d;
        d.title("Tooltip text");
        std::string result = d.html_string();
        CHECK(result.find("title=\"Tooltip text\"") != std::string::npos);
    }
    SECTION("lang") {
        html::div d;
        d.lang("en-US");
        std::string result = d.html_string();
        CHECK(result.find("lang=\"en-US\"") != std::string::npos);
    }
    SECTION("dir") {
        html::div d;
        d.dir("rtl");
        std::string result = d.html_string();
        CHECK(result.find("dir=\"rtl\"") != std::string::npos);
    }
    SECTION("draggable") {
        html::div d;
        d.draggable(true);
        std::string result = d.html_string();
        CHECK(result.find("draggable=\"true\"") != std::string::npos);
    }
    SECTION("spellcheck") {
        html::div d;
        d.spellcheck(false);
        std::string result = d.html_string();
        CHECK(result.find("spellcheck=\"false\"") != std::string::npos);
    }
}
