# Bootstrap Modernization Plan

## 1. Current State Analysis

### Existing Components
- **Layout**: `container`, `row`, `column` - Basic Bootstrap 3 grid
- **Navigation**: `navbar`, `navbar_dropdown` - Bootstrap 3 navbar
- **Charts**: `line_chart`, `bar_chart`, `timeseries_line_chart` - C3.js based (not Bootstrap)
- **Legacy**: `rotator` - 1990s-style image gallery

### Issues
1. **Bootstrap 3 only** - Uses outdated classes (`col-md-*`, `navbar-default`)
2. **Charts misplaced** - C3.js charts in bootstrap namespace but aren't Bootstrap
3. **Missing components** - No buttons, cards, modals, forms, alerts, badges, etc.
4. **Inconsistent patterns** - Public member variables in charts, fragile string templates
5. **No dependency management** - Manual inclusion of CSS/JS in every page

---

## 2. Proposed Architecture

### Thread-Local Page Context System

Components automatically register their dependencies without any syntax overhead:

```cpp
// Internal: thread-local pointer to current page being built
namespace html::detail {
    thread_local page* current_page = nullptr;
}

class page {
    std::set<dependency> m_dependencies;
    std::vector<std::string> m_head_scripts;
    std::vector<std::string> m_body_scripts;
    std::vector<std::string> m_init_scripts;

public:
    page() {
        detail::current_page = this;
    }

    ~page() {
        detail::current_page = nullptr;
    }

    void require(dependency dep);
    void add_head_script(const std::string& js);
    void add_body_script(const std::string& js);
    void add_on_ready(const std::string& js);
};

// Usage - completely clean syntax
page pg;
pg << modal("confirm", "Are you sure?");  // Auto-registers Bootstrap JS
pg << tooltip("Hover me", "Tooltip text"); // Auto-registers tooltip init
std::cout << pg.html();  // All dependencies resolved
```

### Namespace Organization

```
html::              - Core HTML elements (current)
bootstrap::         - Bootstrap 5 components
  bootstrap::layout::     - container, row, column
  bootstrap::nav::        - navbar, tabs, pills, breadcrumbs
  bootstrap::forms::      - form_group, form_control
  bootstrap::components:: - cards, modals, alerts, badges, buttons
chart::             - Visualization library (separate from Bootstrap)
```

---

## 3. Dependency Management

### Dependency Enum

```cpp
enum class dependency {
    // CSS
    bootstrap_css,
    bootstrap_icons,

    // JavaScript
    bootstrap_js,
    c3_js,
    d3_js,

    // Combined
    bootstrap_bundle  // CSS + JS
};
```

### Placement Strategy

| Type | Location | Example |
|------|----------|---------|
| CSS links | `<head>` | `<link href="bootstrap.min.css">` |
| External JS | End of `<body>` | `<script src="bootstrap.bundle.min.js">` |
| Init scripts | DOMContentLoaded | Tooltip/modal initialization |

### Rendered Output

```html
<!DOCTYPE html>
<html>
<head>
    <!-- Dependencies: CSS -->
    <link href="bootstrap.min.css" rel="stylesheet">
    <script>/* head scripts if any */</script>
</head>
<body>
    <!-- User content -->

    <!-- Dependencies: JS -->
    <script src="bootstrap.bundle.min.js"></script>

    <!-- Combined init scripts -->
    <script>
    document.addEventListener('DOMContentLoaded', function() {
        // All component init scripts combined and deduplicated
        document.querySelectorAll('[data-bs-toggle="tooltip"]')
            .forEach(el => new bootstrap.Tooltip(el));
    });
    </script>
</body>
</html>
```

---

## 4. Component Implementation Tiers

### Tier 1: Essential (~8-10 classes)
Covers 80% of typical use cases.

| Component | Description | Complexity |
|-----------|-------------|------------|
| `button` | Button with variants (primary, danger, etc.) | Simple |
| `alert` | Dismissible alerts with variants | Simple |
| `card` | Card with header/body/footer | Simple |
| `badge` | Inline badge/label | Simple |
| `table` | Bootstrap table with striped/bordered/hover | Simple |
| `form_group` | Form group with label + input | Simple |
| `form_control` | Input wrapper with validation states | Simple |
| `modal` | Modal dialog | Needs JS |
| Grid improvements | Add `col_sm`, `col_lg`, `col_xl` | Simple |

