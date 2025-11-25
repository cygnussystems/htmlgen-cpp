/*  ===================================================================
*                      HTML Generator Library - Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*  Tests for fluent API method chaining and variadic constructors
*/

#include <catch2/catch_all.hpp>
#include "../include/html_gen.h"

using namespace html;

// ============================================================================
// Fluent Method Chaining Tests
// These tests verify that derived classes return the correct type from
// fluent methods, enabling proper chaining without breaking the chain.
// ============================================================================

TEST_CASE("12000: Input fluent method chaining", "[fluent][form][input]") {
    SECTION("complete input chain - the key use case") {
        // This is the primary use case we want to support:
        // input().type("email").name("foo").id("email").cl("form-control").required()
        input i;
        i.type("email").name("user_email").id("email_field").cl("form-control").required();

        std::string html = i.html_string();
        CHECK(html.find("type=\"email\"") != std::string::npos);
        CHECK(html.find("name=\"user_email\"") != std::string::npos);
        CHECK(html.find("id=\"email_field\"") != std::string::npos);
        CHECK(html.find("class=\"form-control\"") != std::string::npos);
        CHECK(html.find("required=\"required\"") != std::string::npos);
    }

    SECTION("all input-specific methods in chain") {
        input i;
        i.type("text")
         .name("username")
         .placeholder("Enter username")
         .value("default_val")
         .minlength(3)
         .maxlength(20)
         .pattern("[A-Za-z]+")
         .autocomplete("username")
         .required()
         .readonly()
         .cl("input-field")
         .id("user-input");

        std::string html = i.html_string();
        CHECK(html.find("minlength=\"3\"") != std::string::npos);
        CHECK(html.find("maxlength=\"20\"") != std::string::npos);
        CHECK(html.find("pattern=\"[A-Za-z]+\"") != std::string::npos);
        CHECK(html.find("autocomplete=\"username\"") != std::string::npos);
        CHECK(html.find("readonly=\"readonly\"") != std::string::npos);
        CHECK(html.find("id=\"user-input\"") != std::string::npos);
    }
}

TEST_CASE("12010: Button fluent method chaining", "[fluent][form][button]") {
    SECTION("button with type and class chain") {
        button b("Submit");
        b.type("submit").cl("btn btn-primary").id("submit-btn").disabled();

        std::string html = b.html_string();
        CHECK(html.find("type=\"submit\"") != std::string::npos);
        CHECK(html.find("class=\"btn btn-primary\"") != std::string::npos);
        CHECK(html.find("id=\"submit-btn\"") != std::string::npos);
        CHECK(html.find("disabled=\"disabled\"") != std::string::npos);
    }
}

TEST_CASE("12020: Select fluent method chaining", "[fluent][form][select]") {
    SECTION("select with name, multiple, required chain") {
        select s;
        s.name("countries").id("country-select").cl("form-select").multiple().required();

        std::string html = s.html_string();
        CHECK(html.find("name=\"countries\"") != std::string::npos);
        CHECK(html.find("id=\"country-select\"") != std::string::npos);
        CHECK(html.find("class=\"form-select\"") != std::string::npos);
        CHECK(html.find("multiple=\"multiple\"") != std::string::npos);
        CHECK(html.find("required=\"required\"") != std::string::npos);
    }
}

TEST_CASE("12030: Form fluent method chaining", "[fluent][form]") {
    SECTION("form with action, method, class chain") {
        form f;
        f.action("/api/submit").method("POST").cl("user-form").id("main-form");

        std::string html = f.html_string();
        CHECK(html.find("action=\"/api/submit\"") != std::string::npos);
        CHECK(html.find("method=\"POST\"") != std::string::npos);
        CHECK(html.find("class=\"user-form\"") != std::string::npos);
        CHECK(html.find("id=\"main-form\"") != std::string::npos);
    }
}

TEST_CASE("12040: Table element fluent chaining", "[fluent][table]") {
    SECTION("td with colspan, rowspan, class chain") {
        td cell("Content");
        cell.colspan(2).rowspan(3).cl("highlight").id("special-cell");

        std::string html = cell.html_string();
        CHECK(html.find("colspan=\"2\"") != std::string::npos);
        CHECK(html.find("rowspan=\"3\"") != std::string::npos);
        CHECK(html.find("class=\"highlight\"") != std::string::npos);
        CHECK(html.find("id=\"special-cell\"") != std::string::npos);
    }

    SECTION("table with class and id") {
        table t;
        t.cl("data-table").id("users-table").role("grid");

        std::string html = t.html_string();
        CHECK(html.find("class=\"data-table\"") != std::string::npos);
        CHECK(html.find("id=\"users-table\"") != std::string::npos);
        CHECK(html.find("role=\"grid\"") != std::string::npos);
    }
}

