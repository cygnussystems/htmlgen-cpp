# Variadic Constructor API Design

## Overview

Add variadic template constructors to all HTML element classes to enable concise, Pythonic element construction with natural nesting.

## Current Pain Points

### 1. Verbose Multi-Child Construction
```cpp
// Current - every child needs separate statement
web::html::div container;
container << h1("Title");
container << p("Paragraph 1");
container << p("Paragraph 2");
```

### 2. Awkward Nesting Syntax
```cpp
// Current - parentheses required for inline nesting
t1.thead << (tr() << th("Name") << th("Age") << th("City"));
```

### 3. Temporary Variables Required
```cpp
// Current - complex structures need intermediates
web::html::div fg1;
fg1.cl("form-group");
fg1 << label("Email:").for_id("email");
input email_input;
email_input.name("email").placeholder("Enter email").required();
email_input.type("email").id("email").cl("form-control");
fg1 << email_input;
login_form << fg1;
```

## Proposed Solution

### New Syntax
```cpp
// Proposed - natural nesting, minimal code
auto container = div(
    h1("Title"),
    p("Paragraph 1"),
    p("Paragraph 2"),
    ul(li("Item 1"), li("Item 2"), li("Item 3"))
).cl("container");
```

### Table Example
```cpp
// Current
table t1;
t1.cl("table table-bordered");
t1.thead << (tr() << th("Name") << th("Age") << th("City"));
t1 << (tr() << td("Alice") << td("28") << td("New York"));
t1 << (tr() << td("Bob") << td("35") << td("Los Angeles"));

// Proposed
auto t1 = table(
    tr(th("Name"), th("Age"), th("City")),
    tr(td("Alice"), td("28"), td("New York")),
    tr(td("Bob"), td("35"), td("Los Angeles"))
).cl("table table-bordered");
```

### Form Example
```cpp
// Current
web::html::div fg1;
fg1.cl("form-group");
fg1 << label("Email:").for_id("email");
fg1 << input().type("email").name("email").cl("form-control");
login_form << fg1;

// Proposed
login_form << div(
    label("Email:").for_id("email"),
    input().type("email").name("email").cl("form-control")
).cl("form-group");
```

### Mixed Content (Strings + Elements)
```cpp
// Strings automatically converted to text nodes
p("Text with ", strong("bold"), " and ", em("italic"), " words.")
// Output: <p>Text with <strong>bold</strong> and <em>italic</em> words.</p>
```

## Implementation Approach

### Core Infrastructure

Add to base `element` class:

```cpp
// Helper to add multiple children using fold expression
template<typename... Args>
void add_children(Args&&... args) {
    (add_child_item(std::forward<Args>(args)), ...);
}

// Type-aware child addition (element vs string)
template<typename T>
void add_child_item(T&& item) {
    if constexpr (std::is_convertible_v<std::decay_t<T>, std::string_view>) {
        add(text(std::string(std::forward<T>(item))));
    } else {
        add(std::forward<T>(item));
    }
}
```

### Element Class Template

Each element gets a variadic constructor:

```cpp
class div : public element {
public:
    // Existing constructors (backward compatibility)
    div() {
        element::m_type = div_t;
        m_newline_after_tag = true;
        m_newline_after_element = true;
    }

    // New variadic constructor
    template<typename... Args>
    explicit div(Args&&... args) {
        element::m_type = div_t;
        m_newline_after_tag = true;
        m_newline_after_element = true;
        add_children(std::forward<Args>(args)...);
    }

    // ... rest of class
};
```

### C++20 Concepts (Optional Enhancement)

For better error messages:

```cpp
template<typename T>
concept HtmlContent = std::derived_from<std::remove_cvref_t<T>, element>
                   || std::convertible_to<T, std::string_view>;

template<typename... Args>
requires (HtmlContent<Args> && ...)
div(Args&&... args);
```

## Elements to Update

### Basic Elements (html_basic.h)
- `div`, `nav`, `span`
- `h1`, `h2`, `h3`, `h4`, `h5`, `h6`
- `p`, `em`, `strong`, `b`, `small_`
- `ul`, `ol`, `li`

### Table Elements (html_table.h)
- `table`, `tr`, `td`, `th`
- `thead`, `tbody`, `tfoot`
- `caption`

### Form Elements (html_form.h)
- `form`, `fieldset`, `legend`
- `select`, `optgroup`
- `label`

### Semantic Elements (html_semantic.h)
- `header`, `footer`, `section`, `article`
- `aside`, `main`, `nav`
- `figure`, `figcaption`

### Interactive Elements (html_interactive.h)
- `details`, `summary`
- `dialog`

### Media Elements (html_media.h)
- `video`, `audio`, `picture`

## Backward Compatibility

- All existing constructors remain unchanged
- `<<` operator continues to work
- `add()` method continues to work
- Existing code compiles and runs identically

## Benefits

1. **50-70% code reduction** for typical HTML structures
2. **Natural nesting** mirrors HTML structure visually
3. **Type-safe** with full compile-time checking
4. **Move-efficient** - perfect forwarding, no unnecessary copies
5. **Mixed content** - strings auto-convert to text nodes
6. **Familiar** to users of React JSX, Kotlin HTML DSL, etc.

## Considerations

1. **Compile time** - heavy template use may increase build times
2. **Error messages** - template errors can be cryptic (mitigated by concepts)
3. **Empty constructor** - `div()` vs `div{}` disambiguation

## Testing Strategy

1. Update existing tests to use new syntax where appropriate
2. Add specific tests for variadic constructors
3. Test mixed content (strings + elements)
4. Test deep nesting
5. Verify backward compatibility with old syntax

## Future Enhancements

### Attribute Helpers (Optional)
```cpp
namespace attrs {
    struct id { std::string value; };
    struct cl { std::string value; };
}

// Enable: div(attrs::id{"main"}, attrs::cl{"container"}, p("text"))
```

### Table Helpers
```cpp
// Helper for common table patterns
auto t = table_from_data(
    {"Name", "Age", "City"},  // headers
    {
        {"Alice", "28", "New York"},
        {"Bob", "35", "Los Angeles"}
    }
);
```
