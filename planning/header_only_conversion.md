# Header-Only Library Conversion Plan

## Overview

This document outlines the plan for converting CPP_HTML_GEN from a compiled static library to a header-only library. The conversion will simplify distribution, improve optimization opportunities, and align with modern C++ library practices.

## Current State Analysis

### Already Header-Only (~70%)
All element subclasses are defined inline in headers with full implementations:
- `html_basic.h` - div, nav, p, ul, ol, li, headings, etc.
- `html_table.h` - table, tr, td, th, thead, tbody, tfoot
- `html_form.h` - form, input, button, select, label, etc.
- `html_semantic.h` - header, footer, section, article, aside, main, figure
- `html_media.h` - video, audio, source, img
- `html_interactive.h` - details, dialog, template_
- `html_misc.h` - meta, script, style, raw_html

### Requires Conversion (~25%)

**html_tags.cpp (797 lines)**
- `html_escape()` function
- `init_static_tag_names()` initialization function
- `element` class core methods: constructors, copy, find, add, html generation
- `element_group` methods
- `page` class methods

**bootstrap.cpp (264 lines)**
- `image::rotator` class implementation
- `chart::line_chart` class implementation
- `chart::timeseries_line_chart` class implementation
- `chart::bar_chart` class implementation

### Requires Special Handling (~5%)

**Static Member Variable**
```cpp
// html_tags.cpp:137
std::vector<std::string> element::s_static_tag_names = init_static_tag_names();
```
This static member must be refactored to avoid ODR violations.

**Resource Data (html_resources.cpp, ~2MB)**
- `bootstrap_css_array` - Embedded Bootstrap CSS as character array
- `bootstrap_css_string()` accessor function

## Required Changes

### 1. Static Tag Names Refactoring

**Problem**: Static member initialization in .cpp causes ODR violations when moved to header.

**Solution**: Use C++17 `inline static` with lazy initialization:

```cpp
// In html_core.h, inside element class
private:
    static std::vector<std::string>& get_static_tag_names() {
        static std::vector<std::string> names = {
            "", "html", "head", "body", "title", "meta", "link",
            // ... all 120 tag names ...
        };
        return names;
    }

public:
    // Replace s_static_tag_names usage with get_static_tag_names()
```

This uses Meyer's Singleton pattern - thread-safe initialization on first use.

### 2. Move html_tags.cpp to html_core.h

Move all function implementations inline:

```cpp
// html_core.h

// Free function - mark inline
inline std::string html_escape(std::string_view input) {
    std::string result;
    result.reserve(input.size());
    for (char c : input) {
        switch (c) {
            case '&': result += "&amp;"; break;
            case '<': result += "&lt;"; break;
            case '>': result += "&gt;"; break;
            case '"': result += "&quot;"; break;
            case '\'': result += "&#39;"; break;
            default: result += c;
        }
    }
    return result;
}

// Class methods - define inline in class or mark inline outside
class element {
public:
    element() {
        m_type = element_t;
        // ... initialization ...
    }

    // Move constructor
    element(element&& other) noexcept {
        // ... implementation ...
    }

    // All other methods inline
};
```

### 3. Move bootstrap.cpp to bootstrap.h

All chart and rotator classes become fully inline:

```cpp
// bootstrap.h

namespace image {
    class rotator : public element {
    public:
        inline rotator() {
            // ... full implementation ...
        }

        inline std::string html() {
            // ... full implementation ...
        }
    };
}

namespace chart {
    class line_chart {
    public:
        inline line_chart() { /* ... */ }
        inline void add(double value) { /* ... */ }
        inline std::string html() { /* ... */ }
    };
    // ... other chart classes ...
}
```

### 4. Resource Data Strategy

**Option A: Inline Constexpr (Recommended for full header-only)**
```cpp
// html_resources.h
inline constexpr char bootstrap_css_data[] = R"(
/* Bootstrap CSS content here */
)";

inline std::string bootstrap_css_string() {
    return std::string(bootstrap_css_data, sizeof(bootstrap_css_data) - 1);
}
```

**Option B: Keep as Optional Compiled Component**
- Keep `html_resources.cpp` as a separate compiled file
- Users who don't need Bootstrap can skip it
- Reduces header size by 2MB

**Option C: External File Loading**
```cpp
// Load from file at runtime instead of embedding
inline std::string bootstrap_css_string() {
    // Load from external file
}
```

**Recommendation**: Option A for simplicity, but document Option B for users concerned about compile times.

## Implementation Steps

