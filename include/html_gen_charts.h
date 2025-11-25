/*  ===================================================================
*                      HTML Generator Library
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#ifndef HTML_GEN_CHARTS__INCLUDED
#define HTML_GEN_CHARTS__INCLUDED

#include "html_gen.h"
#include <cfloat>
#include <chrono>
#include <vector>
#include <string>

namespace chart {

    class line_chart {
      public:
        std::string m_id;
        std::string m_data_name;
        std::string m_height;
        std::string m_color;
        std::vector<double> m_values;

      public:
        line_chart();
        void add(double value);
        [[nodiscard]] std::string html();
    };

    /////////////////////////////////////////////////////////////////////////////////////////

    class timeseries_line_chart {
      public:
        std::string m_id;
        std::string m_data_name;
        std::string m_height;
        std::string m_color;
        std::vector<double> m_values;
        std::vector<std::chrono::system_clock::time_point> m_timestamps;

      public:
        timeseries_line_chart();
        void add(const std::chrono::system_clock::time_point& ts, double value);
        [[nodiscard]] std::string html();
    };

    /////////////////////////////////////////////////////////////////////////////////////////

    class bar_chart {
      public:
        std::string m_id;
        std::string m_data_name;
        std::string m_height;
        std::vector<double> m_values;
        std::vector<std::string> m_categories;

      public:
        bar_chart();
        void add(const std::string& category, double value);
        [[nodiscard]] std::string html();
    };

}

#endif