TEST_CASE("12050: Media element fluent chaining", "[fluent][media]") {
    SECTION("video with controls, autoplay, muted chain") {
        video v;
        v.controls().autoplay().muted().loop().cl("video-player").id("main-video");

        std::string html = v.html_string();
        CHECK(html.find("controls=\"controls\"") != std::string::npos);
        CHECK(html.find("autoplay=\"autoplay\"") != std::string::npos);
        CHECK(html.find("muted=\"muted\"") != std::string::npos);
        CHECK(html.find("loop=\"loop\"") != std::string::npos);
        CHECK(html.find("class=\"video-player\"") != std::string::npos);
    }

    SECTION("audio with controls and preload") {
        audio a;
        a.controls().preload("auto").cl("audio-player");

        std::string html = a.html_string();
        CHECK(html.find("controls=\"controls\"") != std::string::npos);
        CHECK(html.find("preload=\"auto\"") != std::string::npos);
    }

    SECTION("img with loading, decoding, class chain") {
        img i("photo.jpg");
        i.loading("lazy").decoding("async").cl("responsive-img").alt("A photo");

        std::string html = i.html_string();
        CHECK(html.find("src=\"photo.jpg\"") != std::string::npos);
        CHECK(html.find("loading=\"lazy\"") != std::string::npos);
        CHECK(html.find("decoding=\"async\"") != std::string::npos);
        CHECK(html.find("class=\"responsive-img\"") != std::string::npos);
        CHECK(html.find("alt=\"A photo\"") != std::string::npos);
    }
}

TEST_CASE("12060: Interactive element fluent chaining", "[fluent][interactive]") {
    SECTION("details with open and class") {
        details d;
        d.open().cl("accordion-item").id("section-1");

        std::string html = d.html_string();
        CHECK(html.find("open=\"open\"") != std::string::npos);
        CHECK(html.find("class=\"accordion-item\"") != std::string::npos);
        CHECK(html.find("id=\"section-1\"") != std::string::npos);
    }
}

TEST_CASE("12070: Semantic element fluent chaining", "[fluent][semantic]") {
    SECTION("header with role and class") {
        header h;
        h.cl("site-header").id("main-header").role("banner");

        std::string html = h.html_string();
        CHECK(html.find("class=\"site-header\"") != std::string::npos);
        CHECK(html.find("id=\"main-header\"") != std::string::npos);
        CHECK(html.find("role=\"banner\"") != std::string::npos);
    }

    SECTION("blockquote with cite") {
        blockquote bq("Famous quote here");
        bq.cite("https://example.com/source").cl("featured-quote");

        std::string html = bq.html_string();
        CHECK(html.find("cite=\"https://example.com/source\"") != std::string::npos);
        CHECK(html.find("class=\"featured-quote\"") != std::string::npos);
    }

    SECTION("time with datetime") {
        time_ t("July 4, 2024");
        t.datetime("2024-07-04").cl("event-date");

        std::string html = t.html_string();
        CHECK(html.find("datetime=\"2024-07-04\"") != std::string::npos);
        CHECK(html.find("class=\"event-date\"") != std::string::npos);
    }
}

