/*  ===================================================================
*                      HTML Generator Library - Output Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*
*  These tests generate HTML pages in tests/output/ for visual inspection.
*  Run them to see how the library produces real HTML output.
*/

#include <catch2/catch_all.hpp>
#include <fstream>
#include <filesystem>
#include "../include/html_gen.h"
#include "../include/html_gen_charts.h"
#include "../include/html_gen_resources.h"

using namespace html;

// Helper to get output directory path
std::filesystem::path get_output_dir() {
    std::filesystem::path source_file(__FILE__);
    std::filesystem::path dir = source_file.parent_path() / "output";
    if (!std::filesystem::exists(dir)) {
        std::filesystem::create_directories(dir);
    }
    return dir;
}

// Helper to save page to file
void save_page(const std::string& filename, page& pg) {
    std::filesystem::path filepath = get_output_dir() / filename;
    std::ofstream file(filepath);
    file << pg;
    file.close();
}

TEST_CASE("70000: All basic elements showcase", "[output][basic]") {
    page pg;
    pg.head << title("Basic HTML Elements Showcase");
    pg.head << style(resources::bootstrap_css_string());

    // Container
    html::div container;
    container.cl("container");

    // Header
    container << h1("HTML Elements Showcase");
    container << p("This page demonstrates all basic HTML elements available in the library.");
    container << hr();

    // Headings
    container << h2("Headings");
    container << h1("Heading 1");
    container << h2("Heading 2");
    container << h3("Heading 3");
    container << h4("Heading 4");
    container << h5("Heading 5");
    container << h6("Heading 6");
    container << hr();

    // Text formatting
    container << h2("Text Formatting");
    container << p("This is a normal paragraph.");
    container << p(strong("Bold text using strong tag."));
    container << p(b("Bold text using b tag."));
    container << p(em("Emphasized/italic text."));
    container << p(small_("Small text."));
    container << p(mark("Highlighted text."));
    container << p(code("Inline code snippet."));
    container << p(kbd("Keyboard input"));
    container << p() << text("Text with ") << sub("subscript") << text(" and ") << sup("superscript");
    container << p(del("Deleted text."));
    container << p(ins("Inserted text."));
    container << p(s("Strikethrough text."));
    container << p(u("Underlined text."));
    container << hr();

    // Lists
    container << h2("Lists");

    container << h3("Unordered List");
    container << ul(li("First item"), li("Second item"), li("Third item"));

    container << h3("Ordered List");
    container << ol(li("First item"), li("Second item"), li("Third item"));
    container << hr();

    // Links and Images
    container << h2("Links and Images");
    container << p() << anchor("https://example.com", "Example link");
    container << p() << img("https://via.placeholder.com/150x100", "150");
    container << hr();

    // Blockquote
    container << h2("Blockquote");
    blockquote bq("This is a blockquote. It can contain a longer piece of text.");
    bq.cite("https://example.com");
    container << bq;
    container << hr();

    // Preformatted text
    container << h2("Preformatted Text");
    pre code_block;
    code_block << text("function example() {\n    console.log('Hello');\n    return true;\n}");
    container << code_block;
    container << hr();

    // Abbreviation
    container << h2("Abbreviation");
    abbr ab("HTML");
    ab.title("HyperText Markup Language");
    container << p() << ab << text(" is the standard markup language for web pages.");

    pg << container;
    save_page("01_basic_elements.html", pg);

    CHECK(std::filesystem::exists(get_output_dir() / "01_basic_elements.html"));
}

