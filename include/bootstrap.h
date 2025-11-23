/*  ===================================================================
*                      HTML Generator Library
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#ifndef HTML_BOOTSTRAP__INCLUDED
#define HTML_BOOTSTRAP__INCLUDED

#include "html_tags.h"
#include <cfloat>
#include <chrono>
#include <format>

namespace image {
        class rotator {
          public:
            std::vector<std::string> m_images;
            std::string m_script;
          public:
            rotator();
            void add_image(const std::string& file);
            [[nodiscard]] std::string html();
        };
}

namespace chart {
        class line_chart {
            std::string m_Script;
          public:
            std::string m_sID;
            std::string m_sDataName;
            std::string m_sChartType;
            std::string m_sHeight;
            std::string m_sColor;
            std::vector<double> m_values;
          public:
            line_chart();
            void add(double _d);
          public:
            [[nodiscard]] std::string html();
        };

        /////////////////////////////////////////////////////////////////////////////////////////

        class timeseries_line_chart {
            std::string m_Script;
          public:
            std::string m_sID;
            std::string m_sDataName;
            std::string m_sChartType;
            std::string m_sHeight;
            std::string m_sColor;
            std::string m_sYMin;
            double m_dMin = DBL_MAX;
            std::vector<double> m_values;
            std::vector<std::chrono::system_clock::time_point> m_timestamps;
            double m_dMinY;
          public:
            timeseries_line_chart();
            void add(const std::chrono::system_clock::time_point& ts, double _d);
          public:
            [[nodiscard]] std::string html();
        };

        /////////////////////////////////////////////////////////////////////////////////////////

        class bar_chart {
            std::string m_Script;
          public:
            std::string m_sID;
            std::string m_sDataName;
            std::string m_sChartType;
            std::string m_sHeight;
            std::vector<double> m_values;
            std::vector<std::string> m_xnames;
          public:
            bar_chart();
            void add(const std::string& xlabel, double _d);
          public:
            [[nodiscard]] std::string html();
        };
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace html {
    namespace bootstrap {

            class container : public html::div {
              public:
                container() { cl("container"); }
                container(element& _e) {
                    cl("container");
                    add(_e);
                }
            };

            class row : public html::div {
              public:
                row() { cl("row clearfix"); }
                row(element& _e) {
                    cl("row clearfix");
                    add(_e);
                }
            };

            class column : public html::div {
              public:
                column(int _grid_width) {
                    cl(std::string("column col-md-") + std::to_string(_grid_width));
                }
            };

            ////////////////////////////////////////////////////////////////////////////////////////////////

            class navbar_dropdown : public html::li {
              public:
                navbar_dropdown(const std::string& _name) {
                    cl("dropdown");
                    anchor a;
                    a.href("#").cl("dropdown-toggle").add_attr("data-toggle", "dropdown");
                    a << span(_name).add_cl("label").add_cl("label-info") << html::b().cl("caret");
                    (*this) << a << html::ul().cl("dropdown-menu").id("listing");
                }

                void add_menu_item(const std::string& _name, const std::string& _target) {
                    get("listing") << (html::li() << (anchor().href(_target) << _name));
                }
            };

            class navbar : public html::nav {
              public:
                navbar() {
                    cl("navbar navbar-default");
                    role("navigation");

                    *this << div().cl("container-fluid").id("nav_container");

                    get("nav_container") << div().cl("navbar-header").id("nav_header");

                    get("nav_container") << div().cl("collapse navbar-collapse navbar-inverse").id("menu_parent");
                    get("menu_parent") << ul().cl("nav navbar-nav").id("menu_list");

                    get("menu_parent") << ul().cl("nav navbar-nav navbar-right").id("menu_list_right");
                }
                element& add_entry(html::element& _e, const std::string& _id) {
                    get("menu_list") << html::li(_e).id(_id);
                    return *this;
                }
                element& add_entry(html::element&& e, const std::string& id) {
                    get("menu_list") << html::li(std::move(e)).id(id);
                    return *this;
                }
                element& add_entry_right(html::element& _e, const std::string& _id) {
                    get("menu_list_right") << html::li(_e).id(_id);
                    return *this;
                }
                element& add_entry_right(html::element&& _e, const std::string& _id) {
                    get("menu_list_right") << html::li(std::move(_e)).id(_id);
                    return *this;
                }
                element& add_dropdown(html::element& _e, const std::string& _id) {
                    get("menu_list") << _e.id(_id);
                    return *this;
                }

                element& add_active_entry(html::element& _e, const std::string& _id) {
                    get("menu_list") << html::li(_e).cl("active").id(_id);
                    return *this;
                }

                element& add_brand(html::element& _e) {
                    get("nav_header") << _e.cl("navbar-brand");
                    return *this;
                }
            };

    }//bootstrap
}//html

#endif
