/*  ===================================================================
*                         HtmlGen++
*            Copyright (c) 2015-2024 Peter Ritter
*                  Licensed under MIT License
*  ====================================================================
*
*  Showcase examples demonstrating HtmlGen++ capabilities.
*  These examples are referenced in README.md documentation.
*  Run tests to generate HTML files in tests/output/
*/

#include <catch2/catch_all.hpp>
#include <fstream>
#include <filesystem>
#include <vector>
#include "../include/html_gen.h"
#include "../include/html_gen_resources.h"

using namespace html;

namespace {

// Helper to get output directory
std::filesystem::path get_output_dir() {
    return std::filesystem::path(__FILE__).parent_path() / "output";
}

// Helper to save page to file
void save_page(const std::string& filename, page& pg) {
    auto output_dir = get_output_dir();
    std::filesystem::create_directories(output_dir);
    std::ofstream file(output_dir / filename);
    file << pg.html();
}

//=============================================================================
// REUSABLE COMPONENT FUNCTIONS
// These demonstrate how to create your own "components" as functions
//=============================================================================

// Metric tile - displays a title and value
element metric_tile(const std::string& title_text, const std::string& value_id) {
    return html::div(
        span(title_text).cl("tile-title"),
        br(),
        span().cl("tile-value").id(value_id)
    ).cl("metric-tile");
}

// Status badge - colored based on status
element status_badge(const std::string& status, bool is_ok) {
    return span(status).cl(is_ok ? "badge bg-success" : "badge bg-danger");
}

// Card component with header and body
element card(const std::string& title_text, element& body_content) {
    html::div card_div;
    card_div.cl("card");
    html::div header;
    header.cl("card-header");
    header << text(title_text);
    card_div << header;
    html::div body;
    body.cl("card-body");
    body << body_content;
    card_div << body;
    return card_div;
}

// Alert box
element alert(const std::string& message, const std::string& type = "info") {
    html::div alert_div;
    alert_div.cl("alert alert-" + type).role("alert");
    alert_div << text(message);
    return alert_div;
}

//=============================================================================
// SHOWCASE CSS - Used by multiple examples
//=============================================================================

const char* showcase_css = R"(
body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    margin: 20px;
    background-color: #f5f5f5;
}

/* Metric Tiles */
.metric-tile {
    display: inline-block;
    background: white;
    border: 1px solid #ddd;
    border-radius: 8px;
    padding: 15px 25px;
    margin: 10px;
    text-align: center;
    box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}

.metric-tile .tile-title {
    font-size: 14px;
    color: #666;
    text-transform: uppercase;
}

.metric-tile .tile-value {
    font-size: 28px;
    font-weight: bold;
    color: #333;
}

/* Dashboard Cards */
.dashboard-card {
    background: white;
    border-radius: 8px;
    padding: 20px;
    margin: 15px 0;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
}

.dashboard-card .card-title {
    font-size: 18px;
    font-weight: 600;
    color: #2c3e50;
    margin-bottom: 15px;
    padding-bottom: 10px;
    border-bottom: 2px solid #3498db;
}

/* Flex Layouts */
.flex-row {
    display: flex;
    gap: 20px;
    flex-wrap: wrap;
}

.flex-center {
    display: flex;
    justify-content: center;
    align-items: center;
}

/* Tables */
.data-table {
    width: 100%;
    border-collapse: collapse;
    background: white;
    border-radius: 8px;
    overflow: hidden;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
}

.data-table th {
    background: #3498db;
    color: white;
    padding: 12px 15px;
    text-align: left;
    font-weight: 600;
}

.data-table td {
    padding: 12px 15px;
    border-bottom: 1px solid #eee;
}

.data-table tr:hover {
    background: #f8f9fa;
}

/* Status Badges */
.badge {
    display: inline-block;
    padding: 4px 12px;
    border-radius: 20px;
    font-size: 12px;
    font-weight: 600;
}