TEST_CASE("12080: Basic element fluent chaining", "[fluent][basic]") {
    SECTION("div with multiple attribute methods") {
        html::div d;
        d.cl("container").id("main").style("padding: 20px;").data("page", "home");

        std::string html = d.html_string();
        CHECK(html.find("class=\"container\"") != std::string::npos);
        CHECK(html.find("id=\"main\"") != std::string::npos);
        CHECK(html.find("style=\"padding: 20px;\"") != std::string::npos);
        CHECK(html.find("data-page=\"home\"") != std::string::npos);
    }

    SECTION("anchor with target and download") {
        anchor a("file.pdf", "Download PDF");
        a.target("_blank").download("document.pdf").cl("download-link");

        std::string html = a.html_string();
        CHECK(html.find("href=\"file.pdf\"") != std::string::npos);
        CHECK(html.find("target=\"_blank\"") != std::string::npos);
        CHECK(html.find("download=\"document.pdf\"") != std::string::npos);
        CHECK(html.find("class=\"download-link\"") != std::string::npos);
    }

    SECTION("heading with class and id") {
        h1 heading("Welcome");
        heading.cl("page-title").id("title");

        std::string html = heading.html_string();
        CHECK(html.find("class=\"page-title\"") != std::string::npos);
        CHECK(html.find("id=\"title\"") != std::string::npos);
    }

    SECTION("list item with class") {
        li item("Item text");
        item.cl("list-item").id("item-1").data("index", "0");

        std::string html = item.html_string();
        CHECK(html.find("class=\"list-item\"") != std::string::npos);
        CHECK(html.find("id=\"item-1\"") != std::string::npos);
        CHECK(html.find("data-index=\"0\"") != std::string::npos);
    }
}

// ============================================================================
// Variadic Constructor Tests with Fluent Chaining
// These tests verify that variadic constructors work with fluent method calls
// ============================================================================

TEST_CASE("12100: Form variadic constructor with fluent chain", "[variadic][fluent][form]") {
    SECTION("form with children and method chain") {
        auto f = form(
            label("Email:").for_id("email"),
            input().type("email").name("email").id("email").required(),
            button("Submit").type("submit")
        ).action("/submit").method("POST").cl("login-form");

        std::string html = f.html_string();
        CHECK(html.find("action=\"/submit\"") != std::string::npos);
        CHECK(html.find("method=\"POST\"") != std::string::npos);
        CHECK(html.find("class=\"login-form\"") != std::string::npos);
        CHECK(html.find("type=\"email\"") != std::string::npos);
        CHECK(html.find("<button") != std::string::npos);
    }
}

TEST_CASE("12110: Select variadic constructor with fluent chain", "[variadic][fluent][form]") {
    SECTION("select with options and attributes") {
        auto s = select(
            option("", "Choose..."),
            option("us", "United States"),
            option("ca", "Canada"),
            option("uk", "United Kingdom")
        ).name("country").id("country-select").required();

        std::string html = s.html_string();
        CHECK(html.find("name=\"country\"") != std::string::npos);
        CHECK(html.find("required=\"required\"") != std::string::npos);
        CHECK(html.find("United States") != std::string::npos);
    }
}

TEST_CASE("12120: Video variadic constructor with fluent chain", "[variadic][fluent][media]") {
    SECTION("video with sources and controls") {
        auto v = video(
            source("movie.mp4", "video/mp4"),
            source("movie.webm", "video/webm")
        ).controls().poster("poster.jpg").cl("main-video");

        std::string html = v.html_string();
        CHECK(html.find("controls=\"controls\"") != std::string::npos);
        CHECK(html.find("poster=\"poster.jpg\"") != std::string::npos);
        CHECK(html.find("class=\"main-video\"") != std::string::npos);
        CHECK(html.find("src=\"movie.mp4\"") != std::string::npos);
        CHECK(html.find("type=\"video/mp4\"") != std::string::npos);
    }
}

TEST_CASE("12130: Details variadic constructor with fluent chain", "[variadic][fluent][interactive]") {
    SECTION("details with summary and content") {
        auto d = details(
            summary("Click to expand"),
            p("Hidden content here"),
            p("More hidden content")
        ).open().cl("accordion");

        std::string html = d.html_string();
        CHECK(html.find("open=\"open\"") != std::string::npos);
        CHECK(html.find("class=\"accordion\"") != std::string::npos);
        CHECK(html.find("<summary>Click to expand</summary>") != std::string::npos);
        CHECK(html.find("Hidden content here") != std::string::npos);
    }
}

