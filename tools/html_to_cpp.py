#!/usr/bin/env python3
"""
HTML to CPP_HTML_GEN C++ Code Converter

Parses HTML and generates corresponding C++ code using the CPP_HTML_GEN library.
This ensures exact 1:1 reproduction of HTML structure.

Usage:
    python html_to_cpp.py input.html [--output output.cpp] [--function-name generate_page]
"""

import argparse
import re
from html.parser import HTMLParser
from typing import List, Tuple, Optional


class HTMLToCppConverter(HTMLParser):
    """Converts HTML to CPP_HTML_GEN C++ code."""

    # Elements that don't have closing tags
    VOID_ELEMENTS = {
        'br', 'hr', 'img', 'input', 'meta', 'link', 'col', 'area',
        'base', 'embed', 'param', 'source', 'track', 'wbr'
    }

    # Map HTML tags to C++ class names (when they differ)
    TAG_MAP = {
        'a': 'anchor',
        'main': 'html::main',  # Avoid conflict with main()
        'div': 'html::div',    # Avoid conflict with stdlib div()
        'small': 'small_',     # Avoid keyword conflict
        'template': 'template_',
        'time': 'time_',       # Avoid conflict with time()
        'link': 'head_link',   # Use head_link for link elements
        's': 'html::s',        # Single letter elements need namespace
        'b': 'html::b',
        'i': 'html::i',
        'u': 'html::u',
        'q': 'html::q',
    }

    # Attributes that map to specific methods
    ATTR_METHODS = {
        'id': 'id',
        'class': 'cl',
        'style': 'style',
        'href': 'href',
        'src': 'src',
        'alt': 'alt',
        'type': 'type',
        'name': 'name',
        'value': 'value',
        'placeholder': 'placeholder',
        'for': 'for_id',
        'action': 'action',
        'method': 'method',
        'colspan': 'colspan',
        'rowspan': 'rowspan',
        'role': 'role',
        'disabled': 'disabled',
        'required': 'required',
        'checked': 'checked',
        'selected': 'selected',
        'multiple': 'multiple',
        'readonly': 'readonly',
        'open': 'open',
        'datetime': 'datetime',
        'cite': 'cite',
        'title': 'title',
        'width': 'width',
        'height': 'height',
        'min': 'min',
        'max': 'max',
        'step': 'step',
        'pattern': 'pattern',
        'maxlength': 'maxlength',
        'minlength': 'minlength',
        'rows': 'rows',
        'cols': 'cols',
        'wrap': 'wrap',
        'autoplay': 'autoplay',
        'controls': 'controls',
        'loop': 'loop',
        'muted': 'muted',
        'preload': 'preload',
        'poster': 'poster',
        'scope': 'scope',
        'span': 'span',
        'label': 'label',
        'abbr': 'abbr',
    }

    # Boolean attributes (no value needed)
    BOOLEAN_ATTRS = {
        'disabled', 'required', 'checked', 'selected', 'multiple',
        'readonly', 'open', 'autoplay', 'controls', 'loop', 'muted'
    }

    def __init__(self):
        super().__init__()
        self.output_lines: List[str] = []
        self.element_stack: List[Tuple[str, str, int]] = []  # (tag, var_name, depth)
        self.var_counter = 0
        self.indent_level = 0
        self.current_text = ""
        self.in_script = False
        self.in_style = False
        self.script_content = ""
        self.style_content = ""

    def get_var_name(self, tag: str) -> str:
        """Generate a unique variable name for an element."""
        self.var_counter += 1
        base = self.TAG_MAP.get(tag, tag).replace('html::', '').replace('_', '')
        return f"{base}_{self.var_counter}"

    def indent(self) -> str:
        """Return current indentation string."""
        return "    " * self.indent_level

    def escape_cpp_string(self, s: str) -> str:
        """Escape a string for use in C++ code."""
        return s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n').replace('\r', '\\r').replace('\t', '\\t')

    def handle_starttag(self, tag: str, attrs: List[Tuple[str, Optional[str]]]):
        # Flush any pending text
        self.flush_text()

        # Handle special tags
        if tag == 'script':
            # Check if it has a src attribute (external script)
            src_attr = None
            for name, value in attrs:
                if name == 'src':
                    src_attr = value
                    break

            if src_attr:
                # External script - output immediately
                escaped_src = self.escape_cpp_string(src_attr)
                if self.element_stack:
                    parent_var = self.element_stack[-1][1]
                    self.output_lines.append(f'{self.indent()}{parent_var} << script().src("{escaped_src}");')
                return
            else:
                # Inline script - capture content
                self.in_script = True
                self.script_content = ""
                return
        elif tag == 'style':
            self.in_style = True
            self.style_content = ""
            return
        elif tag == '!doctype':
            return  # Skip doctype
        elif tag == 'html':
            # Skip html tag - page handles this
            self.element_stack.append((tag, 'pg', 0))  # Use pg as the root
            return
        elif tag == 'head':
            # Use pg.head instead of creating a new element
            self.element_stack.append((tag, 'pg.head', 0))
            return
        elif tag == 'body':
            # Use pg (body) instead of creating a new element
            self.element_stack.append((tag, 'pg', 0))
            return

        # Get C++ class name
        cpp_class = self.TAG_MAP.get(tag, tag)
        var_name = self.get_var_name(tag)

        # Special handling for head_link which uses attr() constructors
        if tag == 'link':
            attr_args = []
            for name, value in attrs:
                if value is not None:
                    escaped_name = self.escape_cpp_string(name)
                    escaped_value = self.escape_cpp_string(value)
                    attr_args.append(f'attr("{escaped_name}", "{escaped_value}")')
            if attr_args:
                self.output_lines.append(f"{self.indent()}{cpp_class} {var_name}({', '.join(attr_args)});")
            else:
                self.output_lines.append(f"{self.indent()}{cpp_class} {var_name};")
        else:
            # Generate element creation
            self.output_lines.append(f"{self.indent()}{cpp_class} {var_name};")

            # Process attributes
            attr_calls = []
            add_attr_calls = []

            for name, value in attrs:
                if name in self.ATTR_METHODS:
                    method = self.ATTR_METHODS[name]
                    if name in self.BOOLEAN_ATTRS and (value is None or value == name or value == ""):
                        attr_calls.append(f"{method}()")
                    elif value is not None:
                        escaped = self.escape_cpp_string(value)
                        if name == 'colspan' or name == 'rowspan':
                            # These take integers
                            try:
                                attr_calls.append(f"{method}({int(value)})")
                            except ValueError:
                                attr_calls.append(f'{method}("{escaped}")')
                        else:
                            attr_calls.append(f'{method}("{escaped}")')
                else:
                    # Use add_attr for non-standard attributes
                    if value is not None:
                        escaped_name = self.escape_cpp_string(name)
                        escaped_value = self.escape_cpp_string(value)
                        add_attr_calls.append(f'add_attr("{escaped_name}", "{escaped_value}")')
                    else:
                        escaped_name = self.escape_cpp_string(name)
                        add_attr_calls.append(f'add_attr("{escaped_name}", "{escaped_name}")')

            # Output attribute method calls
            if attr_calls:
                self.output_lines.append(f"{self.indent()}{var_name}.{'.'.join(attr_calls)};")

            for call in add_attr_calls:
                self.output_lines.append(f"{self.indent()}{var_name}.{call};")

        # Push to stack if not a void element
        if tag not in self.VOID_ELEMENTS:
            self.element_stack.append((tag, var_name, self.indent_level))
        else:
            # For void elements, add to parent immediately
            if self.element_stack:
                parent_var = self.element_stack[-1][1]
                self.output_lines.append(f"{self.indent()}{parent_var} << {var_name};")

    def handle_endtag(self, tag: str):
        # Handle special tags
        if tag == 'script':
            self.in_script = False
            if self.script_content.strip():
                # Add script to parent
                if self.element_stack:
                    parent_var = self.element_stack[-1][1]
                    # Use raw string for script content
                    self.output_lines.append(f'{self.indent()}{parent_var} << script(R"({self.script_content})");')
            return
        elif tag == 'style':
            self.in_style = False
            if self.style_content.strip():
                # Add style to parent
                if self.element_stack:
                    parent_var = self.element_stack[-1][1]
                    # Use raw string for style content
                    self.output_lines.append(f'{self.indent()}{parent_var} << style(R"({self.style_content})");')
            return
        elif tag in ('html', 'head', 'body'):
            # Just pop these special elements without adding to parent
            if self.element_stack and self.element_stack[-1][0] == tag:
                self.element_stack.pop()
            return

        # Flush any pending text
        self.flush_text()

        if tag in self.VOID_ELEMENTS:
            return

        # Pop from stack
        if self.element_stack and self.element_stack[-1][0] == tag:
            _, var_name, _ = self.element_stack.pop()

            # Add this element to its parent
            if self.element_stack:
                parent_var = self.element_stack[-1][1]
                self.output_lines.append(f"{self.indent()}{parent_var} << {var_name};")

    def handle_data(self, data: str):
        if self.in_script:
            self.script_content += data
            return
        elif self.in_style:
            self.style_content += data
            return

        # Accumulate text
        self.current_text += data

    def flush_text(self):
        """Flush accumulated text content."""
        if self.current_text:
            text = self.current_text
            self.current_text = ""

            # Skip pure whitespace
            if not text.strip():
                return

            # Normalize whitespace but preserve some structure
            text = ' '.join(text.split())

            if text and self.element_stack:
                parent_var = self.element_stack[-1][1]
                escaped = self.escape_cpp_string(text)
                self.output_lines.append(f'{self.indent()}{parent_var} << text("{escaped}");')

    def handle_comment(self, data: str):
        # Convert HTML comments to C++ comments
        # Handle multiline comments
        lines = data.strip().split('\n')
        if len(lines) == 1:
            self.output_lines.append(f"{self.indent()}// {lines[0]}")
        else:
            self.output_lines.append(f"{self.indent()}/*")
            for line in lines:
                self.output_lines.append(f"{self.indent()} * {line}")
            self.output_lines.append(f"{self.indent()} */")

    def get_output(self) -> str:
        """Get the generated C++ code."""
        return '\n'.join(self.output_lines)