.badge.bg-success {
    background: #27ae60;
    color: white;
}

.badge.bg-danger {
    background: #e74c3c;
    color: white;
}

.badge.bg-warning {
    background: #f39c12;
    color: white;
}

.badge.bg-info {
    background: #3498db;
    color: white;
}

/* Navigation */
.navbar {
    background: #2c3e50;
    padding: 15px 30px;
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.navbar .brand {
    color: white;
    font-size: 24px;
    font-weight: bold;
    text-decoration: none;
}

.navbar .nav-links {
    display: flex;
    gap: 30px;
    list-style: none;
    margin: 0;
    padding: 0;
}

.navbar .nav-links a {
    color: #ecf0f1;
    text-decoration: none;
    font-size: 16px;
    transition: color 0.3s;
}

.navbar .nav-links a:hover {
    color: #3498db;
}

/* Forms */
.form-group {
    margin-bottom: 20px;
}

.form-group label {
    display: block;
    margin-bottom: 5px;
    font-weight: 600;
    color: #333;
}

.form-control {
    width: 100%;
    padding: 10px 15px;
    border: 1px solid #ddd;
    border-radius: 4px;
    font-size: 16px;
    box-sizing: border-box;
}

.form-control:focus {
    outline: none;
    border-color: #3498db;
    box-shadow: 0 0 0 3px rgba(52,152,219,0.2);
}

.btn {
    padding: 12px 24px;
    border: none;
    border-radius: 4px;
    font-size: 16px;
    cursor: pointer;
    transition: background 0.3s;
}

.btn-primary {
    background: #3498db;
    color: white;
}

.btn-primary:hover {
    background: #2980b9;
}

/* Price Display */
.price-display {
    background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
    color: white;
    padding: 30px;
    border-radius: 12px;
    text-align: center;
}

.price-display .currency {
    font-size: 24px;
    vertical-align: top;
}

.price-display .amount {
    font-size: 64px;
    font-weight: bold;
}

.price-display .cents {
    font-size: 32px;
    vertical-align: top;
}

.price-display .label {
    font-size: 14px;
    opacity: 0.8;
    margin-top: 10px;
}
)";

} // anonymous namespace

//=============================================================================
// SHOWCASE 1: Dynamic Table Generation
// Demonstrates using loops to build tables from data
//=============================================================================

TEST_CASE("40010: Dynamic table generation from data", "[showcase]") {
    // Sample data - in real app, this would come from database/API
    struct Product {
        std::string name;
        double price;
        int stock;
        bool in_stock() const { return stock > 0; }
    };

    std::vector<Product> products = {
        {"Laptop Pro 15\"", 1299.99, 15},
        {"Wireless Mouse", 49.99, 42},
        {"USB-C Hub", 79.99, 0},
        {"Mechanical Keyboard", 149.99, 23},
        {"4K Monitor 27\"", 449.99, 8},
        {"Webcam HD", 89.99, 0},
        {"Laptop Stand", 59.99, 31}
    };

    page pg;
    pg.head << title("Product Inventory");
    pg.head << style(showcase_css);

    pg << h1("Product Inventory");
    pg << p("Demonstrating dynamic table generation with loops.");

    // Build table dynamically
    table product_table;
    product_table.cl("data-table");

    // Header row using variadic constructor
    product_table << thead(
        tr(
            th("Product").scope("col"),
            th("Price").scope("col"),
            th("Stock").scope("col"),
            th("Status").scope("col")
        )
    );

    // Body with dynamic rows
    tbody table_body;
    for (const auto& product : products) {
        table_body << tr(
            td(product.name),
            td("$" + std::to_string(product.price).substr(0, std::to_string(product.price).find('.') + 3)),
            td(std::to_string(product.stock)),
            td(status_badge(
                product.in_stock() ? "In Stock" : "Out of Stock",
                product.in_stock()
            ))
        );
    }
    product_table << table_body;

    pg << product_table;

    // Summary section
    int total_products = products.size();
    int in_stock_count = 0;
    for (const auto& p : products) if (p.in_stock()) in_stock_count++;

    pg << html::div(
        metric_tile("Total Products", "total"),
        metric_tile("In Stock", "in_stock"),
        metric_tile("Out of Stock", "out_stock")
    ).cl("flex-row").style("margin-top: 30px;");

    // Script to populate values
    pg << script(R"(
        document.getElementById('total').textContent = ')" + std::to_string(total_products) + R"(';
        document.getElementById('in_stock').textContent = ')" + std::to_string(in_stock_count) + R"(';
        document.getElementById('out_stock').textContent = ')" + std::to_string(total_products - in_stock_count) + R"(';
    )");

    save_page("showcase_table.html", pg);
    CHECK(std::filesystem::exists(get_output_dir() / "showcase_table.html"));
}

