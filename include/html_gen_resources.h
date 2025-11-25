/*  ===================================================================
*                         HtmlGen++
*            Copyright (c) 2015-2024 Peter Ritter
*                  Licensed under MIT License
*  ====================================================================
*/

#ifndef HTML_GEN_RESOURCES__INCLUDED
#define HTML_GEN_RESOURCES__INCLUDED

#include <string>
#include <cstddef>

namespace resources {

        //---------------------------------------------------------------------------------
        // Bootstrap 5 CSS (minified)
        //---------------------------------------------------------------------------------
        extern const char bootstrap_min_css[];
        extern const size_t bootstrap_min_css_size;

        inline std::string bootstrap_css_string() {
            return std::string(bootstrap_min_css, bootstrap_min_css_size);
        }

        //---------------------------------------------------------------------------------
        // Bootstrap 5 JS Bundle (minified, includes Popper)
        //---------------------------------------------------------------------------------
        extern const char bootstrap_min_js[];
        extern const size_t bootstrap_min_js_size;

        inline std::string bootstrap_js_string() {
            return std::string(bootstrap_min_js, bootstrap_min_js_size);
        }

        //---------------------------------------------------------------------------------
        // ApexCharts JS (minified)
        //---------------------------------------------------------------------------------
        extern const char apexcharts_min_js[];
        extern const size_t apexcharts_min_js_size;

        inline std::string apexcharts_js_string() {
            return std::string(apexcharts_min_js, apexcharts_min_js_size);
        }

} // namespace resources

#endif
