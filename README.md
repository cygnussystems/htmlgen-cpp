# HtmlGen++

A modern C++20 library for generating HTML programmatically using a fluent, type-safe API.

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.cppreference.com/w/cpp/20)

## Features

- **Fluent API** - Chain method calls for clean, readable code
- **Type-safe** - Catch errors at compile time, not runtime
- **Modern C++20** - Uses `std::format`, variadic templates, and modern idioms
- **No external dependencies** - Core library is standalone
- **Bootstrap 5 support** - Embedded CSS/JS resources
- **ApexCharts integration** - Built-in charting support
- **Automatic resource management** - Dependencies auto-register when used

## Quick Example

```cpp
#include "html_tags.h"
using namespace html;

int main() {
    page pg;
    pg.head << title("My Page");

    pg << h1("Welcome")
       << p("This is a paragraph.")
       << div(
            ul(
                li("Item 1"),
                li("Item 2"),
                li("Item 3")
            )
          ).cl("container");

    std::cout << pg;
}
```

Output:
```html
<!DOCTYPE html>
<html>
<head><title>My Page</title></head>
<body>
<h1>Welcome</h1>
<p>This is a paragraph.</p>
<div class="container">
<ul><li>Item 1</li><li>Item 2</li><li>Item 3</li></ul>
</div>
</body>
</html>
```

## Installation

### Requirements

- C++20 compatible compiler (MSVC 2022, GCC 10+, Clang 12+)
- CMake 3.15+
- (Optional) vcpkg with Catch2 for testing

### Building

```bash
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022"  # or your preferred generator
cmake --build . --config Release
```

To build with tests (requires Catch2):
```bash
cmake .. -DBUILD_TESTING=ON -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
```

### Using in Your Project

Add as a subdirectory:
```cmake
add_subdirectory(html_gen_cpp)
target_link_libraries(your_target PRIVATE html_gen_cpp)
```

Or install and find:
```cmake
find_package(html_gen_cpp REQUIRED)
target_link_libraries(your_target PRIVATE html_gen_cpp::html_gen_cpp)
```

## API Overview

### Elements

All HTML elements are available in the `html` namespace:

```cpp
// Basic elements
div(), span(), p(), h1(), h2(), h3(), h4(), h5(), h6()
a(), img(), br(), hr()

// Lists
ul(), ol(), li()

// Tables
table(), tr(), td(), th(), thead(), tbody(), tfoot()

// Forms
form(), input(), button(), select(), option(), label(), textarea()

// Semantic HTML5
header(), footer(), nav(), main(), article(), section(), aside()

// Media
video(), audio(), source()
```

### Attributes

Chain attributes using fluent methods:

```cpp
div()
    .id("main")
    .cl("container fluid")    // class
    .style("color: red")
    .add_attr("data-value", "42");

input()
    .type("text")
    .name("username")
    .placeholder("Enter name")
    .required();

anchor("Click me")
    .href("/page")
    .target("_blank");
```

### Nesting Elements

Use `<<` operator or variadic constructors:

```cpp
// Stream operator
div container;
container << h1("Title") << p("Content");

// Variadic constructor (C++20)
auto content = div(
    h1("Title"),
    p("First paragraph"),
    p("Second paragraph")
);

// Combining with +
auto group = h1("Title") + p("Content") + footer("Footer");
```

### Finding and Modifying Elements

```cpp
page pg;
pg << div().id("content") << p().id("status");

// Later, find and modify
pg.get("status").content("Updated!");
pg["content"] << p("New paragraph");

if (pg.exists("optional")) {
    pg.get("optional").cl("found");
}
```

### Bootstrap Integration

```cpp
#include "html_gen_resources.h"

page pg;
pg.head << style(resources::bootstrap_css_string());
pg.head << script(resources::bootstrap_js_string());

// Or use CDN
pg.require(dependency::bootstrap_css);
pg.require(dependency::bootstrap_js);
```

### Charts (ApexCharts)

```cpp
#include "html_gen_charts.h"

chart::line_chart line;
line.m_id = "sales_chart";
line.m_data_name = "Sales";
line.m_color = "#3498db";
line.add(10.0);
line.add(25.0);
line.add(15.0);

pg << line.html();  // Auto-registers ApexCharts dependency
```

## Project Structure

```
html_gen_cpp/
├── include/           # Header files
│   ├── html_tags.h    # Main include
│   ├── html_core.h    # Core element classes
│   ├── html_gen_charts.h  # ApexCharts integration
│   └── ...
├── src/               # Implementation files
├── tests/             # Catch2 tests
└── CMakeLists.txt
```

## License

MIT License - see [LICENSE](LICENSE) file.

## Contributing

Contributions welcome! Please open an issue or pull request.