//=============================================================================
// SHOWCASE 2: Reusable Component Functions
// Demonstrates creating reusable "components" as C++ functions
//=============================================================================

TEST_CASE("40020: Reusable tile components", "[showcase]") {
    page pg;
    pg.head << title("Dashboard with Reusable Components");
    pg.head << style(showcase_css);

    pg << h1("Sales Dashboard");
    pg << p("Demonstrating reusable component functions.");

    // Row of metric tiles
    pg << html::div(
        metric_tile("Revenue", "revenue"),
        metric_tile("Orders", "orders"),
        metric_tile("Customers", "customers"),
        metric_tile("Avg. Order", "avg_order")
    ).cl("flex-row");

    // Cards using the card component
    html::div chart_placeholder;
    chart_placeholder << p("Chart would go here").style("color: #999; text-align: center; padding: 50px;");

    html::div recent_orders;
    recent_orders << ul(
        li("Order #1234 - $150.00"),
        li("Order #1235 - $89.99"),
        li("Order #1236 - $245.50")
    );

    html::div sales_card;
    sales_card.cl("dashboard-card").style("flex: 2;");
    html::div sales_title;
    sales_title.cl("card-title");
    sales_title << text("Sales Trend");
    sales_card << sales_title << chart_placeholder;

    html::div orders_card;
    orders_card.cl("dashboard-card").style("flex: 1;");
    html::div orders_title;
    orders_title.cl("card-title");
    orders_title << text("Recent Orders");
    orders_card << orders_title << recent_orders;

    pg << html::div(sales_card, orders_card).cl("flex-row");

    // Populate with sample data
    pg << script(R"(
        document.getElementById('revenue').textContent = '$45,231';
        document.getElementById('orders').textContent = '156';
        document.getElementById('customers').textContent = '89';
        document.getElementById('avg_order').textContent = '$289.94';
    )");

    save_page("showcase_components.html", pg);
    CHECK(std::filesystem::exists(get_output_dir() / "showcase_components.html"));
}

//=============================================================================
// SHOWCASE 3: Bootstrap-Style Form
// Demonstrates form building with modern styling
//=============================================================================