def convert_html_to_cpp(html_content: str, function_name: str = "generate_page") -> str:
    """Convert HTML content to CPP_HTML_GEN C++ code."""

    converter = HTMLToCppConverter()
    converter.feed(html_content)

    # Generate the complete function
    lines = [
        '/*  ===================================================================',
        '*   Auto-generated from HTML using html_to_cpp.py',
        '*   This file was automatically converted - do not edit manually',
        '*  ====================================================================',
        '*/',
        '',
        '#include <catch2/catch_all.hpp>',
        '#include <fstream>',
        '#include <filesystem>',
        '#include "../include/html_tags.h"',
        '',
        'using namespace html;',
        '',
        'namespace {',
        '',
        '// Helper to get output directory',
        'std::filesystem::path get_output_dir() {',
        '    return std::filesystem::path(__FILE__).parent_path() / "output";',
        '}',
        '',
        '// Helper to save page to file',
        'void save_page(const std::string& filename, page& pg) {',
        '    auto output_dir = get_output_dir();',
        '    std::filesystem::create_directories(output_dir);',
        '    std::ofstream file(output_dir / filename);',
        '    file << pg.html();',
        '}',
        '',
        '} // anonymous namespace',
        '',
        f'TEST_CASE("{function_name}", "[output][generated]") {{',
        '    page pg;',
        '',
    ]

    # Add the converted content
    for line in converter.output_lines:
        lines.append('    ' + line)

    # Close the function
    lines.extend([
        '',
        '    // The root elements are already added to pg in the conversion',
        '    save_page("generated_output.html", pg);',
        '',
        '    CHECK(std::filesystem::exists(get_output_dir() / "generated_output.html"));',
        '}',
    ])

    return '\n'.join(lines)


def main():
    parser = argparse.ArgumentParser(
        description='Convert HTML to CPP_HTML_GEN C++ code'
    )
    parser.add_argument('input', help='Input HTML file')
    parser.add_argument('--output', '-o', help='Output C++ file (default: stdout)')
    parser.add_argument('--function-name', '-f', default='Generated HTML page',
                       help='Name for the generated test case')

    args = parser.parse_args()

    # Read input file
    with open(args.input, 'r', encoding='utf-8') as f:
        html_content = f.read()

    # Convert
    cpp_code = convert_html_to_cpp(html_content, args.function_name)

    # Output
    if args.output:
        with open(args.output, 'w', encoding='utf-8') as f:
            f.write(cpp_code)
        print(f"Generated {args.output}")
    else:
        print(cpp_code)


if __name__ == '__main__':
    main()
