#!/usr/bin/env python3
"""
HTML DOM Tree Comparison Tool

Compares two HTML files by parsing them into DOM trees and comparing
structure, attributes, and text content.

Usage:
    python compare_html.py expected.html actual.html [--verbose]
"""

import argparse
import sys
from html.parser import HTMLParser
from typing import List, Dict, Optional, Tuple, Any


class DOMNode:
    """Represents a node in the DOM tree."""

    def __init__(self, tag: str, attrs: Dict[str, str] = None):
        self.tag = tag
        self.attrs = attrs or {}
        self.children: List['DOMNode'] = []
        self.text = ""
        self.parent: Optional['DOMNode'] = None

    def add_child(self, child: 'DOMNode'):
        child.parent = self
        self.children.append(child)

    def add_text(self, text: str):
        # Normalize whitespace
        normalized = ' '.join(text.split())
        if normalized:
            if self.text:
                self.text += ' '
            self.text += normalized

    def path(self) -> str:
        """Get the path to this node from root."""
        if self.parent is None:
            return self.tag

        # Find index among siblings with same tag
        if self.parent:
            same_tag_siblings = [c for c in self.parent.children if c.tag == self.tag]
            if len(same_tag_siblings) > 1:
                idx = same_tag_siblings.index(self)
                return f"{self.parent.path()} > {self.tag}[{idx}]"

        return f"{self.parent.path()} > {self.tag}"

    def __repr__(self):
        return f"<{self.tag} {self.attrs}>"


class DOMParser(HTMLParser):
    """Parses HTML into a DOM tree."""

    # Void elements that don't have closing tags
    VOID_ELEMENTS = {
        'br', 'hr', 'img', 'input', 'meta', 'link', 'col', 'area',
        'base', 'embed', 'param', 'source', 'track', 'wbr'
    }

    def __init__(self):
        super().__init__()
        self.root = DOMNode('root')
        self.current = self.root
        self.node_count = 0

    def handle_starttag(self, tag: str, attrs: List[Tuple[str, Optional[str]]]):
        # Convert attrs to dict
        attr_dict = {}
        for name, value in attrs:
            attr_dict[name] = value if value is not None else name

        node = DOMNode(tag, attr_dict)
        self.current.add_child(node)
        self.node_count += 1

        # Only push to stack if not a void element
        if tag.lower() not in self.VOID_ELEMENTS:
            self.current = node

    def handle_endtag(self, tag: str):
        if tag.lower() in self.VOID_ELEMENTS:
            return

        # Pop up to find matching tag
        while self.current.parent and self.current.tag != tag:
            self.current = self.current.parent

        if self.current.parent:
            self.current = self.current.parent

    def handle_data(self, data: str):
        self.current.add_text(data)

    def get_root(self) -> DOMNode:
        return self.root


class HTMLComparator:
    """Compares two DOM trees and reports differences."""

    def __init__(self, verbose: bool = False):
        self.verbose = verbose
        self.differences: List[str] = []
        self.nodes_compared = 0

    def compare_files(self, file1: str, file2: str) -> bool:
        """Compare two HTML files. Returns True if identical."""

        # Parse both files
        with open(file1, 'r', encoding='utf-8') as f:
            content1 = f.read()

        with open(file2, 'r', encoding='utf-8') as f:
            content2 = f.read()

        parser1 = DOMParser()
        parser1.feed(content1)
        root1 = parser1.get_root()

        parser2 = DOMParser()
        parser2.feed(content2)
        root2 = parser2.get_root()

        print(f"Comparing HTML files...")
        print(f"  File 1: {file1} ({parser1.node_count} elements)")
        print(f"  File 2: {file2} ({parser2.node_count} elements)")
        print()

        # Compare trees
        self.compare_nodes(root1, root2, "root")

        # Report results
        if self.differences:
            print(f"FAIL: Found {len(self.differences)} difference(s):\n")
            for diff in self.differences:
                print(f"  {diff}")
            print()
            return False
        else:
            print(f"PASS: Files are structurally identical ({self.nodes_compared} nodes compared)")
            return True

    def compare_nodes(self, node1: DOMNode, node2: DOMNode, path: str):
        """Recursively compare two nodes."""

        self.nodes_compared += 1

        # Compare tag names
        if node1.tag != node2.tag:
            self.differences.append(
                f"Tag mismatch at {path}: expected '{node1.tag}', got '{node2.tag}'"
            )
            return  # Can't compare further if tags differ

        # Compare attributes
        self.compare_attributes(node1, node2, path)

        # Compare text content
        if node1.text != node2.text:
            text1 = node1.text[:50] + "..." if len(node1.text) > 50 else node1.text
            text2 = node2.text[:50] + "..." if len(node2.text) > 50 else node2.text
            self.differences.append(
                f"Text mismatch at {path}: expected '{text1}', got '{text2}'"
            )

        # Compare children count
        if len(node1.children) != len(node2.children):
            self.differences.append(
                f"Child count mismatch at {path}: expected {len(node1.children)}, got {len(node2.children)}"
            )

            # Show which children are different
            if self.verbose:
                tags1 = [c.tag for c in node1.children]
                tags2 = [c.tag for c in node2.children]
                self.differences.append(f"  Expected children: {tags1}")
                self.differences.append(f"  Actual children: {tags2}")

        # Compare children recursively (up to the minimum count)
        min_children = min(len(node1.children), len(node2.children))
        for i in range(min_children):
            child1 = node1.children[i]
            child2 = node2.children[i]

            # Build child path
            same_tag_before = sum(1 for c in node1.children[:i] if c.tag == child1.tag)
            if same_tag_before > 0 or sum(1 for c in node1.children if c.tag == child1.tag) > 1:
                child_path = f"{path} > {child1.tag}[{same_tag_before}]"
            else:
                child_path = f"{path} > {child1.tag}"

            self.compare_nodes(child1, child2, child_path)

    def compare_attributes(self, node1: DOMNode, node2: DOMNode, path: str):
        """Compare attributes of two nodes."""

        attrs1 = node1.attrs
        attrs2 = node2.attrs

        # Check for missing attributes in node2
        for name, value in attrs1.items():
            if name not in attrs2:
                self.differences.append(
                    f"Missing attribute at {path}: '{name}' (expected value: '{value}')"
                )
            elif attrs2[name] != value:
                # Special handling for class attribute (order may differ)
                if name == 'class':
                    classes1 = set(value.split())
                    classes2 = set(attrs2[name].split())
                    if classes1 != classes2:
                        self.differences.append(
                            f"Class mismatch at {path}: expected '{value}', got '{attrs2[name]}'"
                        )
                else:
                    self.differences.append(
                        f"Attribute value mismatch at {path}: '{name}' expected '{value}', got '{attrs2[name]}'"
                    )

        # Check for extra attributes in node2
        for name in attrs2:
            if name not in attrs1:
                self.differences.append(
                    f"Extra attribute at {path}: '{name}' = '{attrs2[name]}'"
                )


def main():
    parser = argparse.ArgumentParser(
        description='Compare two HTML files by DOM structure'
    )
    parser.add_argument('expected', help='Expected (original) HTML file')
    parser.add_argument('actual', help='Actual (generated) HTML file')
    parser.add_argument('--verbose', '-v', action='store_true',
                       help='Show more detailed differences')

    args = parser.parse_args()

    comparator = HTMLComparator(verbose=args.verbose)
    success = comparator.compare_files(args.expected, args.actual)

    sys.exit(0 if success else 1)


if __name__ == '__main__':
    main()