TEST_CASE("40030: Bootstrap-style login form", "[showcase]") {
    page pg;
    pg.head << title("Login Form");
    pg.head << style(showcase_css);

    // Build form using stream operator (form doesn't have variadic constructor)
    form login_form;
    login_form.action("/login").method("POST");

    // Email field
    html::div email_group;
    email_group.cl("form-group");
    email_group << label("Email Address").for_id("email");
    email_group << input().name("email").type("email").id("email")
        .cl("form-control")
        .placeholder("you@example.com")
        .required();
    login_form << email_group;

    // Password field
    html::div password_group;
    password_group.cl("form-group");
    password_group << label("Password").for_id("password");
    password_group << input().name("password").type("password").id("password")
        .cl("form-control")
        .placeholder("Enter your password")
        .required();
    login_form << password_group;

    // Remember me checkbox
    html::div remember_group;
    remember_group.cl("form-group");
    remember_group << input().name("remember").type("checkbox").id("remember");
    remember_group << label(" Remember me").for_id("remember").style("font-weight: normal; margin-left: 5px;");
    login_form << remember_group;

    // Submit button
    login_form << button("Sign In").type("submit").cl("btn btn-primary").style("width: 100%;");

    // Build the container
    html::div container;
    container.style("max-width: 400px; margin: 50px auto; background: white; padding: 40px; border-radius: 8px; box-shadow: 0 4px 12px rgba(0,0,0,0.1);");
    container << h2("Sign In");
    container << p("Please enter your credentials").style("color: #666;");
    container << login_form;
    container << p(
        text("Don't have an account? "),
        anchor("#", "Sign up")
    ).style("text-align: center; margin-top: 20px;");

    pg << container;

    save_page("showcase_form.html", pg);
    CHECK(std::filesystem::exists(get_output_dir() / "showcase_form.html"));
}

//=============================================================================
// SHOWCASE 4: Dashboard with Complex Nested Structure
// Demonstrates deeply nested variadic constructors
//=============================================================================

TEST_CASE("40040: Dashboard with nested structure", "[showcase]") {
    page pg;
    pg.head << title("Financial Dashboard");
    pg.head << style(showcase_css);

    // Build dashboard using stream operators
    html::div dashboard_container;
    dashboard_container.style("max-width: 900px; margin: 0 auto;");

    // Header section
    html::div header_section;
    header_section.style("margin-bottom: 30px;");
    header_section << h1("Financial Overview");
    header_section << p("Q4 2024 Performance").style("color: #666;");
    dashboard_container << header_section;

    // Left: Net Profit display
    html::div net_profit_card;
    net_profit_card.cl("dashboard-card").style("flex: 1;");
    html::div np_title;
    np_title.cl("card-title");
    np_title << text("Net Profit");
    net_profit_card << np_title;
    net_profit_card << html::div(
        span("$").cl("currency"),
        span("127,450").cl("amount"),
        span(".89").cl("cents")
    ).cl("price-display");
    html::div usd_label;
    usd_label.cl("label").style("text-align: center; margin-top: 10px; color: #666;");
    usd_label << text("USD");
    net_profit_card << usd_label;

    // Right: Key metrics
    html::div metrics_card;
    metrics_card.cl("dashboard-card").style("flex: 1;");
    html::div metrics_title;
    metrics_title.cl("card-title");
    metrics_title << text("Key Metrics");
    metrics_card << metrics_title;
    metrics_card << table(
        tr(td("Gross Revenue"), td("$234,500.00").style("text-align: right; font-weight: bold;")),
        tr(td("Operating Costs"), td("$89,234.11").style("text-align: right; color: #e74c3c;")),
        tr(td("Tax (21%)"), td("$17,815.00").style("text-align: right; color: #e74c3c;")),
        tr(td("Net Profit"), td("$127,450.89").style("text-align: right; color: #27ae60; font-weight: bold;"))
    ).style("width: 100%;");
    metrics_card << html::div(
        span("Period: "),
        span("Oct 1 - Dec 31, 2024").style("font-weight: bold;")
    ).style("margin-top: 15px; color: #666; font-size: 14px;");

    // Main content row
    dashboard_container << html::div(net_profit_card, metrics_card).cl("flex-row");

    // Bottom: Quick stats
    dashboard_container << html::div(
        metric_tile("Transactions", "txn_count"),
        metric_tile("Avg. Transaction", "avg_txn"),
        metric_tile("Growth Rate", "growth"),
        metric_tile("Profit Margin", "margin")
    ).cl("flex-row").style("justify-content: center; margin-top: 20px;");

    pg << dashboard_container;

    pg << script(R"(
        document.getElementById('txn_count').textContent = '1,247';
        document.getElementById('avg_txn').textContent = '$188.05';
        document.getElementById('growth').textContent = '+12.4%';
        document.getElementById('margin').textContent = '54.3%';
    )");

    save_page("showcase_dashboard.html", pg);
    CHECK(std::filesystem::exists(get_output_dir() / "showcase_dashboard.html"));
}