TEST_CASE("70010: Table examples", "[output][tables]") {
    page pg;
    pg.head << title("Table Examples");
    pg.head << style(resources::bootstrap_css_string());

    html::div container;
    container.cl("container");

    container << h1("Table Examples");

    // Simple table
    container << h2("Simple Table");
    table t1;
    t1.cl("table table-bordered");
    t1.thead << tr(th("Name"), th("Age"), th("City"));
    t1 << tr(td("Alice"), td("28"), td("New York"));
    t1 << tr(td("Bob"), td("35"), td("Los Angeles"));
    t1 << tr(td("Charlie"), td("42"), td("Chicago"));
    container << t1;

    // Striped table
    container << h2("Striped Table");
    table t2;
    t2.cl("table table-striped");
    t2.thead << tr(th("Product"), th("Price"), th("Quantity"), th("Total"));
    t2 << tr(td("Widget A"), td("$10.00"), td("5"), td("$50.00"));
    t2 << tr(td("Widget B"), td("$15.00"), td("3"), td("$45.00"));
    t2 << tr(td("Widget C"), td("$8.00"), td("10"), td("$80.00"));
    t2.tfoot << tr(td("").colspan(3), td(strong("$175.00")));
    container << t2;

    // Table with colspan and rowspan
    container << h2("Table with Colspan and Rowspan");
    table t3;
    t3.cl("table table-bordered");
    t3.thead << tr(th("Header 1").colspan(2), th("Header 2"));
    t3 << tr(td("Row 1, Col 1"), td("Row 1, Col 2"), td("Row 1, Col 3").rowspan(2));
    t3 << tr(td("Row 2, Col 1").colspan(2));
    container << t3;

    // Table with colgroup
    container << h2("Table with Column Styling");
    table t4;
    t4.cl("table");
    colgroup cg;
    cg << col().style("background-color: #f0f0f0;") << col().span(2);
    t4 << cg;
    t4.thead << tr(th("ID"), th("Name"), th("Value"));
    t4 << tr(td("1"), td("Alpha"), td("100"));
    t4 << tr(td("2"), td("Beta"), td("200"));
    t4 << tr(td("3"), td("Gamma"), td("300"));
    container << t4;

    pg << container;
    save_page("02_tables.html", pg);

    CHECK(std::filesystem::exists(get_output_dir() / "02_tables.html"));
}

TEST_CASE("70020: Form examples", "[output][forms]") {
    page pg;
    pg.head << title("Form Examples");
    pg.head << style(resources::bootstrap_css_string());

    html::div container;
    container.cl("container");

    container << h1("Form Examples");

    // Login form
    container << h2("Login Form");
    form login_form;
    login_form.cl("form-horizontal");
    login_form.action("/login").method("POST");

    html::div fg1;
    fg1.cl("form-group");
    fg1 << label("Email:").for_id("email");
    input email_input;
    email_input.name("email").placeholder("Enter email").required();
    email_input.type("email").id("email").cl("form-control");
    fg1 << email_input;
    login_form << fg1;

    html::div fg2;
    fg2.cl("form-group");
    fg2 << label("Password:").for_id("password");
    input pwd_input;
    pwd_input.name("password").placeholder("Enter password").required();
    pwd_input.type("password").id("password").cl("form-control");
    fg2 << pwd_input;
    login_form << fg2;

    html::div fg3;
    fg3.cl("checkbox");
    label remember_label("Remember me");
    input remember_check;
    remember_check.name("remember");
    remember_check.type("checkbox");
    fg3 << remember_label << remember_check;
    login_form << fg3;

    login_form << button("Login").type("submit").cl("btn btn-primary");
    container << login_form;
    container << hr();

    // Contact form
    container << h2("Contact Form");
    form contact_form;
    contact_form.action("/contact").method("POST");

    fieldset fs;
    fs << legend("Contact Information");

    html::div row1;
    row1.cl("form-group");
    row1 << label("Name:").for_id("name");
    input name_input;
    name_input.name("name").required();
    name_input.type("text").id("name").cl("form-control");
    row1 << name_input;
    fs << row1;

    html::div row2;
    row2.cl("form-group");
    row2 << label("Email:").for_id("contact_email");
    input contact_email;
    contact_email.name("email").required();
    contact_email.type("email").id("contact_email").cl("form-control");
    row2 << contact_email;
    fs << row2;

    html::div row3;
    row3.cl("form-group");
    row3 << label("Subject:").for_id("subject");
    select subj;
    subj.name("subject").id("subject").cl("form-control");
    subj << option("general", "General Inquiry")
         << option("support", "Technical Support")
         << option("sales", "Sales Question");
    fs << row3 << subj;

    html::div row4;
    row4.cl("form-group");
    row4 << label("Message:").for_id("message");
    textarea msg;
    msg.id("message").cl("form-control");
    msg.add_attr("rows", "5");
    fs << row4 << msg;

    contact_form << fs;
    contact_form << button("Send Message").type("submit").cl("btn btn-success");
    container << contact_form;
    container << hr();

    // Form controls showcase
    container << h2("Form Controls");

    container << h3("Input Types");
    input text_in; text_in.placeholder("Text input"); text_in.type("text");
    p p1; p1 << label("Text: ") << text_in; container << p1;
    input num_in; num_in.value("42"); num_in.type("number");
    p p2; p2 << label("Number: ") << num_in; container << p2;
    input range_in; range_in.type("range");
    container << p() << label("Range: ") << range_in;
    input date_in; date_in.type("date");
    container << p() << label("Date: ") << date_in;
    input color_in; color_in.type("color");
    container << p() << label("Color: ") << color_in;

    container << h3("Progress and Meter");
    container << p() << label("Progress: ");
    progress prog;
    prog.value(70).max(100);
    container << prog;

    container << p() << label("Meter: ");
    meter m;
    m.value(0.7).min(0).max(1).low(0.3).high(0.8).optimum(0.5);
    container << m;

    container << h3("Datalist");
    input dl_input;
    dl_input.type("text").add_attr("list", "browsers");
    datalist dl;
    dl.id("browsers");
    dl << option("Chrome") << option("Firefox") << option("Safari") << option("Edge");
    container << dl_input << dl;

    pg << container;
    save_page("03_forms.html", pg);

    CHECK(std::filesystem::exists(get_output_dir() / "03_forms.html"));
}