### Phase 1: Prepare Headers

1. Create backup branch
2. Add `inline` keyword to all free functions in headers
3. Ensure all class methods are defined in class body or marked `inline`

### Phase 2: Refactor Static Initialization

1. Replace `s_static_tag_names` with `get_static_tag_names()` function
2. Update all usages throughout codebase
3. Remove old static member declaration
4. Test ODR compliance

### Phase 3: Move Core Implementation

1. Move `html_escape()` to `html_core.h`
2. Move `element` class methods to `html_core.h`
3. Move `element_group` methods to `html_core.h`
4. Move `page` class methods to `html_core.h`
5. Delete `html_tags.cpp`

### Phase 4: Move Bootstrap Implementation

1. Move `rotator` implementation to `bootstrap.h`
2. Move chart class implementations to `bootstrap.h`
3. Delete `bootstrap.cpp`

### Phase 5: Handle Resources

1. Convert `bootstrap_css_array` to inline constexpr string
2. Move accessor function to header
3. Delete `html_resources.cpp`

### Phase 6: Update Build System

1. Update `CMakeLists.txt` to remove source files
2. Change from STATIC library to INTERFACE library
3. Update test configuration
4. Update installation rules

### Phase 7: Testing and Validation

1. Build with multiple compilers (MSVC, GCC, Clang)
2. Test ODR compliance with multiple translation units
3. Run all existing tests
4. Verify no duplicate symbol errors

## Build System Updates

### Before (Static Library)
```cmake
add_library(CPP_HTML_GEN STATIC
    source/html_tags.cpp
    source/bootstrap.cpp
    source/html_resources.cpp
)
target_include_directories(CPP_HTML_GEN PUBLIC include/)
```

### After (Header-Only)
```cmake
add_library(CPP_HTML_GEN INTERFACE)
target_include_directories(CPP_HTML_GEN INTERFACE include/)
target_compile_features(CPP_HTML_GEN INTERFACE cxx_std_20)
```

### Test Configuration Update
```cmake
add_executable(test_html_tags
    tests/test_10_basic_elements.cpp
    tests/test_20_table_elements.cpp
    # ... other test files ...
)
target_link_libraries(test_html_tags PRIVATE CPP_HTML_GEN Catch2::Catch2WithMain)
```

## Trade-offs

### Compile Time Impact
- **Estimated increase**: 10-15% longer compilation
- **Cause**: Compiler processes more code per translation unit
- **Mitigation**: Most real projects compile incrementally

### Binary Size Impact
- **Object files**: +5-10MB intermediate files (stripped in final binary)
- **Final executable**: Minimal difference due to linker optimization

### Header Size Impact
- **Current headers**: ~2,500 lines total
- **After conversion**: ~3,500 lines total (+40%)
- **With resources**: +2MB for Bootstrap CSS

### Benefits
- Single include distribution
- Better inlining and optimization
- No library linking complexity
- Easier integration with build systems
- Better template/constexpr support

## Testing Plan

### Unit Tests
- Run all existing Catch2 tests
- Verify 256+ assertions pass

### ODR Compliance Tests
1. Create test with multiple .cpp files including same headers
2. Verify no duplicate symbol errors
3. Test with different optimization levels

### Cross-Platform Tests
- Windows (MSVC)
- Linux (GCC, Clang)
- macOS (Apple Clang)

### Integration Test
```cpp
// test_integration_a.cpp
#include "html_tags.h"
void test_a() { html::div d; }

// test_integration_b.cpp
#include "html_tags.h"
void test_b() { html::div d; }

// main.cpp
void test_a();
void test_b();
int main() { test_a(); test_b(); }
```
This must link without duplicate symbol errors.

## Rollback Plan

If issues arise:
1. Keep `source/` directory intact during development
2. Use feature branch for conversion
3. Test thoroughly before merging
4. Can revert to static library if needed

## Timeline Estimate

- Phase 1-2: 1 hour (preparation and static refactoring)
- Phase 3-4: 2 hours (moving implementations)
- Phase 5: 30 minutes (resources)
- Phase 6: 30 minutes (build system)
- Phase 7: 1-2 hours (testing)

**Total: 5-6 hours**

## References

- [C++17 inline variables](https://en.cppreference.com/w/cpp/language/inline)
- [Header-only library best practices](https://www.fluentcpp.com/2017/08/25/3-types-of-macros-that-improve-c-code/)
- [ODR (One Definition Rule)](https://en.cppreference.com/w/cpp/language/definition)