TEST_CASE("12140: Semantic variadic constructor with fluent chain", "[variadic][fluent][semantic]") {
    SECTION("header with nested content") {
        auto h = header(
            h1("Site Title"),
            nav(
                anchor("/", "Home"),
                anchor("/about", "About"),
                anchor("/contact", "Contact")
            )
        ).cl("site-header").role("banner");

        std::string html = h.html_string();
        CHECK(html.find("class=\"site-header\"") != std::string::npos);
        CHECK(html.find("role=\"banner\"") != std::string::npos);
        CHECK(html.find("<h1>Site Title</h1>") != std::string::npos);
        CHECK(html.find("<nav>") != std::string::npos);
    }

    SECTION("footer with content and attributes") {
        auto f = footer(
            p("Copyright 2024"),
            anchor("/privacy", "Privacy Policy")
        ).cl("site-footer").id("footer");

        std::string html = f.html_string();
        CHECK(html.find("class=\"site-footer\"") != std::string::npos);
        CHECK(html.find("id=\"footer\"") != std::string::npos);
    }

    SECTION("article with nested sections") {
        auto art = article(
            h2("Article Title"),
            section(
                h3("Introduction"),
                p("Article introduction text...")
            ),
            section(
                h3("Conclusion"),
                p("Article conclusion text...")
            )
        ).cl("blog-post").id("post-123");

        std::string html = art.html_string();
        CHECK(html.find("class=\"blog-post\"") != std::string::npos);
        CHECK(html.find("id=\"post-123\"") != std::string::npos);
        CHECK(html.find("<article") != std::string::npos);
        CHECK(html.find("<section>") != std::string::npos);
    }
}

TEST_CASE("12150: Table variadic with fluent chaining", "[variadic][fluent][table]") {
    SECTION("table with rows and attributes") {
        auto t = table(
            tr(th("Name").cl("header-cell"), th("Age").cl("header-cell")),
            tr(td("Alice"), td("28")),
            tr(td("Bob"), td("35"))
        ).cl("data-table").id("users");

        std::string html = t.html_string();
        CHECK(html.find("class=\"data-table\"") != std::string::npos);
        CHECK(html.find("id=\"users\"") != std::string::npos);
        CHECK(html.find("class=\"header-cell\"") != std::string::npos);
    }
}

TEST_CASE("12160: Div variadic with fluent chaining", "[variadic][fluent][basic]") {
    SECTION("div with complex nesting") {
        auto d = html::div(
            h1("Welcome").cl("title"),
            p("Introduction paragraph").cl("intro"),
            ul(
                li("First item").cl("item"),
                li("Second item").cl("item"),
                li("Third item").cl("item")
            ).cl("feature-list")
        ).cl("container").id("main-content");

        std::string html = d.html_string();
        CHECK(html.find("class=\"container\"") != std::string::npos);
        CHECK(html.find("id=\"main-content\"") != std::string::npos);
        CHECK(html.find("class=\"title\"") != std::string::npos);
        CHECK(html.find("class=\"feature-list\"") != std::string::npos);
    }
}

// ============================================================================
// Complex Real-World Usage Patterns
// ============================================================================

TEST_CASE("12200: Bootstrap-style form layout", "[fluent][real-world]") {
    SECTION("login form with Bootstrap classes") {
        auto login_form = form(
            html::div(
                label("Email address").for_id("email").cl("form-label"),
                input().type("email").name("email").id("email").cl("form-control").required()
            ).cl("mb-3"),
            html::div(
                label("Password").for_id("password").cl("form-label"),
                input().type("password").name("password").id("password").cl("form-control").required()
            ).cl("mb-3"),
            button("Sign In").type("submit").cl("btn btn-primary")
        ).action("/login").method("POST").cl("needs-validation");

        std::string html = login_form.html_string();
        CHECK(html.find("class=\"needs-validation\"") != std::string::npos);
        CHECK(html.find("class=\"form-control\"") != std::string::npos);
        CHECK(html.find("class=\"btn btn-primary\"") != std::string::npos);
        CHECK(html.find("class=\"mb-3\"") != std::string::npos);
    }
}

TEST_CASE("12210: Navigation menu pattern", "[fluent][real-world]") {
    SECTION("responsive nav with classes") {
        auto nav_menu = nav(
            ul(
                li(anchor("/", "Home").cl("nav-link")).cl("nav-item"),
                li(anchor("/about", "About").cl("nav-link")).cl("nav-item"),
                li(anchor("/services", "Services").cl("nav-link")).cl("nav-item"),
                li(anchor("/contact", "Contact").cl("nav-link")).cl("nav-item")
            ).cl("navbar-nav")
        ).cl("navbar").role("navigation");

        std::string html = nav_menu.html_string();
        CHECK(html.find("class=\"navbar\"") != std::string::npos);
        CHECK(html.find("role=\"navigation\"") != std::string::npos);
        CHECK(html.find("class=\"nav-link\"") != std::string::npos);
        CHECK(html.find("class=\"nav-item\"") != std::string::npos);
    }
}