**Estimated effort**: 400-600 lines of code

### Tier 2: Common (~10-15 classes)
Additional commonly used components.

- `tabs` / `pills` - Navigation tabs
- `pagination` - Page navigation
- `breadcrumb` - Breadcrumb navigation
- `list_group` - List group items
- `progress_bar` - Progress indicator
- `spinner` - Loading spinner
- `accordion` / `collapse` - Collapsible content
- `dropdown` - Standalone dropdown (not just navbar)
- `input_group` - Input with addons
- `toast` - Toast notifications

### Tier 3: Specialized
Less common or complex components.

- `carousel` - Image/content carousel
- `offcanvas` - Sliding panel
- `popover` / `tooltip` - Hover tooltips
- `navbar` improvements - Sticky, dark mode
- Form inputs - Switches, ranges, floating labels

---

## 5. Phased Implementation

### Phase 1: Simple Components (No JS)
Add Tier 1 components that don't require JavaScript:
- button, alert, card, badge, table
- Grid improvements (responsive columns)
- Basic form helpers

**No architectural changes needed** - just new classes extending element.

### Phase 2: Page Context System
Implement the thread-local page context:
- Modify `page` class with dependency tracking
- Add `require()`, `add_on_ready()` methods
- Update `html()` to render dependencies
- Add `dependency` enum

### Phase 3: Interactive Components
Add components requiring JavaScript:
- modal, dropdown, collapse, tooltip
- Components use new context system
- Automatic dependency registration

---

## 6. Component Design Pattern

### Thin Wrappers Over CSS Classes

Bootstrap components are just HTML with specific classes. Our wrappers should be thin:

```cpp
class alert : public html::div {
public:
    alert(const std::string& message) {
        cl("alert");
        add(message);
    }

    // Variant methods - fluent API
    alert& primary()   { add_cl("alert-primary"); return *this; }
    alert& secondary() { add_cl("alert-secondary"); return *this; }
    alert& success()   { add_cl("alert-success"); return *this; }
    alert& danger()    { add_cl("alert-danger"); return *this; }
    alert& warning()   { add_cl("alert-warning"); return *this; }
    alert& info()      { add_cl("alert-info"); return *this; }

    alert& dismissible() {
        add_cl("alert-dismissible fade show");
        add_attr("role", "alert");
        // Add close button
        *this << html::button()
            .cl("btn-close")
            .add_attr("data-bs-dismiss", "alert")
            .add_attr("aria-label", "Close");
        return *this;
    }
};

// Usage
pg << alert("Operation successful!").success().dismissible();
```

### Button Example

```cpp
class button : public html::button {
public:
    button(const std::string& text) {
        cl("btn");
        add(text);
    }

    // Variants
    button& primary()   { add_cl("btn-primary"); return *this; }
    button& secondary() { add_cl("btn-secondary"); return *this; }
    button& success()   { add_cl("btn-success"); return *this; }
    button& danger()    { add_cl("btn-danger"); return *this; }
    button& outline()   { /* modify existing variant class */ return *this; }

    // Sizes
    button& lg() { add_cl("btn-lg"); return *this; }
    button& sm() { add_cl("btn-sm"); return *this; }

    // States
    button& disabled() { add_attr("disabled", ""); return *this; }
};

// Usage
pg << button("Submit").primary().lg();
pg << button("Cancel").secondary();
```

### Card Example

