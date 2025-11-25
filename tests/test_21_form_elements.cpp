/*  ===================================================================
*                      HTML Generator Library - Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#include <catch2/catch_all.hpp>
#include "../include/html_gen.h"

using namespace html;

TEST_CASE("21000: Form element", "[elements][form]") {
    SECTION("empty form") {
        form f;
        CHECK(f.html_string() == "<form>\n</form>\n");
    }
    SECTION("form with action and method") {
        form f;
        f.action("/submit").method("POST");
        std::string html = f.html_string();
        CHECK(html.find("action=\"/submit\"") != std::string::npos);
        CHECK(html.find("method=\"POST\"") != std::string::npos);
    }
}

TEST_CASE("21010: Input element", "[elements][form][input]") {
    SECTION("empty input") {
        input i;
        CHECK(i.html_string() == "<input>");
    }
    SECTION("text input with attributes") {
        input i;
        i.type("text");
        i.name("username").id("user_id");
        std::string html = i.html_string();
        CHECK(html.find("type=\"text\"") != std::string::npos);
        CHECK(html.find("name=\"username\"") != std::string::npos);
        CHECK(html.find("id=\"user_id\"") != std::string::npos);
    }
    SECTION("input with boolean attributes") {
        input i;
        i.type("checkbox");
        i.required().disabled().checked();
        std::string html = i.html_string();
        CHECK(html.find("required=\"required\"") != std::string::npos);
        CHECK(html.find("disabled=\"disabled\"") != std::string::npos);
        CHECK(html.find("checked=\"checked\"") != std::string::npos);
    }
    SECTION("input with placeholder and value") {
        input i;
        i.placeholder("Enter text").value("default");
        std::string html = i.html_string();
        CHECK(html.find("placeholder=\"Enter text\"") != std::string::npos);
        CHECK(html.find("value=\"default\"") != std::string::npos);
    }
}

TEST_CASE("21020: Button element", "[elements][form][button]") {
    SECTION("empty button") {
        button b;
        CHECK(b.html_string() == "<button></button>");
    }
    SECTION("button with text") {
        button b("Submit");
        CHECK(b.html_string() == "<button>Submit</button>");
    }
    SECTION("button with attributes") {
        button b("Click");
        b.type("submit");
        b.name("btn").disabled();
        std::string html = b.html_string();
        CHECK(html.find("type=\"submit\"") != std::string::npos);
        CHECK(html.find("name=\"btn\"") != std::string::npos);
        CHECK(html.find("disabled=\"disabled\"") != std::string::npos);
    }
}

TEST_CASE("21030: Select and option elements", "[elements][form][select]") {
    SECTION("empty select") {
        select s;
        CHECK(s.html_string() == "<select>\n</select>");
    }
    SECTION("select with options") {
        select s;
        s.name("country");
        s << option("us", "United States")
          << option("ca", "Canada").selected();
        std::string html = s.html_string();
        CHECK(html.find("name=\"country\"") != std::string::npos);
        CHECK(html.find("value=\"us\"") != std::string::npos);
        CHECK(html.find("United States") != std::string::npos);
        CHECK(html.find("selected=\"selected\"") != std::string::npos);
    }
    SECTION("select with multiple and required") {
        select s;
        s.multiple().required();
        std::string html = s.html_string();
        CHECK(html.find("multiple=\"multiple\"") != std::string::npos);
        CHECK(html.find("required=\"required\"") != std::string::npos);
    }
}

TEST_CASE("21040: Label element", "[elements][form][label]") {
    SECTION("label with text") {
        label l("Username:");
        CHECK(l.html_string() == "<label>Username:</label>");
    }
    SECTION("label with for attribute") {
        label l("Email:");
        l.for_id("email_input");
        std::string html = l.html_string();
        CHECK(html.find("for=\"email_input\"") != std::string::npos);
    }
}

TEST_CASE("21050: Fieldset and legend", "[elements][form][fieldset]") {
    SECTION("fieldset with legend") {
        fieldset fs;
        input name_input;
        name_input.type("text");
        name_input.name("name").id("name");
        fs << legend("Personal Info")
           << label("Name:").for_id("name")
           << name_input;
        std::string html = fs.html_string();
        CHECK(html.find("<fieldset>") != std::string::npos);
        CHECK(html.find("<legend>Personal Info</legend>") != std::string::npos);
        CHECK(html.find("</fieldset>") != std::string::npos);
    }
}

TEST_CASE("21060: Datalist element", "[elements][form][datalist]") {
    datalist dl;
    dl.id("browsers");
    dl << option("Chrome") << option("Firefox") << option("Safari");
    std::string html = dl.html_string();
    CHECK(html.find("<datalist") != std::string::npos);
    CHECK(html.find("id=\"browsers\"") != std::string::npos);
    CHECK(html.find("</datalist>") != std::string::npos);
}

TEST_CASE("21070: Output element", "[elements][form][output]") {
    output o;
    o.name("result").for_id("a b");
    std::string html = o.html_string();
    CHECK(html.find("<output") != std::string::npos);
    CHECK(html.find("name=\"result\"") != std::string::npos);
    CHECK(html.find("for=\"a b\"") != std::string::npos);
}

TEST_CASE("21080: Optgroup element", "[elements][form][optgroup]") {
    select sel;
    optgroup og;
    og.label("Swedish Cars");
    og << option("volvo", "Volvo") << option("saab", "Saab");
    sel << og;
    std::string html = sel.html_string();
    CHECK(html.find("<optgroup") != std::string::npos);
    CHECK(html.find("label=\"Swedish Cars\"") != std::string::npos);
}

TEST_CASE("21090: Progress element", "[elements][form][progress]") {
    progress prog;
    prog.value(70).max(100);
    std::string html = prog.html_string();
    CHECK(html.find("<progress") != std::string::npos);
    CHECK(html.find("value=\"70") != std::string::npos);
    CHECK(html.find("max=\"100") != std::string::npos);
}

TEST_CASE("21100: Meter element", "[elements][form][meter]") {
    meter m;
    m.value(0.6).min(0).max(1).low(0.3).high(0.7).optimum(0.5);
    std::string html = m.html_string();
    CHECK(html.find("<meter") != std::string::npos);
    CHECK(html.find("value=\"0.6") != std::string::npos);
    CHECK(html.find("low=\"0.3") != std::string::npos);
    CHECK(html.find("high=\"0.7") != std::string::npos);
}
