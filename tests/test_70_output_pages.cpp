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
#include "../include/html_tags.h"
#include "../include/bootstrap.h"
#include "../include/html_resources.h"

using namespace html;
namespace bs = html::bootstrap;

// Helper to get output directory path
std::filesystem::path get_output_dir() {
    std::filesystem::path dir = std::filesystem::current_path();
    // Navigate to tests/output from build directory
    dir = dir.parent_path() / "tests" / "output";
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
    ul ul1;
    ul1 << li("First item") << li("Second item") << li("Third item");
    container << ul1;

    container << h3("Ordered List");
    ol ol1;
    ol1 << li("First item") << li("Second item") << li("Third item");
    container << ol1;
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
    t1.thead << (tr() << th("Name") << th("Age") << th("City"));
    t1 << (tr() << td("Alice") << td("28") << td("New York"));
    t1 << (tr() << td("Bob") << td("35") << td("Los Angeles"));
    t1 << (tr() << td("Charlie") << td("42") << td("Chicago"));
    container << t1;

    // Striped table
    container << h2("Striped Table");
    table t2;
    t2.cl("table table-striped");
    t2.thead << (tr() << th("Product") << th("Price") << th("Quantity") << th("Total"));
    t2 << (tr() << td("Widget A") << td("$10.00") << td("5") << td("$50.00"));
    t2 << (tr() << td("Widget B") << td("$15.00") << td("3") << td("$45.00"));
    t2 << (tr() << td("Widget C") << td("$8.00") << td("10") << td("$80.00"));
    t2.tfoot << (tr() << td("").colspan(3) << td(strong("$175.00")));
    container << t2;

    // Table with colspan and rowspan
    container << h2("Table with Colspan and Rowspan");
    table t3;
    t3.cl("table table-bordered");
    t3.thead << (tr() << th("Header 1").colspan(2) << th("Header 2"));
    t3 << (tr() << td("Row 1, Col 1") << td("Row 1, Col 2") << td("Row 1, Col 3").rowspan(2));
    t3 << (tr() << td("Row 2, Col 1").colspan(2));
    container << t3;

    // Table with colgroup
    container << h2("Table with Column Styling");
    table t4;
    t4.cl("table");
    colgroup cg;
    col c1; c1.style("background-color: #f0f0f0;");
    col c2; c2.span(2);
    cg << c1 << c2;
    t4 << cg;
    t4.thead << (tr() << th("ID") << th("Name") << th("Value"));
    t4 << (tr() << td("1") << td("Alpha") << td("100"));
    t4 << (tr() << td("2") << td("Beta") << td("200"));
    t4 << (tr() << td("3") << td("Gamma") << td("300"));
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
    subj << option("general", "General Inquiry");
    subj << option("support", "Technical Support");
    subj << option("sales", "Sales Question");
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
    ul nav_list;
    nav_list << li(anchor("#", "Home"))
             << li(anchor("#", "About"))
             << li(anchor("#", "Services"))
             << li(anchor("#", "Contact"));
    navigation << nav_list;
    hdr << navigation;
    pg << hdr;

    // Main content
    html::main main_content;

    // Article
    article art;
    art << h2("Article Title");
    art << p("Published on: ") << time_("November 23, 2024").datetime("2024-11-23");

    section sec1;
    sec1 << h3("Introduction");
    sec1 << p("This is the introduction section of the article.");
    art << sec1;

    section sec2;
    sec2 << h3("Main Content");
    sec2 << p("This is the main content section with more details.");

    // Figure
    figure fig;
    fig << img("https://via.placeholder.com/300x200", "300");
    fig << figcaption("Figure 1: A placeholder image");
    sec2 << fig;
    art << sec2;

    main_content << art;

    // Aside
    aside side;
    side << h3("Related Links");
    ul related;
    related << li(anchor("#", "Related Article 1"))
            << li(anchor("#", "Related Article 2"))
            << li(anchor("#", "Related Article 3"));
    side << related;
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
    d2.open();
    d2 << summary("This one starts open");
    d2 << p("This content is visible by default because the details element has the open attribute.");
    container << d2;

    details d3;
    d3 << summary("FAQ: What is this library?");
    d3 << p("This is a C++20 library for generating HTML programmatically. It provides a fluent interface for creating HTML elements.");
    container << d3;

    // Dialog
    container << h2("Dialog");
    dialog dlg;
    dlg.id("myDialog");
    dlg.open();
    dlg << h3("Dialog Title");
    dlg << p("This is a dialog box. In a real application, it would be controlled by JavaScript.");
    button close_btn("Close");
    close_btn.type("button");
    dlg << close_btn;
    container << dlg;

    // Template
    container << h2("Template");
    container << p("Template elements contain content that is not rendered but can be used by JavaScript:");
    template_ tmpl;
    tmpl.id("card-template");
    html::div card;
    card.cl("card");
    card << h3("Card Title");
    card << p("Card content goes here.");
    tmpl << card;
    container << tmpl;

    pg << container;
    save_page("05_interactive.html", pg);

    CHECK(std::filesystem::exists(get_output_dir() / "05_interactive.html"));
}

