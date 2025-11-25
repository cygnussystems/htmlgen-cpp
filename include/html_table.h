/*  ===================================================================
*                         HtmlGen++
*            Copyright (c) 2015-2024 Peter Ritter
*                  Licensed under MIT License
*  ====================================================================
*/

#ifndef HTML_TABLE__INCLUDED
#define HTML_TABLE__INCLUDED

#include "html_core.h"

namespace html {

        /////////////////////////////////////////////////////////////////////////////////////

        class td : public element {
          public:
            td() { element::m_type = td_t; m_newline_after_element = true; }
            td(const std::string& _s) {
                element::m_type = td_t;
                m_newline_after_element = true;
                add(text(_s));
            }
            td( element& _e) {
                element::m_type = td_t;
                m_newline_after_element = true;
                add(_e);
            }
            td( element&& _e) {
                element::m_type = td_t;
                m_newline_after_element = true;
                add(std::move(_e));
            }
            virtual ~td() { ; }
            HTML_FLUENT_METHODS(td)
            td& colspan(int n) { add_attr("colspan", std::to_string(n)); return *this; }
            td& rowspan(int n) { add_attr("rowspan", std::to_string(n)); return *this; }
            td& headers(const std::string& h) { add_attr("headers", h); return *this; }
            virtual element* make_copy()const override {
                td* ptr = new html::td();
                ptr->copy(*this);
                return ptr;
            }
        };
        typedef td cell;

        /////////////////////////////////////////////////////////////////////////////////////

        class tr : public element {
          public:
            tr() {
                m_type = tr_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            // Variadic constructor for multiple children (td/th)
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            tr(Args&&... args) {
                m_type = tr_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~tr() { ; }
            HTML_FLUENT_METHODS(tr)

            virtual element* make_copy()const override {
                tr* ptr = new tr();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class row : public tr {
          public:
            row(size_t _num_field = 0) {
                size_t cnt = 0;
                while(cnt < _num_field) {
                    add(td());
                    ++cnt;
                }
            }
            row& add_all(const html::attr& _a) {
                for(auto& e : m_elements) {
                    e->add_attr(_a);
                }
                return *this;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class hrow : public tr {
          public:
            hrow(size_t _num_col = 0) {
                size_t cnt = 0;
                while(cnt < _num_col) {
                    add(td());
                    ++cnt;
                }
            }
            hrow& add_all(const html::attr& _a) {
                for(auto& e : m_elements) {
                    e->add_attr(_a);
                }
                return *this;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class th : public element {
          public:
            th() {
                m_type = th_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            th(const std::string& _s) {
                m_type = th_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add(text(_s));
            }
            virtual ~th() { ; }
            HTML_FLUENT_METHODS(th)
            th& scope(const std::string& s) { add_attr("scope", s); return *this; }
            th& colspan(int n) { add_attr("colspan", std::to_string(n)); return *this; }
            th& rowspan(int n) { add_attr("rowspan", std::to_string(n)); return *this; }
            th& abbr(const std::string& s) { add_attr("abbr", s); return *this; }
            th& headers(const std::string& h) { add_attr("headers", h); return *this; }

            virtual element* make_copy()const override {
                th* ptr = new th();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class tbody : public element {
          public:
            tbody() {
                m_type = tbody_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            // Variadic constructor for multiple children (tr)
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            tbody(Args&&... args) {
                m_type = tbody_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~tbody() { ; }
            HTML_FLUENT_METHODS(tbody)

            virtual element* make_copy()const override {
                tbody* ptr = new tbody();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class thead : public element {
          public:
            thead() {
                m_type = thead_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            // Variadic constructor for multiple children (tr)
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            thead(Args&&... args) {
                m_type = thead_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~thead() { ; }
            HTML_FLUENT_METHODS(thead)

            virtual element* make_copy()const override {
                thead* ptr = new thead();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class tfoot : public element {
          public:
            tfoot() {
                m_type = tfoot_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            // Variadic constructor for multiple children (tr)
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            tfoot(Args&&... args) {
                m_type = tfoot_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~tfoot() { ; }
            HTML_FLUENT_METHODS(tfoot)

            virtual element* make_copy()const override {
                tfoot* ptr = new tfoot();
                ptr->copy(*this);
                return ptr;
            }
        };

        class caption : public element {
          public:
            caption() {
                m_type = caption_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            caption(const std::string& _s) {
                m_type = caption_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add(text(_s));
            }
            // Variadic constructor for nested children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 1)>>
            caption(Args&&... args) {
                m_type = caption_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~caption() { ; }
            HTML_FLUENT_METHODS(caption)

            virtual element* make_copy()const override {
                caption* ptr = new caption();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class table : public element {
          public:
            html::caption caption;
            html::thead thead;
            html::tfoot tfoot;
            html::tbody tbody;
          public:
            table() {
                element::m_type = table_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            // Variadic constructor for multiple children (tr)
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            table(Args&&... args) {
                element::m_type = table_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~table() { ; }
            HTML_FLUENT_METHODS(table)
          public:
            virtual void write_html(std::ostream& _s)override {
                element::write_open_tag(_s);

                if(caption.size()) {
                    caption.page(element::page());
                    caption.write_html(_s);
                }

                if(thead.size()) {
                    thead.page(element::page());
                    thead.write_html(_s);
                }

                if(tbody.size()) {
                    tbody.page(element::page());
                    tbody.write_html(_s);
                } else {
                    element::write_elements(_s);
                }

                if(tfoot.size()) {
                    tfoot.page(element::page());
                    tfoot.write_html(_s);
                }
                element::write_close_tag(_s);
            }

            virtual element* make_copy()const override {
                table* ptr = new table();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////
        // Table Structure Elements
        /////////////////////////////////////////////////////////////////////////////////////

        class colgroup : public element {
          public:
            colgroup() {
                element::m_type = colgroup_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            // Variadic constructor for nested col elements
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            colgroup(Args&&... args) {
                element::m_type = colgroup_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            HTML_FLUENT_METHODS(colgroup)
            colgroup& span(int n) { add_attr("span", std::to_string(n)); return *this; }
            colgroup& span_attr(int n) { add_attr("span", std::to_string(n)); return *this; }
            virtual ~colgroup() { ; }
            virtual element* make_copy()const override {
                colgroup* ptr = new colgroup();
                ptr->copy(*this);
                return ptr;
            }
        };

        class col : public element {
          public:
            col() {
                element::m_type = col_t;
                element::m_has_closing_tag = false;
                element::m_is_container = false;
            }
            HTML_FLUENT_METHODS(col)
            col& span(int n) { add_attr("span", std::to_string(n)); return *this; }
            col& span_attr(int n) { add_attr("span", std::to_string(n)); return *this; }
            virtual ~col() { ; }
            virtual element* make_copy()const override {
                col* ptr = new col();
                ptr->copy(*this);
                return ptr;
            }
        };

}//html

#endif
