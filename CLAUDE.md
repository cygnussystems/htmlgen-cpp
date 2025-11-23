# CPP_HTML_GEN

## Project Overview

A modern C++20 library for generating HTML from code. Developers can create HTML documents programmatically using a fluent interface with element classes like `div`, `p`, `table`, `form`, etc.

## Development Environment

- IDE: CLion (recommended) or Visual Studio 2022
- Language: C++20
- Build System: CMake 3.15+
- Testing: Catch2 (via vcpkg)

## Project Structure

```
CPP_HTML_GEN/
├── .claude/              # Claude Code configuration
├── .idea/                # IDE configuration
├── include/              # Header files
│   ├── html_tags.h       # Core HTML elements
│   └── bootstrap.h       # Bootstrap components & charts
├── source/               # Source files
│   ├── html_tags.cpp     # Core implementation
│   └── bootstrap.cpp     # Bootstrap & chart implementation
├── tests/                # Unit tests
│   ├── CMakeLists.txt    # Test configuration
│   └── test_html_tags.cpp
├── build/                # Build output (generated)
├── CMakeLists.txt        # Main build configuration
└── CLAUDE.md             # This file
```

## Prerequisites

- Visual Studio 2022 (Community or higher)
- CMake 3.15+
- vcpkg with Catch2 installed at `C:/Users/ritte/vcpkg`

## Build Instructions

### Building with CLion (Recommended)

1. Open the project folder in CLion
2. CLion auto-detects CMakeLists.txt and configures
3. Select Debug/Release configuration
4. Build → Build Project (Ctrl+F9)

### Building with Visual Studio

#### Initial Configuration

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=C:/Users/ritte/vcpkg/scripts/buildsystems/vcpkg.cmake
```

#### Build Command

```bash
"C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe" ^
    "build\CPP_HTML_GEN.sln" ^
    -p:Configuration=Debug ^
    -v:minimal
```

#### Build Specific Target

```bash
MSBuild.exe build\CPP_HTML_GEN.sln -t:test_html_tags -p:Configuration=Debug
```

## Running Tests

```bash
# Run all tests
cd build
ctest --output-on-failure

# Run specific test executable
./tests/Debug/test_html_tags.exe

# Run with verbose output
./tests/Debug/test_html_tags.exe -s

# Run specific test by tag
./tests/Debug/test_html_tags.exe "[element]"
./tests/Debug/test_html_tags.exe "[page]"
```

## Usage Examples

### Basic Page

```cpp
#include "html_tags.h"
using namespace html;

page pg;
pg.head.add(title("My Page"));

pg << h1("Welcome")
   << p("This is a paragraph.")
   << div().cl("container")
        << ul()
            << li("Item 1")
            << li("Item 2");

std::cout << pg;
```

### Form Example

```cpp
form f;
f.action("/submit").method("POST");

f << label("Username:").for_id("username")
  << input().type("text").name("username").id("username").required()
  << br()
  << label("Password:").for_id("password")
  << input().type("password").name("password").id("password").required()
  << br()
  << button("Submit").type("submit");
```

### Semantic HTML5

```cpp
pg << header()
       << nav().cl("main-nav")
           << ul()
               << li(anchor("/", "Home"))
               << li(anchor("/about", "About"));

pg << main()
       << article()
           << h1("Article Title")
           << section()
               << h2("Section 1")
               << p("Content here...");

pg << footer()
       << p("Copyright 2024");
```

### HTML Escaping

```cpp
// Escape user input to prevent XSS
std::string user_input = "<script>alert('xss')</script>";
pg << p(html_escape(user_input));

// Use raw_html for trusted content
pg << raw_html("<div class='trusted'>Trusted HTML</div>");
```

### Charts (with C3.js)

```cpp
#include "bootstrap.h"

chart::line_chart chart;
chart.m_sID = "my_chart";
chart.m_sDataName = "Sales";
chart.m_sColor = "#3498db";

for (double val : {10.0, 25.0, 15.0, 30.0, 22.0}) {
    chart.add(val);
}

pg << chart.html();
```

## Available Elements

### Core HTML
- Text: `text`, `p`, `span`, `strong`, `em`, `b`, `small_`
- Headings: `h1`, `h2`, `h3`, `h4`, `h5`, `h6`
- Links: `anchor`, `link`, `head_link`
- Lists: `ul`, `ol`, `li`
- Structure: `div`, `br`, `hr`

### Tables
- `table`, `tr`, `td`, `th`, `thead`, `tbody`, `tfoot`, `caption`
- Helper: `row`, `hrow`, `cell`

### Forms
- `form`, `input`, `button`, `select`, `option`, `label`, `fieldset`, `legend`, `textarea`

### Semantic HTML5
- `header`, `footer`, `section`, `article`, `aside`, `main`, `nav`

### Media
- `video`, `audio`, `source`, `img`

### Page Structure
- `page`, `head`, `body`, `title`, `meta`, `script`, `style`

### Bootstrap Components
- `bootstrap::container`, `bootstrap::row`, `bootstrap::column`
- `bootstrap::navbar`, `bootstrap::navbar_dropdown`

### Charts
- `chart::line_chart`, `chart::bar_chart`, `chart::timeseries_line_chart`
- `image::rotator`

## Dependencies

- **Catch2**: Testing framework (via vcpkg)
- No other external dependencies - fully standalone!

## C++20 Features Used

- `std::string_view` for efficient string parameters
- `std::format` for string formatting
- `std::chrono` for date/time handling
- `[[nodiscard]]` attributes
- Modern initializer lists

## Guidelines

- Follow C++ best practices and modern C++20 standards
- Keep code readable and maintainable
- Use fluent interface patterns for element construction
- Always escape user-provided content with `html_escape()`

## API Reference

### Element Methods

All elements support these chainable methods:
- `.id(string)` - Set element ID
- `.cl(string)` - Set CSS class
- `.add_cl(string)` - Add CSS class
- `.style(string)` - Set inline style
- `.type(string)` - Set type attribute
- `.role(string)` - Set ARIA role
- `.src(string)` - Set source URL
- `.href(string)` - Set hyperlink reference
- `.alt(string)` - Set alt text
- `.width(string)` / `.height(string)` - Set dimensions
- `.add_attr(name, value)` - Add custom attribute

### Content Methods
- `.add(element)` - Add child element
- `.add(string)` - Add text content
- `<< element` - Stream operator for adding children
- `.content(string)` - Replace content
- `.clear()` - Clear children
- `.clear_all()` - Clear children and attributes

### Finding Elements
- `.get(id)` - Get element by ID (throws if not found)
- `.find(id)` - Find element by ID (returns nullptr if not found)
- `.exists(id)` - Check if element exists
- `[index]` - Access child by index
- `[id]` - Access element by ID

## Notes

- The library uses `html` namespace
- Elements support chaining via `<<` operator
- Use `.id()`, `.cl()`, `.style()` etc. for attributes
- `element_group` allows combining multiple elements with `+` operator
- Form elements have convenience methods like `.required()`, `.disabled()`, `.checked()`
- Media elements have `.controls()`, `.autoplay()`, `.loop()`, `.muted()`
