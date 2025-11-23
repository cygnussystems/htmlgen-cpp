/*  ===================================================================
*                      HTML Generator Library
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#ifndef HTML_RESOURCES__INCLUDED
#define HTML_RESOURCES__INCLUDED

#include <string>
#include <cstddef>

namespace resources {

        //---------------------------------------------------------------------------------
        // Bootstrap CSS (minified)
        //---------------------------------------------------------------------------------
        extern const char bootstrap_min_css[];
        extern const size_t bootstrap_min_css_size;

        inline std::string bootstrap_css_string() {
            return std::string(bootstrap_min_css, bootstrap_min_css_size);
        }

        //---------------------------------------------------------------------------------
        // Bootstrap JS (minified)
        //---------------------------------------------------------------------------------
        extern const char bootstrap_min_js[];
        extern const size_t bootstrap_min_js_size;

        inline std::string bootstrap_js_string() {
            return std::string(bootstrap_min_js, bootstrap_min_js_size);
        }

        //---------------------------------------------------------------------------------
        // jQuery JS (minified)
        //---------------------------------------------------------------------------------
        extern const char jquery_min_js[];
        extern const size_t jquery_min_js_size;

        inline std::string jquery_js_string() {
            return std::string(jquery_min_js, jquery_min_js_size);
        }

        //---------------------------------------------------------------------------------
        // D3.js (minified)
        //---------------------------------------------------------------------------------
        extern const char d3_min_js[];
        extern const size_t d3_min_js_size;

        inline std::string d3_js_string() {
            return std::string(d3_min_js, d3_min_js_size);
        }

        //---------------------------------------------------------------------------------
        // C3.js (minified)
        //---------------------------------------------------------------------------------
        extern const char c3_min_js[];
        extern const size_t c3_min_js_size;

        inline std::string c3_js_string() {
            return std::string(c3_min_js, c3_min_js_size);
        }

        //---------------------------------------------------------------------------------
        // C3 CSS
        //---------------------------------------------------------------------------------
        extern const char c3_css[];
        extern const size_t c3_css_size;

        inline std::string c3_css_string() {
            return std::string(c3_css, c3_css_size);
        }

} // namespace resources

#endif
