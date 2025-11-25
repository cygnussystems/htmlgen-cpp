# HtmlGen++

**HTML generation that feels like React, but it's pure C++20.**

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![Header-only friendly](https://img.shields.io/badge/Headers-Included-green.svg)](#installation)

A modern C++20 library for generating HTML programmatically using a fluent, type-safe API. No more string concatenation nightmares, no more unclosed tags, no more runtime HTML errors.

```cpp
// Instead of this error-prone mess:
std::string html = "<div class=\"container\"><h1>" + title + "</h1><p>" + content + "</p></div>";

// Write this:
auto page_content = div(h1(title), p(content)).cl("container");
```

---

## Table of Contents

- [Why HtmlGen++?](#why-htmlgen)
- [Quick Start](#quick-start)
- [Feature Showcase](#feature-showcase)
  - [Fluent Method Chaining](#fluent-method-chaining)
  - [Variadic Constructors](#variadic-constructors)
  - [Reusable Components](#reusable-components)
  - [Dynamic Content](#dynamic-content)
  - [Forms](#forms)
  - [Tables](#tables)
  - [Navigation](#navigation)
- [Coding Styles](#coding-styles)
- [API Reference](#api-reference)
- [Advanced Features](#advanced-features)
- [Installation & Building](#installation--building)
- [Examples Gallery](#examples-gallery)
- [Contributing](#contributing)
- [License](#license)

---

## Why HtmlGen++?

### Type-Safe

Catch errors at compile time, not in the browser. No more debugging unclosed tags or malformed attributes.

```cpp
// Compiler catches typos and type mismatches
input().typo("email");  // Compile error! No such method
```

### Fluent API

Chain methods naturally for clean, readable code. Every method returns the right type for continued chaining.

```cpp
input().type("email")
       .name("email")
       .id("email-field")
       .cl("form-control")
       .placeholder("you@example.com")
       .required()
```

### Modern C++20

Uses variadic templates, perfect forwarding, and modern idioms. Feels natural to modern C++ developers.

```cpp
// Declarative, nested structure - just like JSX
auto content = div(
    h1("Welcome"),
    p("Introduction text"),
    ul(li("Item 1"), li("Item 2"), li("Item 3"))
).cl("container");
```

### No Dependencies

The core library is completely standalone. Just include the headers and go.

### Flexible

Use stream operators for dynamic construction, variadic constructors for declarative style, or mix both seamlessly.

---

## Quick Start

### Minimal Example

```cpp
#include "html_gen.h"
using namespace html;

int main() {
    page pg;
    pg.head << title("My First Page");

    pg << h1("Hello, HtmlGen++!")
       << p("This is a paragraph.")
       << div(
            ul(
                li("Easy to read"),
                li("Easy to write"),
                li("Easy to maintain")
            )
          ).cl("features");

    std::cout << pg;
}
```

### Output

```html
<!DOCTYPE html>
<html>
<head>
<title>My First Page</title>
</head>
<body>
<h1>Hello, HtmlGen++!</h1>
<p>This is a paragraph.</p>
<div class="features">
<ul>
<li>Easy to read</li>
<li>Easy to write</li>
<li>Easy to maintain</li>
</ul>
</div>
</body>
</html>
```

### Add to Your Project (CMake)

```cmake
add_subdirectory(html_gen_cpp)
target_link_libraries(your_target PRIVATE html_gen_cpp)
```

---

## Feature Showcase

### Fluent Method Chaining

The killer feature. Chain any combination of methods in any order - the API always returns the right type.

```cpp
// Build a complete input with all attributes in one expression
auto email_input = input()
    .type("email")
    .name("email")
    .id("email-field")
    .cl("form-control")
    .placeholder("you@example.com")
    .minlength(5)
    .maxlength(100)
    .autocomplete("email")
    .required();

// Works with any element
auto styled_heading = h1("Dashboard")
    .cl("page-title")
    .id("main-title")
    .style("color: #2c3e50;");

// Media elements
auto responsive_video = video()
    .cl("video-player")
    .id("main-video")
    .controls()
    .autoplay()
    .muted()
    .loop();
```

### Variadic Constructors

Build complex nested structures declaratively, just like JSX or HTML templates.

```cpp
// Navigation structure
auto navbar = nav(
    anchor("#", "MyApp").cl("brand"),
    ul(
        li(anchor("/", "Home")),
        li(anchor("/products", "Products")),
        li(anchor("/about", "About")),
        li(anchor("/contact", "Contact"))
    ).cl("nav-links")
).cl("navbar").role("navigation");

// Nested sections
auto article_content = article(
    header(
        h1("Article Title"),
        p("Published on December 1, 2024").cl("meta")
    ),
    section(
        h2("Introduction"),
        p("Opening paragraph...")
    ),
    section(
        h2("Main Content"),
        p("Detailed discussion...")
    ),
    footer(
        p("Written by John Doe")
    )
).cl("blog-post");
```

### Reusable Components

Create your own "components" as simple C++ functions. Return `element` and compose freely.

```cpp
// Define a metric tile component
element metric_tile(const std::string& label, const std::string& value_id) {
    return div(
        span(label).cl("tile-label"),
        br(),
        span().cl("tile-value").id(value_id)
    ).cl("metric-tile");
}

// Define a card component
element card(const std::string& title, element& body) {
    return div(
        div(title).cl("card-header"),
        div(body).cl("card-body")
    ).cl("card");
}

// Define a status badge
element status_badge(const std::string& text, bool is_success) {
    return span(text).cl(is_success ? "badge bg-success" : "badge bg-danger");
}

// Use components in your layout
pg << div(
    metric_tile("Revenue", "rev-value"),
    metric_tile("Orders", "order-count"),
    metric_tile("Customers", "customer-count"),
    metric_tile("Growth", "growth-rate")
).cl("metrics-row");

pg << card("Recent Activity", activity_list);
pg << card("Statistics", stats_table);
```

### Dynamic Content

Use loops and data structures to build content dynamically.

```cpp
// Data structure
struct Product {
    std::string name;
    double price;
    int stock;
    bool available() const { return stock > 0; }
};

std::vector<Product> products = {
    {"Laptop Pro 15\"", 1299.99, 15},
    {"Wireless Mouse", 49.99, 42},
    {"USB-C Hub", 79.99, 0},
    {"Mechanical Keyboard", 149.99, 23}
};

// Build table dynamically
table product_table;
product_table.cl("data-table");

product_table << thead(tr(
    th("Product").scope("col"),
    th("Price").scope("col"),
    th("Stock").scope("col"),
    th("Status").scope("col")
));

tbody table_body;
for (const auto& product : products) {
    table_body << tr(
        td(product.name),
        td("$" + std::to_string(product.price)),
        td(std::to_string(product.stock)),
        td(status_badge(
            product.available() ? "In Stock" : "Out of Stock",
            product.available()
        ))
    );
}
product_table << table_body;
```

### Forms

Build complete forms with Bootstrap-style classes.

```cpp
auto login_form = form(
    // Email field
    div(
        label("Email Address").for_id("email"),
        input().type("email").name("email").id("email")
            .cl("form-control")
            .placeholder("you@example.com")
            .required()
    ).cl("form-group"),

    // Password field
    div(
        label("Password").for_id("password"),
        input().type("password").name("password").id("password")
            .cl("form-control")
            .placeholder("Enter your password")
            .required()
    ).cl("form-group"),

    // Remember me checkbox
    div(
        input().type("checkbox").name("remember").id("remember"),
        label(" Remember me").for_id("remember")
    ).cl("form-check"),

    // Submit button
    button("Sign In").type("submit").cl("btn btn-primary")

).action("/login").method("POST").cl("login-form");
```

### Tables

Full support for semantic table structure with thead, tbody, tfoot.

```cpp
// Complete table with all sections
auto data_table = table(
    caption("Q4 2024 Financial Summary"),
    thead(tr(
        th("Category").scope("col"),
        th("Q3 2024").scope("col"),
        th("Q4 2024").scope("col"),
        th("Change").scope("col")
    )),
    tbody(
        tr(td("Revenue"), td("$1.2M"), td("$1.5M"), td("+25%")),
        tr(td("Expenses"), td("$800K"), td("$850K"), td("+6%")),
        tr(td("Profit"), td("$400K"), td("$650K"), td("+62%"))
    ),
    tfoot(tr(
        td("Total").colspan(3),
        td("$650K").style("font-weight: bold;")
    ))
).cl("table table-striped");

// Table with colgroup for column styling
table styled_table;
styled_table << colgroup(
    col().span(1).style("background: #f0f0f0;"),
    col().span(2).style("background: #e0e0e0;")
);
```

### Navigation

Build navigation structures with semantic HTML5 elements.

```cpp
// Full navbar with dropdown support
pg << nav(
    div(
        anchor("#", "MyApp").cl("navbar-brand"),
        button().cl("navbar-toggler")
            .type("button")
            .data("bs-toggle", "collapse")
            .data("bs-target", "#navbarNav")
    ).cl("container-fluid"),
    div(
        ul(
            li(anchor("/", "Home").cl("nav-link active")).cl("nav-item"),
            li(anchor("/products", "Products").cl("nav-link")).cl("nav-item"),
            li(anchor("/services", "Services").cl("nav-link")).cl("nav-item"),
            li(anchor("/about", "About").cl("nav-link")).cl("nav-item"),
            li(anchor("/contact", "Contact").cl("nav-link")).cl("nav-item")
        ).cl("navbar-nav")
    ).cl("collapse navbar-collapse").id("navbarNav")
).cl("navbar navbar-expand-lg navbar-dark bg-dark");

// Breadcrumb navigation
pg << nav(
    ol(
        li(anchor("/", "Home")).cl("breadcrumb-item"),
        li(anchor("/products", "Products")).cl("breadcrumb-item"),
        li("Laptops").cl("breadcrumb-item active")
    ).cl("breadcrumb")
).aria_label("breadcrumb");
```

---

## Coding Styles

HtmlGen++ supports multiple coding styles. Use whichever fits your needs, or mix them!

### Style 1: Stream Operator

Best for building elements incrementally, in loops, or when structure is determined at runtime.

```cpp
html::div container;
container.cl("card");

html::div title_div;
title_div.cl("card-title");
title_div << text("User Profile");
container << title_div;

ul info_list;
info_list << li("Name: John Doe");
info_list << li("Email: john@example.com");
info_list << li("Role: Administrator");
container << info_list;

pg << container;
```

### Style 2: Variadic Constructor

Best for declarative, tree-like structure definition where the structure is known at compile time.

```cpp
pg << div(
    div("User Profile").cl("card-title"),
    ul(
        li("Name: John Doe"),
        li("Email: john@example.com"),
        li("Role: Administrator")
    )
).cl("card");
```

### Style 3: Mixed (Recommended)

Combine both for maximum flexibility. Use variadic for structure, stream for dynamic content.

```cpp
// Structure defined declaratively
html::div container;
container.cl("card");
container << div("User Profile").cl("card-title");

// Dynamic content built with loop
std::vector<std::pair<std::string, std::string>> user_data = {
    {"Name", "John Doe"},
    {"Email", "john@example.com"},
    {"Role", "Administrator"}
};

ul data_list;
for (const auto& [key, value] : user_data) {
    data_list << li(strong(key + ": "), text(value));
}
container << data_list;

pg << container;
```

---

## API Reference

### Elements

All HTML elements are available in the `html` namespace:

#### Structure
```cpp
div(), span(), p(), br(), hr()
```

#### Headings
```cpp
h1(), h2(), h3(), h4(), h5(), h6()
```

#### Text Formatting
```cpp
strong(), em(), b(), small_(), mark()
code(), pre(), kbd(), samp(), var()
blockquote(), q(), cite_(), abbr(), dfn()
sub(), sup(), ins(), del(), s(), u()
```

#### Links & Media
```cpp
anchor(), img(), video(), audio(), source(), track()
picture(), iframe(), canvas()
```

#### Lists
```cpp
ul(), ol(), li()
```

#### Tables
```cpp
table(), tr(), td(), th()
thead(), tbody(), tfoot(), caption()
colgroup(), col()
```

#### Forms
```cpp
form(), input(), button(), select(), option(), optgroup()
textarea(), label(), fieldset(), legend()
datalist(), output(), progress(), meter()
```

#### Semantic HTML5
```cpp
header(), footer(), nav(), main(), article(), section(), aside()
figure(), figcaption(), address()
time_(), mark()
```

#### Interactive
```cpp
details(), summary(), dialog(), template_()
```

#### Page Structure
```cpp
page, title(), meta(), script(), style(), head_link()
```

### Chainable Attribute Methods

Available on all elements:

```cpp
element.id("my-id")              // Set ID
element.cl("class1 class2")      // Set class(es)
element.add_cl("extra")          // Add class (preserves existing)
element.style("color: red")      // Inline style
element.type("button")           // Type attribute
element.role("navigation")       // ARIA role
element.hidden()                 // Hidden attribute
element.tabindex(0)              // Tab index
element.title("Tooltip text")    // Title attribute
element.aria_label("Label")      // ARIA label
element.data("key", "value")     // data-* attributes
element.add_attr("name", "val")  // Any custom attribute
```

### Element-Specific Methods

#### Form Elements
```cpp
// input
input().name("field").value("default")
       .placeholder("Enter text").required()
       .disabled().readonly().checked()
       .min("0").max("100").step("1")
       .minlength(3).maxlength(100)
       .pattern("[A-Za-z]+").autocomplete("email")
       .autofocus().list("datalist-id")

// form
form().action("/submit").method("POST")
      .enctype("multipart/form-data")
      .target("_blank").novalidate()

// select
select().name("choice").multiple().required().size(5)

// option
option("value", "Display Text").selected().disabled()

// label
label("Label Text").for_id("input-id")

// button
button("Click").name("btn").value("clicked").disabled()

// textarea - inherits from element
textarea("Default content")

// progress
progress().value(75).max(100)

// meter
meter().value(0.7).min(0).max(1).low(0.3).high(0.8).optimum(0.5)
```

#### Table Elements
```cpp
// td/th
td("Content").colspan(2).rowspan(3).headers("col1")
th("Header").scope("col").abbr("Short")

// col/colgroup
col().span(2)
colgroup().span(3)
```

#### Media Elements
```cpp
// video
video().controls().autoplay().loop().muted()
       .poster("thumb.jpg").preload("auto").playsinline()

// audio
audio().controls().autoplay().loop().muted().preload("metadata")

// img
img("image.jpg").alt("Description").loading("lazy").decoding("async")

// source
source("video.mp4", "video/mp4").media("(min-width: 800px)")

// track
track().kind("subtitles").srclang("en").label("English").default_()

// iframe
iframe().sandbox("allow-scripts").allow("fullscreen")
        .loading("lazy").name("frame-name")
```

#### Link Elements
```cpp
anchor("https://example.com", "Click here")
    .target("_blank")
    .download("filename.pdf")
```

#### Interactive Elements
```cpp
details().open()
dialog().open()
```

#### Semantic Elements
```cpp
time_("December 2024").datetime("2024-12")
blockquote("Quote text").cite("https://source.com")
ins("Added text").cite("reason").datetime("2024-01-01")
del("Removed text").cite("reason").datetime("2024-01-01")
```

### Content Methods

```cpp
element.add(child_element)        // Add child element
element << child_element          // Stream operator (same as add)
element.add(text("string"))       // Add text content
element.content("text")           // Replace all content with text
element.clear()                   // Remove all children
element.empty()                   // Check if has no children
element.size()                    // Number of children
```

### Element Access

```cpp
element.get("id")                 // Get by ID (throws if not found)
element.find("id")                // Find by ID (returns nullptr if not found)
element.exists("id")              // Check if ID exists
element["id"]                     // Shorthand for get()
element[0]                        // Access child by index
```

### Output

```cpp
std::cout << pg;                  // Stream entire page
std::string html = pg.html();     // Get page as string
element.html_string()             // Get element HTML as string
```

---

## Advanced Features

### Finding and Modifying Elements

Access elements by ID after creation:

```cpp
page pg;
pg << div().id("content")
   << p("Initial status").id("status")
   << span("0").id("counter");

// Later, find and modify elements
pg.get("status").content("Loading complete!");
pg["content"] << p("New paragraph added dynamically");

// Check if element exists before modifying
if (pg.exists("optional-section")) {
    pg.get("optional-section").cl("found").style("display: block;");
}

// Access by index
pg[0].add_cl("first-element");
```

### Bootstrap Integration

Use Bootstrap with embedded resources or CDN:

```cpp
#include "html_gen_resources.h"

page pg;

// Option 1: Embedded (no external dependencies, larger file)
pg.head << style(resources::bootstrap_css_string());
// ... at end of body:
pg << script(resources::bootstrap_js_string());

// Option 2: CDN (smaller file size, requires internet)
pg.require(dependency::bootstrap_css);
pg.require(dependency::bootstrap_js);
// Dependencies are automatically added to output
```

### Charts with ApexCharts

Built-in charting support:

```cpp
#include "html_gen_charts.h"

// Line chart
chart::line_chart sales_chart;
sales_chart.m_id = "sales_chart";
sales_chart.m_data_name = "Monthly Sales";
sales_chart.m_color = "#3498db";

sales_chart.add(1200.0);
sales_chart.add(1900.0);
sales_chart.add(1500.0);
sales_chart.add(2100.0);
sales_chart.add(1800.0);

pg << sales_chart.html();  // Auto-registers ApexCharts dependency

// Bar chart
chart::bar_chart revenue_chart;
revenue_chart.m_id = "revenue_chart";
// ... configure and add data

// Time series
chart::timeseries_line_chart time_chart;
time_chart.m_id = "time_chart";
// ... configure with timestamps
```

### HTML Escaping

Automatically escape user input to prevent XSS:

```cpp
std::string user_input = "<script>alert('xss')</script>";

// Safe - content is escaped
pg << p(html_escape(user_input));
// Output: <p>&lt;script&gt;alert('xss')&lt;/script&gt;</p>

// For trusted HTML content only
pg << raw_html("<div class='trusted'>Pre-validated HTML</div>");
```

### Custom Component Pattern

Build complex reusable components:

```cpp
// A complete card component with optional footer
element card_component(
    const std::string& title,
    element& body,
    const std::string& footer_text = ""
) {
    html::div card_div;
    card_div.cl("card");

    // Header
    html::div header;
    header.cl("card-header");
    header << h5(title);
    card_div << header;

    // Body
    html::div body_div;
    body_div.cl("card-body");
    body_div << body;
    card_div << body_div;

    // Optional footer
    if (!footer_text.empty()) {
        html::div footer;
        footer.cl("card-footer text-muted");
        footer << small_(footer_text);
        card_div << footer;
    }

    return card_div;
}

// Alert component
element alert_box(const std::string& message, const std::string& type = "info") {
    return div(
        strong(type == "danger" ? "Error! " : type == "warning" ? "Warning! " : "Info: "),
        text(message)
    ).cl("alert alert-" + type).role("alert");
}

// Modal component
element modal(const std::string& id, const std::string& title, element& content) {
    return div(
        div(
            div(
                div(
                    h5(title).cl("modal-title"),
                    button().type("button").cl("btn-close")
                        .data("bs-dismiss", "modal")
                ).cl("modal-header"),
                div(content).cl("modal-body"),
                div(
                    button("Close").type("button").cl("btn btn-secondary")
                        .data("bs-dismiss", "modal"),
                    button("Save").type("button").cl("btn btn-primary")
                ).cl("modal-footer")
            ).cl("modal-content")
        ).cl("modal-dialog")
    ).cl("modal fade").id(id).tabindex(-1);
}
```

---

## Installation & Building

### Requirements

- C++20 compatible compiler:
  - MSVC 2022 (Visual Studio 17.0+)
  - GCC 10+
  - Clang 12+
- CMake 3.15+
- (Optional) vcpkg with Catch2 for testing

### Building

```bash
# Clone the repository
git clone https://github.com/yourusername/html_gen_cpp.git
cd html_gen_cpp

# Create build directory
mkdir build && cd build

# Configure (choose your generator)
cmake .. -G "Visual Studio 17 2022"      # Windows
cmake .. -G "Unix Makefiles"              # Linux/Mac

# Build
cmake --build . --config Release
```

### Building with Tests

Requires Catch2 (install via vcpkg):

```bash
# Install Catch2
vcpkg install catch2

# Configure with vcpkg toolchain
cmake .. -DBUILD_TESTING=ON \
         -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake

# Build and run tests
cmake --build . --config Debug
ctest --output-on-failure

# Run specific test executable directly
./tests/Debug/test_html_tags.exe          # Windows
./tests/test_html_tags                     # Linux/Mac

# Verbose output (shows all assertions)
./tests/Debug/test_html_tags.exe -s

# Run tests by tag
./tests/Debug/test_html_tags.exe "[chart]"
./tests/Debug/test_html_tags.exe "[page]"
./tests/Debug/test_html_tags.exe "[fluent]"
```

### Using in Your Project

**Option 1: Add as subdirectory**
```cmake
add_subdirectory(html_gen_cpp)
target_link_libraries(your_target PRIVATE html_gen_cpp)
```

**Option 2: Install and find**
```cmake
find_package(html_gen_cpp REQUIRED)
target_link_libraries(your_target PRIVATE html_gen_cpp::html_gen_cpp)
```

**Option 3: Header-only usage**

Copy the `include/` directory to your project and add to include path:
```cmake
target_include_directories(your_target PRIVATE path/to/html_gen_cpp/include)
```

---

## Examples Gallery

The test suite includes comprehensive examples that generate actual HTML files:

### Generated Examples

Run the tests to generate example HTML files in `tests/output/`:

| File | Description |
|------|-------------|
| `showcase_table.html` | Dynamic table with data and status badges |
| `showcase_components.html` | Dashboard with reusable tile components |
| `showcase_form.html` | Bootstrap-style login form |
| `showcase_dashboard.html` | Complex financial dashboard layout |
| `showcase_navigation.html` | Navigation menu structure |
| `showcase_styles.html` | Comparison of coding styles |

### View Examples

```bash
# Build and run tests
cd build
ctest

# Open generated files
# Windows:
start tests/output/showcase_dashboard.html

# Mac:
open tests/output/showcase_dashboard.html

# Linux:
xdg-open tests/output/showcase_dashboard.html
```

---

## Project Structure

```
html_gen_cpp/
├── include/                      # Header files
│   ├── html_gen.h                # Main include (pulls in all core headers)
│   ├── html_gen_charts.h         # ApexCharts integration
│   ├── html_gen_resources.h      # Embedded Bootstrap/ApexCharts
│   ├── html_core.h               # Core element class and utilities
│   ├── html_forward.h            # Forward declarations
│   ├── html_basic.h              # Basic elements (div, p, span, etc.)
│   ├── html_table.h              # Table elements
│   ├── html_form.h               # Form elements
│   ├── html_semantic.h           # Semantic HTML5 elements
│   ├── html_media.h              # Media elements
│   ├── html_interactive.h        # Interactive elements
│   └── html_misc.h               # Miscellaneous elements
├── src/                          # Implementation files
│   ├── html_gen.cpp
│   ├── html_gen_charts.cpp
│   └── resources/                # Embedded resource files
├── tests/                        # Catch2 tests
│   ├── test_10_basic_elements.cpp
│   ├── test_12_fluent_api.cpp    # Fluent API tests
│   ├── test_20_table_elements.cpp
│   ├── test_21_form_elements.cpp
│   ├── test_40_showcase.cpp      # Showcase examples
│   └── output/                   # Generated HTML files
├── CMakeLists.txt
├── README.md
└── LICENSE
```

---

## Contributing

Contributions are welcome! Please feel free to submit issues and pull requests.

### Development Setup

1. Fork the repository
2. Clone your fork
3. Create a feature branch: `git checkout -b feature/my-feature`
4. Make your changes
5. Run tests: `ctest --output-on-failure`
6. Commit: `git commit -m "Add my feature"`
7. Push: `git push origin feature/my-feature`
8. Open a Pull Request

### Code Style

- Follow modern C++20 conventions
- Use fluent interface patterns
- Add tests for new features
- Update documentation as needed

---

## License

MIT License - see [LICENSE](LICENSE) file.

Copyright (c) 2015-2024 Peter Ritter

---

## Acknowledgments

- Built with modern C++20
- Charts powered by [ApexCharts](https://apexcharts.com/)
- Optional Bootstrap integration via [Bootstrap](https://getbootstrap.com/)
- Testing with [Catch2](https://github.com/catchorg/Catch2)

---

**Made with C++ for C++ developers who want clean, type-safe HTML generation.**