TEST_CASE("70030: Semantic elements", "[output][semantic]") {
    page pg;
    pg.head << title("Semantic HTML5 Elements");
    pg.head << style(resources::bootstrap_css_string());
    pg.head << style(R"(
        header, footer, nav, main, article, section, aside {
            border: 1px solid #ddd;
            padding: 10px;
            margin: 5px 0;
        }
        header { background-color: #f5f5f5; }
        nav { background-color: #e8f4f8; }
        main { background-color: #fff; }
        article { background-color: #f9f9f9; }
        aside { background-color: #fef9e7; }
        footer { background-color: #f5f5f5; }
    )");

    // Page header
    header hdr;
    hdr << h1("Website Title");
    nav navigation;
    navigation << ul(
        li(anchor("#", "Home")),
        li(anchor("#", "About")),
        li(anchor("#", "Services")),
        li(anchor("#", "Contact"))
    );
    hdr << navigation;
    pg << hdr;

    // Main content
    html::main main_content;

    // Article
    article art(
        h2("Article Title"),
        p("Published on: "),
        time_("November 23, 2024").datetime("2024-11-23"),
        section(
            h3("Introduction"),
            p("This is the introduction section of the article.")
        ),
        section(
            h3("Main Content"),
            p("This is the main content section with more details."),
            figure(
                img("https://via.placeholder.com/300x200", "300"),
                figcaption("Figure 1: A placeholder image")
            )
        )
    );
    main_content << art;

    // Aside
    aside side(
        h3("Related Links"),
        ul(
            li(anchor("#", "Related Article 1")),
            li(anchor("#", "Related Article 2")),
            li(anchor("#", "Related Article 3"))
        )
    );
    main_content << side;

    pg << main_content;

    // Footer
    footer ftr;
    address addr;
    addr << text("Contact: ") << anchor("mailto:info@example.com", "info@example.com");
    ftr << addr;
    ftr << p(small_("Copyright 2024 Example Inc."));
    pg << ftr;

    save_page("04_semantic.html", pg);

    CHECK(std::filesystem::exists(get_output_dir() / "04_semantic.html"));
}

TEST_CASE("70040: Interactive elements", "[output][interactive]") {
    page pg;
    pg.head << title("Interactive Elements");
    pg.head << style(resources::bootstrap_css_string());

    html::div container;
    container.cl("container");

    container << h1("Interactive Elements");

    // Details/Summary
    container << h2("Details and Summary");

    details d1;
    d1 << summary("Click to expand - Basic example");
    d1 << p("This is the hidden content that appears when you click the summary.");
    container << d1;

    details d2;
    d2 << summary("This one starts open");
    d2 << p("This content is visible by default because the details element has the open attribute.");
    d2.open();
    container << d2;

    details d3;
    d3 << summary("FAQ: What is this library?");
    d3 << p("This is a C++20 library for generating HTML programmatically. It provides a fluent interface for creating HTML elements.");
    container << d3;

    // Dialog
    container << h2("Dialog");
    dialog dlg;
    dlg << h3("Dialog Title");
    dlg << p("This is a dialog box. In a real application, it would be controlled by JavaScript.");
    dlg << button("Close").type("button");
    dlg.id("myDialog");
    dlg.open();
    container << dlg;

    // Template
    container << h2("Template");
    container << p("Template elements contain content that is not rendered but can be used by JavaScript:");
    template_ tmpl;
    tmpl << html::div(h3("Card Title"), p("Card content goes here.")).cl("card");
    tmpl.id("card-template");
    container << tmpl;

    pg << container;
    save_page("05_interactive.html", pg);

    CHECK(std::filesystem::exists(get_output_dir() / "05_interactive.html"));
}

TEST_CASE("70050: Bootstrap styled page", "[output][bootstrap]") {
    page pg;
    pg.head << title("Bootstrap Styled Page");
    pg.head << style(resources::bootstrap_css_string());
    pg.head << script(resources::bootstrap_js_string());

    // Navigation bar (Bootstrap 5)
    nav navbar;
    navbar.cl("navbar navbar-expand-lg navbar-light bg-light");
    html::div nav_container;
    nav_container.cl("container-fluid");

    anchor brand("Brand");
    brand.cl("navbar-brand").href("#");
    nav_container << brand;

    html::div nav_collapse;
    nav_collapse.cl("collapse navbar-collapse");
    ul nav_items(
        li(anchor("#", "Home").cl("nav-link active")),
        li(anchor("#", "Products").cl("nav-link")),
        li(anchor("#", "About").cl("nav-link")),
        li(anchor("#", "Contact").cl("nav-link"))
    );
    nav_items.cl("navbar-nav me-auto mb-2 mb-lg-0");
    for (size_t i = 0; i < nav_items.size(); i++) {
        nav_items[i].cl("nav-item");
    }
    nav_collapse << nav_items;
    nav_container << nav_collapse;

    navbar << nav_container;
    pg << navbar;

    // Main container
    html::div cont;
    cont.cl("container");

    // Page header (Bootstrap 5)
    html::div page_header;
    page_header.cl("pb-2 mt-4 mb-4 border-bottom");
    page_header << h1("Dashboard") << small_(" Overview").cl("text-muted");
    cont << page_header;

    // Row with panels
    html::div row1;
    row1.cl("row");

    // Card 1 (Bootstrap 5 - replaces panel)
    html::div col1;
    col1.cl("col-md-4 mb-3");
    html::div card1;
    card1.cl("card text-bg-primary");
    html::div card1_head;
    card1_head.cl("card-header");
    card1_head << h5("Statistics").cl("card-title mb-0");
    card1 << card1_head;
    html::div card1_body;
    card1_body.cl("card-body");
    card1_body << p("Total Users: ") << strong("1,234");
    card1_body << p("Active Today: ") << strong("567");
    card1 << card1_body;
    col1 << card1;
    row1 << col1;

    // Card 2
    html::div col2;
    col2.cl("col-md-4 mb-3");
    html::div card2;
    card2.cl("card text-bg-success");
    html::div card2_head;
    card2_head.cl("card-header");
    card2_head << h5("Revenue").cl("card-title mb-0");
    card2 << card2_head;
    html::div card2_body;
    card2_body.cl("card-body");
    card2_body << p("This Month: ") << strong("$45,678");
    card2_body << p("Last Month: ") << strong("$42,123");
    card2 << card2_body;
    col2 << card2;
    row1 << col2;

    // Card 3
    html::div col3;
    col3.cl("col-md-4 mb-3");
    html::div card3;
    card3.cl("card text-bg-info");
    html::div card3_head;
    card3_head.cl("card-header");
    card3_head << h5("Tasks").cl("card-title mb-0");
    card3 << card3_head;
    html::div card3_body;
    card3_body.cl("card-body");
    card3_body << p("Completed: ") << strong("89%");
    html::div prog_container;
    prog_container.cl("progress");
    html::div prog_bar;
    prog_bar.cl("progress-bar").style("width: 89%").role("progressbar");
    prog_bar.add_attr("aria-valuenow", "89");
    prog_bar.add_attr("aria-valuemin", "0");
    prog_bar.add_attr("aria-valuemax", "100");
    prog_container << prog_bar;
    card3_body << prog_container;
    card3 << card3_body;
    col3 << card3;
    row1 << col3;

    cont << row1;

    // Table in a card (Bootstrap 5)
    html::div table_card;
    table_card.cl("card mt-4");
    html::div table_card_head;
    table_card_head.cl("card-header");
    table_card_head << h5("Recent Orders").cl("card-title mb-0");
    table_card << table_card_head;

    table orders;
    orders.cl("table table-striped mb-0");
    orders.thead << tr(th("#"), th("Customer"), th("Product"), th("Amount"), th("Status"));
    orders << tr(td("1001"), td("John Doe"), td("Widget Pro"), td("$299"), td(span("Shipped").cl("badge bg-success")));
    orders << tr(td("1002"), td("Jane Smith"), td("Gadget Plus"), td("$149"), td(span("Processing").cl("badge bg-warning text-dark")));
    orders << tr(td("1003"), td("Bob Wilson"), td("Tool Kit"), td("$89"), td(span("Pending").cl("badge bg-secondary")));
    table_card << orders;

    cont << table_card;

    // Alerts
    cont << h2("Alerts");
    html::div alert1;
    alert1.cl("alert alert-success");
    alert1 << strong("Success!") << text(" Operation completed successfully.");
    cont << alert1;

    html::div alert2;
    alert2.cl("alert alert-warning");
    alert2 << strong("Warning!") << text(" Please review your settings.");
    cont << alert2;

    html::div alert3;
    alert3.cl("alert alert-danger");
    alert3 << strong("Error!") << text(" Something went wrong.");
    cont << alert3;

    pg << cont;

    // Footer (Bootstrap 5)
    footer ftr;
    ftr.cl("text-center mt-5 py-4 bg-light");
    ftr << p("Generated with CPP_HTML_GEN Library").cl("text-muted mb-0");
    pg << ftr;

    save_page("06_bootstrap.html", pg);

    CHECK(std::filesystem::exists(get_output_dir() / "06_bootstrap.html"));
}

TEST_CASE("70060: Media elements", "[output][media]") {
    page pg;
    pg.head << title("Media Elements");
    pg.head << style(resources::bootstrap_css_string());

    html::div container;
    container.cl("container");

    container << h1("Media Elements");

    // Images
    container << h2("Images");
    container << p("Basic image:");
    container << img("https://via.placeholder.com/300x200", "300").alt("Placeholder image");

    // Picture element
    container << h2("Picture Element (Responsive Images)");
    picture pic;
    source src1;
    src1.add_attr("media", "(min-width: 800px)");
    src1.add_attr("srcset", "https://via.placeholder.com/800x400");
    pic << src1;
    source src2;
    src2.add_attr("media", "(min-width: 400px)");
    src2.add_attr("srcset", "https://via.placeholder.com/400x200");
    pic << src2;
    pic << img("https://via.placeholder.com/200x100", "200").alt("Fallback image");
    container << pic;

    // Video
    container << h2("Video Element");
    video vid;
    vid.width("400").height("300");
    vid.controls();
    vid.add_attr("poster", "https://via.placeholder.com/400x300");
    source vid_src("https://example.com/video.mp4", "video/mp4");
    vid << vid_src;
    vid << p("Your browser does not support the video tag.");
    container << vid;

    // Audio
    container << h2("Audio Element");
    audio aud;
    aud.controls();
    source aud_src("https://example.com/audio.mp3", "audio/mp3");
    aud << aud_src;
    aud << p("Your browser does not support the audio tag.");
    container << aud;

    // Iframe
    container << h2("Iframe");
    iframe ifr;
    ifr.src("https://example.com").width("100%").height("300");
    ifr.sandbox("allow-scripts");
    container << ifr;

    // Canvas
    container << h2("Canvas");
    canvas cnv;
    cnv.id("myCanvas").width("400").height("200");
    cnv.style("border: 1px solid #ddd;");
    cnv << text("Your browser does not support the canvas element.");
    container << cnv;

    pg << container;
    save_page("07_media.html", pg);

    CHECK(std::filesystem::exists(get_output_dir() / "07_media.html"));
}

TEST_CASE("70070: Accessibility features", "[output][a11y]") {
    page pg;
    pg.head << title("Accessibility Features");
    pg.head << style(resources::bootstrap_css_string());

    html::div container;
    container.cl("container");

    container << h1("Accessibility Features");
    container << p("This page demonstrates ARIA attributes and accessibility features.");

    // ARIA landmarks
    container << h2("ARIA Landmarks");

    nav main_nav;
    main_nav << ul(
        li(anchor("#", "Home")),
        li(anchor("#", "Products")),
        li(anchor("#", "Contact"))
    );
    main_nav.role("navigation").aria_label("Main navigation");
    container << main_nav;

    // Accessible form
    container << h2("Accessible Form");
    form acc_form;
    acc_form.role("form").aria_labelledby("form-title");
    acc_form << h3("User Registration").id("form-title");

    html::div fg;
    fg.cl("form-group");
    label name_label("Full Name");
    name_label.for_id("fullname");
    input fullname_input;
    fullname_input.name("fullname").required();
    fullname_input.type("text").id("fullname").cl("form-control").aria_describedby("name-help");
    span name_help("Enter your first and last name.");
    name_help.id("name-help").cl("help-block");
    fg << name_label << fullname_input << name_help;
    acc_form << fg;

    container << acc_form;

    // Accessible buttons
    container << h2("Accessible Buttons");

    button btn1("Open Menu");
    btn1.aria_expanded(false).aria_controls("menu1");
    container << btn1;

    button btn2;
    btn2.aria_label("Close").type("button");
    btn2 << span("X").aria_hidden(true);
    container << btn2;

    // Live regions
    container << h2("Live Regions");
    html::div status;
    status.role("status").aria_live("polite");
    status << p("Status messages will appear here.");
    container << status;

    html::div alert;
    alert.role("alert").aria_live("assertive");
    alert.cl("alert alert-danger");
    alert << p("Important alert message!");
    container << alert;

    // Data attributes
    container << h2("Data Attributes");
    html::div data_div;
    data_div.data("user-id", "123")
            .data("role", "admin")
            .data("created", "2024-01-15");
    data_div << p("This div has custom data attributes.");
    container << data_div;

    // Global attributes
    container << h2("Global Attributes");
    html::div global_div;
    global_div.id("special-div")
              .cl("highlighted")
              .title("Tooltip text")
              .lang("en")
              .tabindex(0)
              .contenteditable(true)
              .spellcheck(true);
    global_div << p("This div demonstrates various global attributes. It's content-editable!");
    container << global_div;

    pg << container;
    save_page("08_accessibility.html", pg);

    CHECK(std::filesystem::exists(get_output_dir() / "08_accessibility.html"));
}

TEST_CASE("70080: Charts with ApexCharts", "[output][charts]") {
    page pg;
    pg.head << title("Charts with ApexCharts");
    pg.head << style(resources::bootstrap_css_string());
    pg.head << script(resources::apexcharts_js_string());

    html::div container;
    container.cl("container");

    container << h1("Charts with ApexCharts");
    container << p("This page demonstrates the built-in chart support using ApexCharts library.");

    // Line chart
    container << h2("Line Chart");
    chart::line_chart line;
    line.m_id = "line_chart";
    line.m_data_name = "Sales";
    line.m_color = "#3498db";
    for (double val : {10.0, 25.0, 15.0, 30.0, 22.0, 35.0, 28.0}) {
        line.add(val);
    }
    container << line.html();

    // Bar chart
    container << h2("Bar Chart");
    chart::bar_chart bar;
    bar.m_id = "bar_chart";
    bar.m_data_name = "Revenue";
    bar.add("Jan", 120.0);
    bar.add("Feb", 180.0);
    bar.add("Mar", 150.0);
    bar.add("Apr", 200.0);
    bar.add("May", 170.0);
    container << bar.html();

    // Timeseries chart
    container << h2("Timeseries Chart");
    chart::timeseries_line_chart ts;
    ts.m_id = "ts_chart";
    ts.m_data_name = "Temperature";
    ts.m_color = "#e74c3c";
    ts.add(std::chrono::system_clock::now() - std::chrono::hours(24*6), 20.0);
    ts.add(std::chrono::system_clock::now() - std::chrono::hours(24*5), 22.0);
    ts.add(std::chrono::system_clock::now() - std::chrono::hours(24*4), 19.0);
    ts.add(std::chrono::system_clock::now() - std::chrono::hours(24*3), 24.0);
    ts.add(std::chrono::system_clock::now() - std::chrono::hours(24*2), 21.0);
    ts.add(std::chrono::system_clock::now() - std::chrono::hours(24), 23.0);
    ts.add(std::chrono::system_clock::now(), 25.0);
    container << ts.html();

    pg << container;
    save_page("09_charts.html", pg);

    CHECK(std::filesystem::exists(get_output_dir() / "09_charts.html"));
}

TEST_CASE("70090: Complete report example", "[output][report]") {
    page pg;
    pg.head << title("Monthly Sales Report - Q4 2024");
    pg.head << style(resources::bootstrap_css_string());
    pg.head << script(resources::apexcharts_js_string());

    // Custom styles
    pg.head << style(R"(
        .report-header { background-color: #2c3e50; color: white; padding: 20px; margin-bottom: 20px; }
        .metric-card { text-align: center; padding: 20px; border: 1px solid #ddd; border-radius: 5px; }
        .metric-value { font-size: 2.5em; font-weight: bold; color: #3498db; }
        .metric-label { color: #7f8c8d; }
    )");

    // Report header
    header report_header;
    report_header.cl("report-header");
    report_header << h1("Monthly Sales Report");
    report_header << p("Q4 2024 - November Analysis");
    pg << report_header;

    html::div cont;
    cont.cl("container");

    // Summary metrics
    html::div metrics_row;
    metrics_row.cl("row");

    html::div m1;
    m1.cl("col-md-3");
    html::div metric1;
    metric1.cl("metric-card");
    metric1 << html::div().cl("metric-value") << text("$127,450");
    metric1 << html::div().cl("metric-label") << text("Total Revenue");
    m1 << metric1;
    metrics_row << m1;

    html::div m2;
    m2.cl("col-md-3");
    html::div metric2;
    metric2.cl("metric-card");
    metric2 << html::div().cl("metric-value") << text("1,847");
    metric2 << html::div().cl("metric-label") << text("Total Orders");
    m2 << metric2;
    metrics_row << m2;

    html::div m3;
    m3.cl("col-md-3");
    html::div metric3;
    metric3.cl("metric-card");
    metric3 << html::div().cl("metric-value") << text("$69.00");
    metric3 << html::div().cl("metric-label") << text("Avg Order Value");
    m3 << metric3;
    metrics_row << m3;

    html::div m4;
    m4.cl("col-md-3");
    html::div metric4;
    metric4.cl("metric-card");
    metric4 << html::div().cl("metric-value") << text("+15%");
    metric4 << html::div().cl("metric-label") << text("Growth Rate");
    m4 << metric4;
    metrics_row << m4;

    cont << metrics_row;
    cont << hr();

    // Sales chart
    cont << h2("Sales Trend");
    chart::line_chart sales_chart;
    sales_chart.m_id = "sales_trend";
    sales_chart.m_data_name = "Revenue ($)";
    sales_chart.m_color = "#3498db";
    for (double val : {28500.0, 31200.0, 29800.0, 37950.0}) {
        sales_chart.add(val);
    }
    cont << sales_chart.html();

    // Top products table
    cont << h2("Top Products");
    table products;
    products.cl("table table-striped table-hover");
    products.thead << tr(th("Rank"), th("Product"), th("Units Sold"), th("Revenue"), th("Growth"));
    products << tr(td("1"), td("Widget Pro"), td("423"), td("$42,300"), td(span("+23%").cl("text-success")));
    products << tr(td("2"), td("Gadget Plus"), td("356"), td("$35,600"), td(span("+18%").cl("text-success")));
    products << tr(td("3"), td("Tool Kit"), td("298"), td("$26,820"), td(span("+12%").cl("text-success")));
    products << tr(td("4"), td("Basic Widget"), td("245"), td("$12,250"), td(span("-5%").cl("text-danger")));
    products << tr(td("5"), td("Mini Gadget"), td("189"), td("$9,450"), td(span("+8%").cl("text-success")));
    cont << products;

    // Regional breakdown
    cont << h2("Regional Performance");
    chart::bar_chart region_chart;
    region_chart.m_id = "region_perf";
    region_chart.m_data_name = "Revenue ($K)";
    region_chart.add("North", 45.2);
    region_chart.add("South", 38.7);
    region_chart.add("East", 28.4);
    region_chart.add("West", 15.1);
    cont << region_chart.html();

    // Footer
    footer report_footer;
    report_footer.cl("text-center");
    report_footer.style("margin-top: 30px; padding: 20px; background-color: #ecf0f1;");
    report_footer << p("Report generated: November 23, 2024");
    report_footer << p(small_("CPP_HTML_GEN Library - Self-contained HTML Report"));
    cont << report_footer;

    pg << cont;
    save_page("10_complete_report.html", pg);

    CHECK(std::filesystem::exists(get_output_dir() / "10_complete_report.html"));
}