```cpp
class card : public html::div {
    html::div m_header;
    html::div m_body;
    html::div m_footer;
    bool m_has_header = false;
    bool m_has_footer = false;

public:
    card() {
        cl("card");
        m_header.cl("card-header");
        m_body.cl("card-body");
        m_footer.cl("card-footer");
    }

    card& header(const std::string& text) {
        m_header.add(text);
        m_has_header = true;
        return *this;
    }

    card& body(element&& content) {
        m_body << std::move(content);
        return *this;
    }

    card& footer(const std::string& text) {
        m_footer.add(text);
        m_has_footer = true;
        return *this;
    }

    // Override html() to assemble parts
    std::string html() override {
        if (m_has_header) *this << m_header;
        *this << m_body;
        if (m_has_footer) *this << m_footer;
        return element::html();
    }
};

// Usage
pg << card()
    .header("Card Title")
    .body(p("Card content here"))
    .footer("Last updated: today");
```

### Modal Example (With Dependencies)

```cpp
class modal : public html::div {
public:
    modal(const std::string& id, const std::string& title) {
        cl("modal fade");
        this->id(id);
        add_attr("tabindex", "-1");
        add_attr("aria-labelledby", id + "Label");
        add_attr("aria-hidden", "true");

        // Register dependency with page context
        if (detail::current_page) {
            detail::current_page->require(dependency::bootstrap_js);
        }

        // Build modal structure
        auto dialog = html::div().cl("modal-dialog");
        auto content = html::div().cl("modal-content");

        // Header
        auto header = html::div().cl("modal-header");
        header << h5(title).cl("modal-title").id(id + "Label");
        header << html::button()
            .cl("btn-close")
            .add_attr("data-bs-dismiss", "modal")
            .add_attr("aria-label", "Close");
        content << header;

        // Body placeholder
        content << html::div().cl("modal-body").id(id + "-body");

        // Footer placeholder
        content << html::div().cl("modal-footer").id(id + "-footer");

        dialog << content;
        *this << dialog;
    }

    // Methods to populate body/footer...
};

// Usage
pg << modal("confirmDialog", "Confirm Action");
// Bootstrap JS automatically included in page output
```

### Tooltip Example (With Init Script)

```cpp
class tooltip_wrapper : public html::span {
public:
    tooltip_wrapper(const std::string& text, const std::string& tip) {
        add(text);
        add_attr("data-bs-toggle", "tooltip");
        add_attr("data-bs-placement", "top");
        add_attr("title", tip);

        if (detail::current_page) {
            detail::current_page->require(dependency::bootstrap_js);
            // This will be deduplicated if multiple tooltips
            detail::current_page->add_on_ready(
                "document.querySelectorAll('[data-bs-toggle=\"tooltip\"]')"
                ".forEach(el => new bootstrap.Tooltip(el));"
            );
        }
    }
};
```

---

## 7. Migration Strategy

### Backwards Compatibility
- Keep existing Bootstrap 3 classes working
- Add Bootstrap 5 as new/parallel components
- Deprecate old components over time

### Bootstrap Version Support
- **Target Bootstrap 5** for new development
- Use CSS custom properties where applicable
- Document any Bootstrap 3 → 5 migration steps

---

## 8. Inline Images (Related Enhancement)

For icons and simple graphics, use data URIs to avoid external dependencies:

```cpp
namespace icons {
    const char* arrow_right = "data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' "
        "viewBox='0 0 24 24' fill='none' stroke='currentColor' stroke-width='2'%3E"
        "%3Cpath d='M5 12h14M12 5l7 7-7 7'/%3E%3C/svg%3E";

    const char* chevron_down = "data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' "
        "viewBox='0 0 24 24' fill='currentColor'%3E"
        "%3Cpath d='M19 9l-7 7-7-7'/%3E%3C/svg%3E";

    const char* check = "data:image/svg+xml,...";
    const char* x_mark = "data:image/svg+xml,...";
}

// Usage
pg << img(icons::arrow_right, "20");
```

---

## 9. Summary

### Benefits of This Architecture
1. **Clean syntax** - No explicit dependency management in user code
2. **Self-contained components** - Each knows what it needs
3. **Automatic deduplication** - Libraries included once
4. **Proper ordering** - CSS in head, JS at end of body
5. **Fluent API** - Consistent with existing library style
6. **Incremental adoption** - Can add components as needed

### Next Steps
1. Decide on Bootstrap version (5 recommended)
2. Start with Phase 1 simple components
3. Test with real use cases
4. Implement page context system
5. Add interactive components
