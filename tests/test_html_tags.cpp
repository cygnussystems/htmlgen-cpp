/*  ===================================================================
*                      HTML Generator Library - Unit Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#include <catch2/catch_test_macros.hpp>
#include "../include/html_tags.h"
#include "../include/bootstrap.h"

#include <iostream>
#include <sstream>

using namespace web::html;

TEST_CASE("Element basics", "[element]") {
    h1 tag("some content");
    CHECK(tag[0].html_string() == "some content");
    CHECK(tag.html_content_string() == "some content");
    tag.content("content 2").id("test_id");
    CHECK(tag.id() == "test_id");
    CHECK(tag[0].html_string() == "content 2");

    CHECK(tag.size() == 1);
    CHECK_THROWS(tag[2]);

    tag << "add content";
    CHECK(tag.size() == 2);
    tag << "add content";
    CHECK(tag.size() == 3);

    tag.clear();
    tag << "replace content";
    CHECK(tag.size() == 1);
    CHECK(tag[0].html_string() == "replace content");
}

TEST_CASE("Element attributes", "[element][attributes]") {
    h1 tag("test");

    tag.id("id");
    CHECK(tag.id() == "id");

    tag.cl("cl");
    CHECK(tag.cl() == "cl");

    tag.src("src");
    CHECK(tag.src() == "src");

    tag.type("type");
    CHECK(tag.type() == "type");

    tag.width("width");
    CHECK(tag.width() == "width");

    tag.height("height");
    CHECK(tag.height() == "height");

    tag.alt("alt");
    CHECK(tag.alt() == "alt");

    tag.style("style");
    CHECK(tag.style() == "style");

    tag.add_attr("other", "100");
    tag.add(attr("other2", "200"));

    SECTION("clear() preserves attributes") {
        tag.clear();
        CHECK(tag.size() == 0);

        CHECK(tag.id() == "id");
        CHECK(tag.cl() == "cl");
        CHECK(tag.src() == "src");
        CHECK(tag.type() == "type");
        CHECK(tag.width() == "width");
        CHECK(tag.height() == "height");
        CHECK(tag.alt() == "alt");
        CHECK(tag.style() == "style");
        CHECK(tag.attr() != "");
    }

    SECTION("clear_all() removes attributes") {
        tag.clear_all();

        CHECK(tag.id() == "");
        CHECK(tag.cl() == "");
        CHECK(tag.src() == "");
        CHECK(tag.type() == "");
        CHECK(tag.width() == "");
        CHECK(tag.height() == "");
        CHECK(tag.alt() == "");
        CHECK(tag.style() == "");
        CHECK(tag.attr() == "");
    }
}

TEST_CASE("Element groups", "[element_group]") {
    h1 tag2("t2"), tag3("t3");
    CHECK(tag2.size() == 1);
    CHECK(tag3.size() == 1);

    element_group ag1;

    ag1.add(tag2);
    ag1.add(tag3);
    CHECK(ag1.size() == 2);
    CHECK(ag1[0][0].html_string() == "t2");
    CHECK(ag1[1][0].html_string() == "t3");
    CHECK(ag1[0].html_content_string() == "t2");
    CHECK(ag1[1].html_content_string() == "t3");

    element_group ag2(ag1);
    // Copy constructor does not copy, but GRABS content
    CHECK(ag2.size() == 2);
    CHECK(ag1.size() == 0); // content was taken
}

TEST_CASE("Paragraph element", "[elements][p]") {
    p tag("test-string");
    std::string s = tag.html_string();
    CHECK(s == "<p>test-string</p>");
}

TEST_CASE("Heading elements", "[elements][headings]") {
    SECTION("h1") {
        h1 tag("test-string");
        CHECK(tag.html_string() == "<h1>test-string</h1>\n");
    }
    SECTION("h2") {
        h2 tag("test-string");
        CHECK(tag.html_string() == "<h2>test-string</h2>\n");
    }
    SECTION("h3") {
        h3 tag("test-string");
        CHECK(tag.html_string() == "<h3>test-string</h3>\n");
    }
    SECTION("h4") {
        h4 tag("test-string");
        CHECK(tag.html_string() == "<h4>test-string</h4>\n");
    }
    SECTION("h5") {
        h5 tag("test-string");
        CHECK(tag.html_string() == "<h5>test-string</h5>\n");
    }
    SECTION("h6") {
        h6 tag("test-string");
        CHECK(tag.html_string() == "<h6>test-string</h6>\n");
    }
}

TEST_CASE("Text formatting elements", "[elements][formatting]") {
    SECTION("strong") {
        strong tag("test-string");
        CHECK(tag.html_string() == "<strong>test-string</strong>");
    }
    SECTION("small") {
        small_ tag("test-string");
        CHECK(tag.html_string() == "<small>test-string</small>");
    }
    SECTION("em") {
        em tag("test-string");
        CHECK(tag.html_string() == "<em>test-string</em>");
    }
}

TEST_CASE("Container elements", "[elements][containers]") {
    SECTION("div") {
        web::html::div tag;
        CHECK(tag.html_string() == "<div>\n</div>\n");
    }
    SECTION("nav") {
        nav tag;
        CHECK(tag.html_string() == "<nav>\n</nav>\n");
    }
}

TEST_CASE("List elements", "[elements][lists]") {
    SECTION("ol") {
        ol tag;
        CHECK(tag.html_string() == "<ol>\n</ol>\n");
    }
    SECTION("ul") {
        ul tag;
        CHECK(tag.html_string() == "<ul>\n</ul>\n");
    }
    SECTION("li") {
        li tag("test-string");
        CHECK(tag.html_string() == "<li>test-string</li>\n");
    }
}

TEST_CASE("Table elements", "[elements][table]") {
    SECTION("table") {
        web::html::table tag;
        CHECK(tag.html_string() == "<table>\n</table>\n");
    }
    SECTION("tr") {
        tr tag;
        CHECK(tag.html_string() == "<tr>\n</tr>\n");
    }
    SECTION("td") {
        td tag("test-string");
        CHECK(tag.html_string() == "<td>test-string</td>\n");
    }
}

TEST_CASE("Style and anchor elements", "[elements]") {
    SECTION("style") {
        style tag("test-string");
        CHECK(tag.html_string() == "<style>test-string</style>\n");
    }
    SECTION("anchor") {
        anchor tag("test-string");
        CHECK(tag.html_string() == "<a href=\"test-string\"></a>");
    }
}

TEST_CASE("Link and image elements", "[elements]") {
    SECTION("link") {
        link tag;
        CHECK(tag.html_string() == "<link>\n");
    }
    SECTION("img empty") {
        img tag;
        CHECK(tag.html_string() == "<img>\n");
    }
    SECTION("img with src") {
        img tag("img-src");
        CHECK(tag.html_string() == "<img src=\"img-src\">\n");
    }
    SECTION("img with src, width, and alt") {
        img i("my_img.jpg", "50%");
        i.alt("alt-text");
        CHECK(i.html_string() == "<img src=\"my_img.jpg\" alt=\"alt-text\" width=\"50%\">\n");
    }
}

TEST_CASE("Find elements by ID", "[element][find]") {
    span s;
    CHECK(s.empty());

    s << span("content").id("le1_a");

    CHECK_FALSE(s.empty());
    CHECK(s.exists("le1_a"));

    s << span("content").id("le1_b");
    CHECK(s.exists("le1_b"));

    s << span("content").id("le1_c");
    CHECK(s.exists("le1_c"));

    s << span("content").id("le1_d");
    CHECK(s.exists("le1_d"));

    s.get("le1_c") << span().id("le2_a") << span().id("le2_b");

    s.get("le2_b") << text("treasure-content").id("treasure");

    element* pele2_a = s.find("le2_a");
    REQUIRE(pele2_a != nullptr);
    CHECK(pele2_a->id() == std::string("le2_a"));

    element* petreasure = s.find("treasure");
    REQUIRE(petreasure != nullptr);
    CHECK(petreasure->id() == "treasure");

    element& ele2_b = s.get("le2_b");
    CHECK(ele2_b.id() == "le2_b");

    element& etreasure = s.get("treasure");
    CHECK(etreasure.id() == "treasure");

    std::string content_str = etreasure.html_content_string();
    CHECK(content_str == "treasure-content");
}

TEST_CASE("Page generation", "[page]") {
    page pg;
    h1 tag("test title");
    pg << tag;
    pg.add(tag.id("h1_a").content("reset title"));
    pg.add(br());

    element& e = pg.add(h1("another h1 title"));
    e.add("added text.");
    e.id("test");

    std::ostringstream ss;
    ss << pg;
    std::string output = ss.str();

    CHECK(output.find("<!DOCTYPE html>") != std::string::npos);
    CHECK(output.find("<html>") != std::string::npos);
    CHECK(output.find("<body>") != std::string::npos);
    CHECK(output.find("</body>") != std::string::npos);
    CHECK(output.find("</html>") != std::string::npos);
}

////////////////////////////////////////////////////////////////////////////////////
// New Tests for Modernized Library
////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("HTML escape utility", "[escape][security]") {
    SECTION("escapes angle brackets") {
        CHECK(html_escape("<script>") == "&lt;script&gt;");
    }
    SECTION("escapes ampersand") {
        CHECK(html_escape("a & b") == "a &amp; b");
    }
    SECTION("escapes quotes") {
        CHECK(html_escape("\"quoted\"") == "&quot;quoted&quot;");
        CHECK(html_escape("it's") == "it&#39;s");
    }
    SECTION("mixed content") {
        CHECK(html_escape("<div class=\"test\">a & b</div>") ==
              "&lt;div class=&quot;test&quot;&gt;a &amp; b&lt;/div&gt;");
    }
    SECTION("empty string") {
        CHECK(html_escape("") == "");
    }
    SECTION("no escaping needed") {
        CHECK(html_escape("hello world") == "hello world");
    }
}

TEST_CASE("Form element", "[elements][form]") {
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

TEST_CASE("Input element", "[elements][form][input]") {
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

TEST_CASE("Button element", "[elements][form][button]") {
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

TEST_CASE("Select and option elements", "[elements][form][select]") {
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

TEST_CASE("Label element", "[elements][form][label]") {
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

TEST_CASE("Fieldset and legend", "[elements][form][fieldset]") {
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

TEST_CASE("Header element", "[elements][semantic]") {
    header h;
    h << h1("Site Title");
    std::string html = h.html_string();
    CHECK(html.find("<header>") != std::string::npos);
    CHECK(html.find("</header>") != std::string::npos);
    CHECK(html.find("<h1>Site Title</h1>") != std::string::npos);
}

TEST_CASE("Footer element", "[elements][semantic]") {
    footer f;
    f << p("Copyright 2024");
    std::string html = f.html_string();
    CHECK(html.find("<footer>") != std::string::npos);
    CHECK(html.find("</footer>") != std::string::npos);
}

TEST_CASE("Section element", "[elements][semantic]") {
    section s;
    s << h2("Section Title");
    std::string html = s.html_string();
    CHECK(html.find("<section>") != std::string::npos);
    CHECK(html.find("</section>") != std::string::npos);
}

TEST_CASE("Article element", "[elements][semantic]") {
    article a;
    a << h2("Article Title") << p("Content");
    std::string html = a.html_string();
    CHECK(html.find("<article>") != std::string::npos);
    CHECK(html.find("</article>") != std::string::npos);
}

TEST_CASE("Aside element", "[elements][semantic]") {
    aside a;
    a << p("Sidebar content");
    std::string html = a.html_string();
    CHECK(html.find("<aside>") != std::string::npos);
    CHECK(html.find("</aside>") != std::string::npos);
}

TEST_CASE("Main element", "[elements][semantic]") {
    web::html::main m;
    m << article();
    std::string html = m.html_string();
    CHECK(html.find("<main>") != std::string::npos);
    CHECK(html.find("</main>") != std::string::npos);
}

TEST_CASE("Video element", "[elements][media]") {
    SECTION("empty video") {
        video v;
        CHECK(v.html_string() == "<video>\n</video>\n");
    }
    SECTION("video with attributes") {
        video v;
        v.controls().autoplay().loop().muted();
        v.width("640").height("480");
        std::string html = v.html_string();
        CHECK(html.find("controls=\"controls\"") != std::string::npos);
        CHECK(html.find("autoplay=\"autoplay\"") != std::string::npos);
        CHECK(html.find("loop=\"loop\"") != std::string::npos);
        CHECK(html.find("muted=\"muted\"") != std::string::npos);
    }
    SECTION("video with poster") {
        video v;
        v.poster("thumbnail.jpg");
        std::string html = v.html_string();
        CHECK(html.find("poster=\"thumbnail.jpg\"") != std::string::npos);
    }
    SECTION("video with source") {
        video v;
        v.controls();
        v << source("movie.mp4", "video/mp4");
        std::string html = v.html_string();
        CHECK(html.find("src=\"movie.mp4\"") != std::string::npos);
        CHECK(html.find("type=\"video/mp4\"") != std::string::npos);
    }
}

TEST_CASE("Audio element", "[elements][media]") {
    SECTION("empty audio") {
        audio a;
        CHECK(a.html_string() == "<audio>\n</audio>\n");
    }
    SECTION("audio with controls") {
        audio a;
        a.controls().autoplay();
        std::string html = a.html_string();
        CHECK(html.find("controls=\"controls\"") != std::string::npos);
        CHECK(html.find("autoplay=\"autoplay\"") != std::string::npos);
    }
    SECTION("audio with source") {
        audio a;
        a.controls();
        a << source("audio.mp3", "audio/mpeg");
        std::string html = a.html_string();
        CHECK(html.find("src=\"audio.mp3\"") != std::string::npos);
        CHECK(html.find("type=\"audio/mpeg\"") != std::string::npos);
    }
}

TEST_CASE("Source element", "[elements][media]") {
    source s("video.webm", "video/webm");
    std::string html = s.html_string();
    CHECK(html.find("<source") != std::string::npos);
    CHECK(html.find("src=\"video.webm\"") != std::string::npos);
    CHECK(html.find("type=\"video/webm\"") != std::string::npos);
    // source is self-closing
    CHECK(html.find("</source>") == std::string::npos);
}

TEST_CASE("Bootstrap container", "[bootstrap]") {
    bootstrap::container c;
    std::string html = c.html_string();
    CHECK(html.find("class=\"container\"") != std::string::npos);
}

TEST_CASE("Bootstrap row", "[bootstrap]") {
    bootstrap::row r;
    std::string html = r.html_string();
    CHECK(html.find("class=\"row clearfix\"") != std::string::npos);
}

TEST_CASE("Bootstrap column", "[bootstrap]") {
    bootstrap::column c(6);
    std::string html = c.html_string();
    CHECK(html.find("class=\"column col-md-6\"") != std::string::npos);
}

TEST_CASE("Bootstrap grid layout", "[bootstrap]") {
    bootstrap::container cont;
    cont << (bootstrap::row()
            << bootstrap::column(6).id("left")
            << bootstrap::column(6).id("right"));
    std::string html = cont.html_string();
    CHECK(html.find("class=\"container\"") != std::string::npos);
    CHECK(html.find("class=\"row clearfix\"") != std::string::npos);
    CHECK(html.find("col-md-6") != std::string::npos);
    CHECK(html.find("id=\"left\"") != std::string::npos);
    CHECK(html.find("id=\"right\"") != std::string::npos);
}

TEST_CASE("Line chart", "[chart]") {
    web::chart::line_chart chart;
    chart.m_sID = "test_chart";
    chart.m_sDataName = "values";
    chart.m_sColor = "#ff0000";
    chart.add(10.0);
    chart.add(20.0);
    chart.add(15.0);

    std::string html = chart.html();
    CHECK(html.find("test_chart") != std::string::npos);
    CHECK(html.find("c3.generate") != std::string::npos);
    CHECK(html.find("#ff0000") != std::string::npos);
}

TEST_CASE("Bar chart", "[chart]") {
    web::chart::bar_chart chart;
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