TEST_CASE("70050: Bootstrap styled page", "[output][bootstrap]") {
    page pg;
    pg.head << title("Bootstrap Styled Page");
    pg.head << style(resources::bootstrap_css_string());
    pg.head << script(resources::jquery_js_string());
    pg.head << script(resources::bootstrap_js_string());

    // Navigation bar
    nav navbar;
    navbar.cl("navbar navbar-default");
    html::div nav_container;
    nav_container.cl("container-fluid");

    html::div nav_header;
    nav_header.cl("navbar-header");
    anchor brand("Brand");
    brand.cl("navbar-brand").href("#");
    nav_header << brand;
    nav_container << nav_header;

    ul nav_items;
    nav_items.cl("nav navbar-nav");
    li home; home.cl("active"); home << anchor("#", "Home");
    nav_items << home;
    nav_items << li(anchor("#", "Products"));
    nav_items << li(anchor("#", "About"));
    nav_items << li(anchor("#", "Contact"));
    nav_container << nav_items;

    navbar << nav_container;
    pg << navbar;

    // Main container
    bs::container cont;

    // Page header
    html::div page_header;
    page_header.cl("page-header");
    page_header << h1("Dashboard") << small_(" Overview");
    cont << page_header;

    // Row with panels
    bs::row row1;

    // Panel 1
    bs::column col1(4);
    html::div panel1;
    panel1.cl("panel panel-primary");
    html::div panel1_head;
    panel1_head.cl("panel-heading");
    panel1_head << h3("Statistics").cl("panel-title");
    panel1 << panel1_head;
    html::div panel1_body;
    panel1_body.cl("panel-body");
    panel1_body << p("Total Users: ") << strong("1,234");
    panel1_body << p("Active Today: ") << strong("567");
    panel1 << panel1_body;
    col1 << panel1;
    row1 << col1;

    // Panel 2
    bs::column col2(4);
    html::div panel2;
    panel2.cl("panel panel-success");
    html::div panel2_head;
    panel2_head.cl("panel-heading");
    panel2_head << h3("Revenue").cl("panel-title");
    panel2 << panel2_head;
    html::div panel2_body;
    panel2_body.cl("panel-body");
    panel2_body << p("This Month: ") << strong("$45,678");
    panel2_body << p("Last Month: ") << strong("$42,123");
    panel2 << panel2_body;
    col2 << panel2;
    row1 << col2;

    // Panel 3
    bs::column col3(4);
    html::div panel3;
    panel3.cl("panel panel-info");
    html::div panel3_head;
    panel3_head.cl("panel-heading");
    panel3_head << h3("Tasks").cl("panel-title");
    panel3 << panel3_head;
    html::div panel3_body;
    panel3_body.cl("panel-body");
    panel3_body << p("Completed: ") << strong("89%");
    progress task_prog;
    task_prog.value(89).max(100);
    panel3_body << task_prog;
    panel3 << panel3_body;
    col3 << panel3;
    row1 << col3;

    cont << row1;

    // Table in a panel
    html::div table_panel;
    table_panel.cl("panel panel-default");
    html::div table_panel_head;
    table_panel_head.cl("panel-heading");
    table_panel_head << h3("Recent Orders").cl("panel-title");
    table_panel << table_panel_head;

    table orders;
    orders.cl("table table-striped");
    orders.thead << (tr() << th("#") << th("Customer") << th("Product") << th("Amount") << th("Status"));
    orders << (tr() << td("1001") << td("John Doe") << td("Widget Pro") << td("$299") << td() << span("Shipped").cl("label label-success"));
    orders << (tr() << td("1002") << td("Jane Smith") << td("Gadget Plus") << td("$149") << td() << span("Processing").cl("label label-warning"));
    orders << (tr() << td("1003") << td("Bob Wilson") << td("Tool Kit") << td("$89") << td() << span("Pending").cl("label label-default"));
    table_panel << orders;

    cont << table_panel;

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

    // Footer
    footer ftr;
    ftr.cl("text-center");
    ftr.style("margin-top: 30px; padding: 20px; background-color: #f5f5f5;");
    ftr << p("Generated with CPP_HTML_GEN Library");
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
    main_nav.role("navigation").aria_label("Main navigation");
    ul nav_list;
    nav_list << li(anchor("#", "Home"))
             << li(anchor("#", "Products"))
             << li(anchor("#", "Contact"));
    main_nav << nav_list;
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

TEST_CASE("70080: Charts with C3.js", "[output][charts]") {
    page pg;
    pg.head << title("Charts with C3.js");
    pg.head << style(resources::bootstrap_css_string());
    pg.head << style(resources::c3_css_string());
    pg.head << script(resources::d3_js_string());
    pg.head << script(resources::c3_js_string());

    html::div container;
    container.cl("container");

    container << h1("Charts with C3.js");
    container << p("This page demonstrates the built-in chart support using C3.js library.");

    // Line chart
    container << h2("Line Chart");
    chart::line_chart line;
    line.m_sID = "line_chart";
    line.m_sDataName = "Sales";
    line.m_sColor = "#3498db";
    for (double val : {10.0, 25.0, 15.0, 30.0, 22.0, 35.0, 28.0}) {
        line.add(val);
    }
    container << line.html();

    // Bar chart
    container << h2("Bar Chart");
    chart::bar_chart bar;
    bar.m_sID = "bar_chart";
    bar.m_sDataName = "Revenue";
    bar.add("Jan", 120.0);
    bar.add("Feb", 180.0);
    bar.add("Mar", 150.0);
    bar.add("Apr", 200.0);
    bar.add("May", 170.0);
    container << bar.html();

    // Timeseries chart
    container << h2("Timeseries Chart");
    chart::timeseries_line_chart ts;
    ts.m_sID = "ts_chart";
    ts.m_sDataName = "Temperature";
    ts.m_sColor = "#e74c3c";
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
    pg.head << style(resources::c3_css_string());
    pg.head << script(resources::d3_js_string());
    pg.head << script(resources::c3_js_string());

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

    bs::container cont;

    // Summary metrics
    bs::row metrics_row;

    bs::column m1(3);
    html::div metric1;
    metric1.cl("metric-card");
    metric1 << html::div().cl("metric-value") << text("$127,450");
    metric1 << html::div().cl("metric-label") << text("Total Revenue");
    m1 << metric1;
    metrics_row << m1;

    bs::column m2(3);
    html::div metric2;
    metric2.cl("metric-card");
    metric2 << html::div().cl("metric-value") << text("1,847");
    metric2 << html::div().cl("metric-label") << text("Total Orders");
    m2 << metric2;
    metrics_row << m2;

    bs::column m3(3);
    html::div metric3;
    metric3.cl("metric-card");
    metric3 << html::div().cl("metric-value") << text("$69.00");
    metric3 << html::div().cl("metric-label") << text("Avg Order Value");
    m3 << metric3;
    metrics_row << m3;

    bs::column m4(3);
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
    sales_chart.m_sID = "sales_trend";
    sales_chart.m_sDataName = "Revenue ($)";
    sales_chart.m_sColor = "#3498db";
    for (double val : {28500.0, 31200.0, 29800.0, 37950.0}) {
        sales_chart.add(val);
    }
    cont << sales_chart.html();

    // Top products table
    cont << h2("Top Products");
    table products;
    products.cl("table table-striped table-hover");
    products.thead << (tr() << th("Rank") << th("Product") << th("Units Sold") << th("Revenue") << th("Growth"));
    products << (tr() << td("1") << td("Widget Pro") << td("423") << td("$42,300") << td() << span("+23%").cl("text-success"));
    products << (tr() << td("2") << td("Gadget Plus") << td("356") << td("$35,600") << td() << span("+18%").cl("text-success"));
    products << (tr() << td("3") << td("Tool Kit") << td("298") << td("$26,820") << td() << span("+12%").cl("text-success"));
    products << (tr() << td("4") << td("Basic Widget") << td("245") << td("$12,250") << td() << span("-5%").cl("text-danger"));
    products << (tr() << td("5") << td("Mini Gadget") << td("189") << td("$9,450") << td() << span("+8%").cl("text-success"));
    cont << products;

    // Regional breakdown
    cont << h2("Regional Performance");
    chart::bar_chart region_chart;
    region_chart.m_sID = "region_perf";
    region_chart.m_sDataName = "Revenue ($K)";
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