TEST_CASE("12220: Card component pattern", "[fluent][real-world]") {
    SECTION("card with image and body") {
        auto card = html::div(
            img("card-image.jpg").cl("card-img-top").alt("Card image"),
            html::div(
                h5("Card Title").cl("card-title"),
                p("Some quick example text for the card.").cl("card-text"),
                anchor("#", "Go somewhere").cl("btn btn-primary")
            ).cl("card-body")
        ).cl("card").style("width: 18rem;");

        std::string html = card.html_string();
        CHECK(html.find("class=\"card\"") != std::string::npos);
        CHECK(html.find("class=\"card-img-top\"") != std::string::npos);
        CHECK(html.find("class=\"card-body\"") != std::string::npos);
        CHECK(html.find("class=\"card-title\"") != std::string::npos);
    }
}

TEST_CASE("12230: Accessibility patterns", "[fluent][real-world]") {
    SECTION("accessible form with ARIA") {
        auto accessible_form = form(
            html::div(
                label("Search").for_id("search").cl("sr-only"),
                input().type("search").name("q").id("search")
                    .cl("form-control")
                    .aria_label("Search the site")
                    .placeholder("Search...")
            ).cl("form-group"),
            button("Search").type("submit").cl("btn").aria_label("Submit search")
        ).role("search").cl("search-form");

        std::string html = accessible_form.html_string();
        CHECK(html.find("role=\"search\"") != std::string::npos);
        CHECK(html.find("aria-label=\"Search the site\"") != std::string::npos);
    }

    SECTION("accessible navigation") {
        auto accessible_nav = nav(
            ul(
                li(anchor("/", "Home")),
                li(anchor("/about", "About"))
            ).cl("nav-list")
        ).role("navigation").aria_label("Main navigation");

        std::string html = accessible_nav.html_string();
        CHECK(html.find("role=\"navigation\"") != std::string::npos);
        CHECK(html.find("aria-label=\"Main navigation\"") != std::string::npos);
    }
}

// ============================================================================
// Edge Cases and Return Type Verification
// ============================================================================

TEST_CASE("12300: Method chain return types", "[fluent][types]") {
    SECTION("input returns input& from all fluent methods") {
        input i;
        // All these should compile and return input&
        input& ref1 = i.type("text");
        input& ref2 = ref1.name("test");
        input& ref3 = ref2.id("myid");
        input& ref4 = ref3.cl("myclass");
        input& ref5 = ref4.style("color:red");
        input& ref6 = ref5.required();

        CHECK(&ref1 == &i);
        CHECK(&ref2 == &i);
        CHECK(&ref3 == &i);
        CHECK(&ref4 == &i);
        CHECK(&ref5 == &i);
        CHECK(&ref6 == &i);
    }

    SECTION("div returns div& from all fluent methods") {
        html::div d;
        html::div& ref1 = d.id("test");
        html::div& ref2 = ref1.cl("container");
        html::div& ref3 = ref2.style("margin:0");

        CHECK(&ref1 == &d);
        CHECK(&ref2 == &d);
        CHECK(&ref3 == &d);
    }

    SECTION("video returns video& from media methods") {
        video v;
        video& ref1 = v.controls();
        video& ref2 = ref1.autoplay();
        video& ref3 = ref2.muted();
        video& ref4 = ref3.cl("video-class");

        CHECK(&ref1 == &v);
        CHECK(&ref2 == &v);
        CHECK(&ref3 == &v);
        CHECK(&ref4 == &v);
    }
}

TEST_CASE("12310: Add_cl accumulation with fluent chain", "[fluent][classes]") {
    SECTION("add_cl adds to existing classes") {
        html::div d;
        d.cl("base").add_cl("modifier").add_cl("state");

        std::string html = d.html_string();
        CHECK(html.find("class=\"base modifier state\"") != std::string::npos);
    }
}

TEST_CASE("12320: Data attributes in chain", "[fluent][data]") {
    SECTION("multiple data attributes") {
        html::div d;
        d.data("id", "123").data("action", "toggle").data("target", "#menu").cl("interactive");

        std::string html = d.html_string();
        CHECK(html.find("data-id=\"123\"") != std::string::npos);
        CHECK(html.find("data-action=\"toggle\"") != std::string::npos);
        CHECK(html.find("data-target=\"#menu\"") != std::string::npos);
    }
}
