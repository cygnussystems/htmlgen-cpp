/*  ===================================================================
*                         HtmlGen++
*            Copyright (c) 2015-2024 Peter Ritter
*                  Licensed under MIT License
*  ====================================================================
*/

#include "../include/html_gen_charts.h"
#include <stdexcept>
#include <cassert>
#include <format>

namespace chart {

    line_chart::line_chart() {
        m_id = "chart";
        m_data_name = "data";
        m_height = "350";
        m_color = "#3498db";
    }

    void line_chart::add(double value) {
        m_values.push_back(value);
    }

    std::string line_chart::html() {
        if (m_values.empty()) {
            throw std::runtime_error("line_chart: no data added");
        }

        // Auto-register dependency
        if (html::detail::current_page) {
            html::detail::current_page->require(html::dependency::apexcharts_js);
        }

        // Build data array
        std::string data;
        for (size_t i = 0; i < m_values.size(); i++) {
            if (i > 0) data += ", ";
            data += std::to_string(m_values[i]);
        }

        // Generate ApexCharts script
        std::string script = std::format(R"(
var options_{0} = {{
  chart: {{
    type: 'line',
    height: {1},
    toolbar: {{ show: false }}
  }},
  series: [{{
    name: '{2}',
    data: [{3}]
  }}],
  colors: ['{4}'],
  stroke: {{ curve: 'smooth', width: 2 }},
  grid: {{ show: true }},
  xaxis: {{ labels: {{ show: false }} }},
  yaxis: {{ labels: {{ show: true }} }}
}};
var chart_{0} = new ApexCharts(document.querySelector("#{0}"), options_{0});
chart_{0}.render();
)", m_id, m_height, m_data_name, data, m_color);

        html::element_group group;
        group << html::div().id(m_id);
        group << html::script(script);
        return group.html();
    }

    ///////////////////////////////////////////////////////////////////////////////

    timeseries_line_chart::timeseries_line_chart() {
        m_id = "chart";
        m_data_name = "data";
        m_height = "350";
        m_color = "#3498db";
    }

    void timeseries_line_chart::add(const std::chrono::system_clock::time_point& ts, double value) {
        m_values.push_back(value);
        m_timestamps.push_back(ts);
    }

    std::string timeseries_line_chart::html() {
        if (m_values.empty()) {
            throw std::runtime_error("timeseries_line_chart: no data added");
        }

        // Auto-register dependency
        if (html::detail::current_page) {
            html::detail::current_page->require(html::dependency::apexcharts_js);
        }

        // Build data array with timestamps
        std::string data;
        for (size_t i = 0; i < m_values.size(); i++) {
            if (i > 0) data += ", ";
            // Convert to milliseconds since epoch for ApexCharts
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                m_timestamps[i].time_since_epoch()).count();
            data += std::format("{{ x: {}, y: {} }}", ms, m_values[i]);
        }

        // Generate ApexCharts script
        std::string script = std::format(R"(
var options_{0} = {{
  chart: {{
    type: 'line',
    height: {1},
    toolbar: {{ show: false }}
  }},
  series: [{{
    name: '{2}',
    data: [{3}]
  }}],
  colors: ['{4}'],
  stroke: {{ curve: 'smooth', width: 2 }},
  grid: {{ show: true }},
  xaxis: {{
    type: 'datetime',
    labels: {{ datetimeUTC: false }}
  }},
  yaxis: {{ labels: {{ show: true }} }},
  tooltip: {{
    x: {{ format: 'yyyy-MM-dd HH:mm:ss' }}
  }}
}};
var chart_{0} = new ApexCharts(document.querySelector("#{0}"), options_{0});
chart_{0}.render();
)", m_id, m_height, m_data_name, data, m_color);

        html::element_group group;
        group << html::div().id(m_id);
        group << html::script(script);
        return group.html();
    }

    ///////////////////////////////////////////////////////////////////////////////

    bar_chart::bar_chart() {
        m_id = "chart";
        m_data_name = "data";
        m_height = "350";
    }

    void bar_chart::add(const std::string& category, double value) {
        m_values.push_back(value);
        m_categories.push_back(category);
    }

    std::string bar_chart::html() {
        if (m_values.empty()) {
            throw std::runtime_error("bar_chart: no data added");
        }

        // Auto-register dependency
        if (html::detail::current_page) {
            html::detail::current_page->require(html::dependency::apexcharts_js);
        }

        // Build data array
        std::string data;
        for (size_t i = 0; i < m_values.size(); i++) {
            if (i > 0) data += ", ";
            data += std::to_string(m_values[i]);
        }

        // Build categories array
        std::string categories;
        for (size_t i = 0; i < m_categories.size(); i++) {
            if (i > 0) categories += ", ";
            categories += std::format("'{}'", m_categories[i]);
        }

        // Generate ApexCharts script
        std::string script = std::format(R"(
var options_{0} = {{
  chart: {{
    type: 'bar',
    height: {1},
    toolbar: {{ show: false }}
  }},
  series: [{{
    name: '{2}',
    data: [{3}]
  }}],
  plotOptions: {{
    bar: {{ borderRadius: 4, horizontal: false }}
  }},
  grid: {{ show: true }},
  xaxis: {{
    categories: [{4}],
    labels: {{ rotate: -45 }}
  }},
  yaxis: {{ labels: {{ show: true }} }}
}};
var chart_{0} = new ApexCharts(document.querySelector("#{0}"), options_{0});
chart_{0}.render();
)", m_id, m_height, m_data_name, data, categories);

        html::element_group group;
        group << html::div().id(m_id);
        group << html::script(script);
        return group.html();
    }

}
