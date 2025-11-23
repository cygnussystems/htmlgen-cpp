/*  ===================================================================
*                      HTML Generator Library
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#include "../include/bootstrap.h"
#include <stdexcept>
#include <cassert>
#include <format>
#include <regex>

namespace web {

    namespace {
        // Local string replace utility
        void find_replace_all(std::string& str, const std::string& from, const std::string& to) {
            if (from.empty()) return;
            size_t start_pos = 0;
            while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
                str.replace(start_pos, from.length(), to);
                start_pos += to.length();
            }
        }
    }

    namespace image {
        rotator::rotator() {
            m_script = "<table border = '0' cellpadding = '0'>"
                "<tr>"
                "<td width = '100 % '><form method = 'POST' name = 'rotater'>"
                "<div align = 'center'><center><p>"
                "<script language = 'JavaScript1.1'>"
                "var photos = new Array();"
                "var which = 0;"
                "photos[0] = 'FIRST_IMAGE';"
                "SUBSEQUENT_IMAGES"
                "function backward()"
                "{"
                "	if(which>0) {"
                "		window.state = '';"
                "			which--;"
                "			document.images.photoslider.src = photos[which];"
                "	}"
                "}"
                "function forward()"
                "{"
                "	if(which<photos.length - 1) {"
                "	which++;"
                "		document.images.photoslider.src = photos[which];"
                "} else window.state = 'End of gallery';"
                "}"
                "</script>"
                "<input type = 'button' value = '&lt; &lt; Back' name = 'B2'"
                "onClick = 'backward()'> <input type = 'button' value = 'Next&gt; &gt; ' name = 'B1'"
                "onClick = 'forward()'><br>"
                "<a href = '#'  onClick = 'which = 1; backward(); return false'> <small> Start Over </small>  </a></p>"
                "</center>  </div>"
                "</form>"
                "</td>"
                "</tr>"
                "<tr>"
                "<td width = '100%'>"
                "<img src = 'FIRST_IMAGE' name = 'photoslider'>"
                "</td>"
                "</tr>"
                "</table>";
        }

        std::string rotator::html() {
            if (m_images.empty()) {
                throw std::runtime_error("rotator: no images added");
            }
            find_replace_all(m_script, "FIRST_IMAGE", m_images[0]);
            std::string lststr;
            if (m_images.size() > 1) {
                for (size_t c = 1; c < m_images.size(); c++) {
                    lststr += std::format("photos[{}] = '{}';", c, m_images[c]);
                }
            }
            find_replace_all(m_script, "SUBSEQUENT_IMAGES", lststr);
            return m_script;
        }

        void rotator::add_image(const std::string& _file) {
            m_images.push_back(_file);
        }
    }

    namespace chart {

        line_chart::line_chart() {
            m_sDataName = "data";
            m_Script = "var chart = c3.generate({ bindto: '#UNIQUE_CHART_NAME', "
                "data : { columns:[['DATA_NAME', CSV_NUMBERS_Y]], "
                "types : { DATA_NAME: 'CHART_TYPE'}, colors : {DATA_NAME:'COLOR'}}, "
                "grid: {x: {show: true}, y : {show: true}},"
                "point : {show:false}, "
                "axis : { x : { show:false}}"
                "}); ";
            //default values
            m_sID = "default_chart_id";
            m_sDataName = "default_data_name";
            m_sChartType = "line";
            m_sHeight = "200px";
            m_sColor = "#b2d0e8";
        }

        void line_chart::add(double _d) { m_values.push_back(_d); }

        std::string line_chart::html() {
            assert(!m_sID.empty());
            find_replace_all(m_Script, "UNIQUE_CHART_NAME", m_sID);
            find_replace_all(m_Script, "DATA_NAME", m_sDataName);
            find_replace_all(m_Script, "CHART_TYPE", m_sChartType);
            find_replace_all(m_Script, "COLOR", m_sColor);
            std::string s_numbers;
            for (size_t c = 0; c < m_values.size(); c++) {
                s_numbers += std::to_string(m_values[c]);
                if (c < m_values.size() - 1) {
                    s_numbers += ',';
                }
            }
            find_replace_all(m_Script, "CSV_NUMBERS_Y", s_numbers);
            web::html::element_group group;
            group << web::html::div().id(m_sID).style("height:" + m_sHeight);
            group << web::html::script(m_Script);
            return group.html();
        }

        ///////////////////////////////////////////////////////////////////////////////

        timeseries_line_chart::timeseries_line_chart() {
            m_sDataName = "data";
            m_Script =
                "var chart = c3.generate({"
                "bindto:'#UNIQUE_CHART_NAME',"
                "data : {"
                "x: 'x',"
                "x_format : '%Y-%m-%d %H:%M:%S', "
                "columns : ["
                "['x', CSV_TIMESTAMPS_X],"
                "['DATA_NAME', CSV_NUMBERS_Y]],"
                "types : { DATA_NAME: 'CHART_TYPE'} , colors : {DATA_NAME:'COLOR'}"
                "},"
                "axis: {"
                "x: {"
                "show: false,"
                "type : 'timeseries',"
                "tick : {"
                "format: '%Y-%m-%d %H:%M:%S'"
                "}"
                "},"
                "y:{"
                "min: Y_MINIMUM"
                "}    },"
                "axes: {"
                "DATA_NAME: 'y'"
                "},"
                "point : {show:false},"
                "grid : {x: {show: true}, y : {show: true}}"
                "});";
            //default values
            m_sID = "default_chart_id";
            m_sDataName = "default_data_name";
            m_sChartType = "line";
            m_sHeight = "200px";
            m_sColor = "#b2d0e8";
        }

        void timeseries_line_chart::add(const std::chrono::system_clock::time_point& ts, double _d) {
            m_values.push_back(_d);
            m_timestamps.push_back(ts);
            if (_d < m_dMin) {
                m_dMin = _d;
            }
        }

        std::string timeseries_line_chart::html() {
            assert(!m_values.empty());
            assert(!m_sID.empty());
            find_replace_all(m_Script, "UNIQUE_CHART_NAME", m_sID);
            find_replace_all(m_Script, "DATA_NAME", m_sDataName);
            find_replace_all(m_Script, "CHART_TYPE", m_sChartType);
            find_replace_all(m_Script, "COLOR", m_sColor);
            std::string s_numbers;
            for (size_t c = 0; c < m_values.size(); c++) {
                s_numbers += std::to_string(m_values[c]);
                if (c < m_values.size() - 1) {
                    s_numbers += ',';
                }
            }
            std::string s_timestamps;
            for (size_t c = 0; c < m_timestamps.size(); c++) {
                s_timestamps += "'";
                s_timestamps += std::format("{:%Y-%m-%d %H:%M:%S}", m_timestamps[c]);
                s_timestamps += "'";
                if (c < m_timestamps.size() - 1) {
                    s_timestamps += ',';
                }
            }
            find_replace_all(m_Script, "CSV_NUMBERS_Y", s_numbers);
            find_replace_all(m_Script, "CSV_TIMESTAMPS_X", s_timestamps);
            find_replace_all(m_Script, "Y_MINIMUM", std::to_string(m_dMin));
            web::html::element_group group;
            group << web::html::div().id(m_sID).style("height:" + m_sHeight);
            group << web::html::script(m_Script);
            return group.html();
        }

        ///////////////////////////////////////////////////////////////////////////////

        bar_chart::bar_chart() {
            m_sDataName = "data";
            m_Script = "var chart = c3.generate({ bindto: '#UNIQUE_CHART_NAME', "
                "data : { x : 'x', columns:[['x', CSV_NAMES_X], ['DATA_NAME', CSV_NUMBERS_Y]], "
                "type : 'bar' },"
                "grid : {x: {show: true}, y : {show: true}},"
                "axis: {x: {type: 'category' , tick:{rotate:90}, height:90}}"
                "}); ";
            //default values
            m_sID = "default_chart_id";
            m_sDataName = "default_data_name";
            m_sChartType = "bar";
            m_sHeight = "200px";
        }

        void bar_chart::add(const std::string& _xlabel, double _d) {
            m_values.push_back(_d);
            m_xnames.push_back(_xlabel);
        }

        std::string bar_chart::html() {
            assert(!m_sID.empty());
            find_replace_all(m_Script, "UNIQUE_CHART_NAME", m_sID);
            find_replace_all(m_Script, "DATA_NAME", m_sDataName);
            find_replace_all(m_Script, "CHART_TYPE", m_sChartType);
            std::string s_numbers;
            for (size_t c = 0; c < m_values.size(); c++) {
                s_numbers += std::to_string(m_values[c]);
                if (c < m_values.size() - 1) {
                    s_numbers += ',';
                }
            }
            std::string s_xnames;
            for (size_t c = 0; c < m_xnames.size(); c++) {
                s_xnames += std::format("'{}'", m_xnames[c]);
                if (c < m_xnames.size() - 1) {
                    s_xnames += ',';
                }
            }
            find_replace_all(m_Script, "CSV_NUMBERS_Y", s_numbers);
            find_replace_all(m_Script, "CSV_NAMES_X", s_xnames);
            web::html::element_group group;
            group << web::html::div().id(m_sID).style("height:" + m_sHeight);
            group << web::html::script(m_Script);
            return group.html();
        }
    }

    namespace html {
        namespace bootstrap {
            // All bootstrap classes are header-only
        }
    }
}