//=============================================================================
// SHOWCASE 5: Navigation Menu
// Demonstrates building navigation structures
//=============================================================================

TEST_CASE("40050: Navigation with structure", "[showcase]") {
    page pg;
    pg.head << title("Navigation Example");
    pg.head << style(showcase_css);

    // Navigation bar
    pg << nav(
        anchor("#", "MyApp").cl("brand"),
        ul(
            li(anchor("#", "Home")),
            li(anchor("#", "Products")),
            li(anchor("#", "Services")),
            li(anchor("#", "About")),
            li(anchor("#", "Contact"))
        ).cl("nav-links")
    ).cl("navbar");

    // Page content
    pg << html::div(
        h1("Welcome to MyApp"),
        p("This example demonstrates navigation structure building."),

        h2("Features"),
        ul(
            li(strong("Fluent API"), text(" - Chain methods for clean code")),
            li(strong("Type-safe"), text(" - Catch errors at compile time")),
            li(strong("Modern C++20"), text(" - Uses latest language features")),
            li(strong("No dependencies"), text(" - Core library is standalone"))
        ),

        html::div(
            button("Get Started").cl("btn btn-primary"),
            anchor("#", "Learn More").style("margin-left: 15px;")
        ).style("margin-top: 30px;")
    ).style("max-width: 800px; margin: 40px auto; padding: 0 20px;");

    save_page("showcase_navigation.html", pg);
    CHECK(std::filesystem::exists(get_output_dir() / "showcase_navigation.html"));
}

//=============================================================================
// SHOWCASE 6: Two Coding Styles Comparison
// Shows stream operator vs variadic constructor
//=============================================================================

TEST_CASE("40060: Two coding styles comparison", "[showcase]") {
    page pg;
    pg.head << title("Coding Styles Comparison");
    pg.head << style(showcase_css);

    pg << h1("Two Ways to Write the Same Thing");

    // Style 1: Stream operator (traditional)
    pg << h2("Style 1: Stream Operator");
    pg << p("Good for building elements incrementally or in loops.");

    html::div container1;
    container1.cl("dashboard-card");
    html::div title1;
    title1 << text("User Profile");
    title1.cl("card-title");
    container1 << title1;

    ul info_list;
    info_list << li("Name: John Doe");
    info_list << li("Email: john@example.com");
    info_list << li("Role: Administrator");
    container1 << info_list;

    pg << container1;

    // Style 2: Variadic constructor (modern)
    pg << h2("Style 2: Variadic Constructor");
    pg << p("Great for defining structure in a declarative way.");

    html::div container2;
    container2.cl("dashboard-card");
    html::div title2;
    title2.cl("card-title");
    title2 << text("User Profile");
    container2 << title2;
    container2 << ul(
        li("Name: John Doe"),
        li("Email: john@example.com"),
        li("Role: Administrator")
    );
    pg << container2;

    // Style 3: Mixed (recommended)
    pg << h2("Style 3: Mixed (Recommended)");
    pg << p("Combine both styles for maximum flexibility.");

    html::div container3;
    container3.cl("dashboard-card");
    html::div title3;
    title3.cl("card-title");
    title3 << text("User Profile");
    container3 << title3;

    // Use loop to build list
    std::vector<std::pair<std::string, std::string>> user_data = {
        {"Name", "John Doe"},
        {"Email", "john@example.com"},
        {"Role", "Administrator"}
    };

    ul data_list;
    for (const auto& [key, value] : user_data) {
        data_list << li(strong(key + ": "), text(value));
    }
    container3 << data_list;

    pg << container3;

    save_page("showcase_styles.html", pg);
    CHECK(std::filesystem::exists(get_output_dir() / "showcase_styles.html"));
}
