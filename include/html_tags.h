/*  ===================================================================
*                      HTML Generator Library
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#ifndef HTML_TAGS__INCLUDED
#define HTML_TAGS__INCLUDED

#include <vector>
#include <string>
#include <string_view>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <cassert>

namespace web {

    namespace html {

        // HTML escape utility - escapes <, >, &, ", '
        [[nodiscard]] std::string html_escape(std::string_view input);

        // Raw HTML wrapper - content will not be escaped
        struct raw_html {
            std::string content;
            explicit raw_html(std::string_view s) : content(s) {}
        };

        enum element_t {
            undefined_t = 0,
            body_t,
            head_t,
            title_t,
            meta_t,
            element_group_t,

            div_t,

            text_t,
            script_t,
            img_t,
            a_t,
            link_t,
            style_t,
            nav_t,
            span_t,

            h1_t,
            h2_t,
            h3_t,
            h4_t,
            h5_t,
            h6_t,

            p_t,
            small_t,
            em_t,
            strong_t,
            b_t,
            textarea_t,

            br_t,
            hr_t,

            table_t,
            tr_t,
            td_t,
            tbody_t,
            thead_t,
            tfoot_t,
            th_t,
            caption_t,

            ul_t,
            ol_t,
            li_t,

            // Form elements
            form_t,
            input_t,
            button_t,
            select_t,
            option_t,
            label_t,
            fieldset_t,
            legend_t,

            // Semantic HTML5 elements
            header_t,
            footer_t,
            section_t,
            article_t,
            aside_t,
            main_t,

            // Media elements
            video_t,
            audio_t,
            source_t
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class attr {
          public:
            std::string name;
            std::string value;
          public:
            attr(const std::string& _name, const std::string& _value) {
                name = _name;
                value = _value;
            }
            attr(const attr& _other) {
                this->copy(_other);
            }
            ~attr() { ; }
            const attr& operator=(const attr& _other) {
                this->copy(_other);
                return *this;
            }
            void copy(const attr& _other) {
                name = _other.name;
                value = _other.value;
            }
        };
        //----------------------------------------------------------------

        std::string nbsp(size_t repeat = 1);


        //----------------------------------------------------------------
        class page;
        class element_group;

        class element {
          private:
            static std::vector<std::string> s_static_tag_names;
          protected:
            page* m_page_ptr;
            element* m_parent_ptr;
            element_t m_type;
            std::string m_tag;
          public:
            void parent(element* ptr) { m_parent_ptr = ptr; }
            element* parent() { return m_parent_ptr; }
            void page(page* ptr) { m_page_ptr = ptr; }
            html::page* page() { return m_page_ptr; }
          public:
            bool m_is_container;
            bool m_has_closing_tag;
            bool m_is_head_element;
            bool m_newline_after_tag;
            bool m_newline_after_element;
          public:
            std::string m_class_attr;
            std::string m_id_attr;
            std::string m_data_id_attr;
            std::string m_type_attr;
            std::string m_role_attr;
            std::string m_style_attr;
            std::string m_src_attr;
            std::string m_alt_attr;
            std::string m_width_attr;
            std::string m_height_attr;
            std::string m_href_attr;
            std::string m_rel_attr;

            std::string m_other_attr;
          public:
            std::vector<std::unique_ptr<element>> m_elements;
          private:
            void operator=(element&) = delete;
          public:
            element();
            element(const element&);
            virtual ~element();

            void copy(const element&);
            const std::string& tag()const;
          public:
            element& get(const std::string& id);
            element& get_child(const std::string& id);
            bool exists(const std::string& id);
            element& at(size_t);
            element* find(const std::string& id);
            element* find_child(const std::string& id);
          public:
            void add_attr(const std::string& name, const std::string& value);
            //
            const std::string& attr()const;
          public:
            element& id(const std::string&);
            const std::string& id()const;

            element& data_id(const std::string&);
            const std::string& data_id()const;

            element& cl(const std::string&);
            element& add_cl(const std::string&);
            const std::string& cl()const;

            element& type(const std::string&);
            const std::string& type()const;

            element& role(const std::string&);
            const std::string& role()const;

            element& rel(const std::string&);
            const std::string& rel()const;

            element& src(const std::string&);
            const std::string& src()const;

            element& height(const std::string&);
            const std::string& height()const;

            element& width(const std::string&);
            const std::string& width()const;

            element& alt(const std::string&);
            const std::string& alt()const;

            element& style(const std::string&);
            const std::string& style()const;

            element& href(const std::string&);
            const std::string& href()const;

          public:
            element& add_attr(const html::attr&);

          public:
            element& add(const html::attr&);
            virtual element& add(const std::string&);
            virtual element& add(const element&);
            virtual element& add(element&& e) { return add(static_cast<const element&>(e)); }
            element& add(element_group&);
            element& operator<<(const std::string&);
            element& operator<<(const element&);
            element& operator<<(element_group&);
            element& operator<<(html::attr&);

            // Add comprehensive rvalue overloads
            element& operator<<(html::attr&& rhs) { return *this << rhs; }
            element& operator<<(element&& rhs) { return *this << static_cast<const element&>(rhs); }
            element& operator<<(element_group&& rhs) { return *this << rhs; }


            element& operator<<=(const std::string&);
            element& operator<<=(const element&);
            element& operator<<=(element_group&);
          public:
            element& operator[](size_t);
            element& operator[](const std::string&);
          public:
            virtual element& content(const std::string&);
            virtual element& content(element&);

            void clear();
            void clear_all();
            bool empty()const;
            size_t size()const;
          protected:
            void write_elements(std::ostream&);
            void write_attributes(std::ostream&)const;
          public:
            std::string html();
            std::string html_string();
            std::string html_content_string();

          protected:
            void write_open_tag(std::ostream&)const;
            void write_close_tag(std::ostream&)const;
          public:
            virtual void write_html(std::ostream&);
            virtual element* make_copy()const;
        };

        std::ostream& operator<<(std::ostream&, web::html::element&);

        /////////////////////////////////////////////////////////////////////////////////////
        // Page head

        class head : public element {
          public:
            head() {
                element::m_type = head_t;
                m_newline_after_element = true;
                m_newline_after_tag = true;
            }
            virtual ~head() { ; }
            virtual element* make_copy()const override {
                head* ptr = new head();
                ptr->copy(*this);
                return ptr;
            }
        };



        /////////////////////////////////////////////////////////////////////////////////////

        class body : public element {
          public:
            body() { element::m_type = body_t; }
            virtual ~body() { ; }
            virtual element* make_copy()const override {
                body* ptr = new body();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class page : public element {

          public:
            html::head head;
            std::string preamble;
            bool m_bWriteNewlineAfterTag;
          public:
            page();
            virtual ~page();
          public:
            virtual element* make_copy()const override;
            virtual void write_html(std::ostream&) override;
        };
        std::ostream& operator<<(std::ostream& _s, page& _p);


        /////////////////////////////////////////////////////////////////////////////////////

        class text : public element {
          public:
            std::string m_text;
          public:
            text() {
                element::m_type = text_t;
                element::m_is_container = false;
            }
            text(const std::string& _s) {
                element::m_type = text_t;
                element::m_is_container = false;
                m_text = _s;
            }
            text(const char* _s) {
                element::m_type = text_t;
                element::m_is_container = false;
                m_text = _s;
            }
            virtual ~text() { ; }
            virtual void write_html(std::ostream& _s) override {
                assert(element::m_is_container == false);
                _s << m_text;
                if(m_newline_after_element)
                { _s << std::endl; }
            }
            virtual element* make_copy()const override {
                text* ptr = new text();
                ptr->copy(*this);
                ptr->m_text = m_text;
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class title : public element {
          public:
            title() {
                element::m_type = title_t;
                m_newline_after_element = true;
            }
            title(const std::string& _s) {
                element::m_type = title_t;
                m_newline_after_element = true;
                add(text(_s));
            }
            virtual ~title() { ; }
            virtual element* make_copy()const override {
                title* ptr = new title();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class element_group : public element {
          public:
            element_group(element_group& _g);
            element_group();
            virtual ~element_group() { ; }
            virtual element* make_copy() const override;
            virtual void write_html(std::ostream& _s) override {
                for(auto& e : m_elements) {
                    e->write_html(_s);
                }
            }
        };

        // Global operator+ overloads for all combinations
        element_group operator+(element&, element&);
        element_group operator+(element_group&, element_group&);
        element_group operator+(element_group&, element&);
        // C++20 rvalue compatibility - declarations only
        element_group operator+(element&&, element&&);
        element_group operator+(element&, element&&);
        element_group operator+(element&&, element&);

        /////////////////////////////////////////////////////////////////////////////////////

        class div : public element {
          public:
            div() {
                element::m_type = div_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            div(element& _e) {
                element::m_type = div_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add(_e);
            }
            div(element&& _e) {
                element::m_type = div_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add(std::move(_e));
            }
            virtual ~div() { ; }
            virtual element* make_copy()const override {
                div* ptr = new div();
                ptr->copy(*this);
                return ptr;
            }
        };



        /////////////////////////////////////////////////////////////////////////////////////

        class nav : public element {
          public:
            nav() {
                m_newline_after_tag = true;
                m_newline_after_element = true;
                element::m_type = nav_t;
            }
            nav(element& _e) {
                m_newline_after_tag = true;
                m_newline_after_element = true;
                element::m_type = nav_t;
                add(_e);
            }
            virtual ~nav() { ; }
            virtual element* make_copy()const override {
                nav* ptr = new nav();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class h1 : public element {
          public:
            h1() { m_type = h1_t; m_newline_after_element = true; }
            h1(const std::string& _s) {
                m_type = h1_t;
                m_newline_after_element = true;
                add(text(_s));
            }
            h1(const element& _e) {
                m_type = h1_t;
                m_newline_after_element = true;
                add(_e);
            }
            virtual ~h1() { ; }
            virtual element* make_copy()const override {
                h1* ptr = new h1();
                ptr->copy(*this);
                return ptr;
            }
        };

        class h2 : public element {
          public:
            h2() { m_type = h2_t; m_newline_after_element = true; }
            h2(const std::string& _s) {
                m_type = h2_t;
                m_newline_after_element = true;
                add(text(_s));
            }
            h2(const element& _e) {
                m_type = h2_t;
                m_newline_after_element = true;
                add(_e);
            }
            virtual ~h2() { ; }
            virtual element* make_copy()const override {
                h2* ptr = new h2();
                ptr->copy(*this);
                return ptr;
            }
        };

        class h3 : public element {
          public:
            h3() { m_type = h3_t; m_newline_after_element = true; }
            h3(const std::string& _s) {
                m_type = h3_t;
                m_newline_after_element = true;
                add(text(_s));
            }
            h3(const element& _e) {
                m_type = h3_t;
                m_newline_after_element = true;
                add(_e);
            }
            virtual ~h3() { ; }
            virtual element* make_copy()const override {
                h3* ptr = new h3();
                ptr->copy(*this);
                return ptr;
            }
        };

        class h4 : public element {
          public:
            h4() { m_type = h4_t; m_newline_after_element = true; }
            h4(const std::string& _s) {
                m_type = h4_t;
                m_newline_after_element = true;
                add(text(_s));
            }
            h4(const element& _e) {
                m_type = h4_t;
                m_newline_after_element = true;
                add(_e);
            }
            virtual ~h4() { ; }
            virtual element* make_copy()const override {
                h4* ptr = new h4();
                ptr->copy(*this);
                return ptr;
            }
        };

        class h5 : public element {
          public:
            h5() { m_type = h5_t; m_newline_after_element = true; }
            h5(const std::string& _s) {
                m_type = h5_t;
                m_newline_after_element = true;
                add(text(_s));
            }
            h5(const element& _e) {
                m_type = h5_t;
                m_newline_after_element = true;
                add(_e);
            }
            virtual ~h5() { ; }
            virtual element* make_copy()const override {
                h5* ptr = new h5();
                ptr->copy(*this);
                return ptr;
            }
        };

        class h6 : public element {
          public:
            h6() { m_type = h6_t; m_newline_after_element = true; }
            h6(const std::string& _s) {
                m_type = h6_t;
                m_newline_after_element = true;
                add(text(_s));
            }
            h6(const element& _e) {
                m_type = h6_t;
                m_newline_after_element = true;
                add(_e);
            }
            virtual ~h6() { ; }
            virtual element* make_copy()const override {
                h6* ptr = new h6();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class p : public element {
          public:
            p() { element::m_type = p_t; }
            p(const std::string& _s) {
                element::m_type = p_t;
                add(text(_s));
            }
            p(element& _e) {
                element::m_type = p_t;
                add(_e);
            }
            p(element&& _e) {
                element::m_type = p_t;
                add(std::move(_e));
            }
            virtual ~p() { ; }
            virtual element* make_copy()const override {
                p* ptr = new html::p();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class em : public element {
          public:
            em() { element::m_type = em_t; }
            em(const std::string& _s) {
                element::m_type = em_t;
                add(text(_s));
            }
            virtual ~em() { ; }
            virtual element* make_copy()const override {
                em* ptr = new html::em();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class strong : public element {
          public:
            strong() { element::m_type = strong_t; }
            strong(const std::string& _s) {
                element::m_type = strong_t;
                add(text(_s));
            }
            strong(element& _e) {
                element::m_type = strong_t;
                add(_e);
            }
            strong(element&& _e) {
                element::m_type = strong_t;
                add(std::move(_e));
            }

            virtual ~strong() { ; }
            virtual element* make_copy()const override {
                strong* ptr = new html::strong();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class b : public element {
          public:
            b() { element::m_type = b_t; }
            b(const std::string& _s) {
                element::m_type = b_t;
                add(text(_s));
            }
            b(element& _e) {
                element::m_type = b_t;
                add(_e);
            }
            virtual ~b() { ; }
            virtual element* make_copy()const override {
                html::b* ptr = new html::b();
                ptr->copy(*this);
                return ptr;
            }
        };




        /////////////////////////////////////////////////////////////////////////////////////

        class small_ : public element {
          public:
            small_() { element::m_type = small_t; }
            small_(const std::string& _s) {
                element::m_type = small_t;
                add(text(_s));
            }
            virtual ~small_() { ; }
            virtual element* make_copy()const override {
                small_* ptr = new html::small_();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class span : public element {
          public:
            span() { element::m_type = span_t; }
            span(const std::string& _s) {
                element::m_type = span_t;
                add(text(_s));
            }
            virtual ~span() { ; }
            virtual element* make_copy()const override {
                span* ptr = new html::span();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class ul : public element {
          public:
            ul() {
                element::m_type = ul_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }

            virtual ~ul() { ; }
            virtual element* make_copy()const override {
                ul* ptr = new html::ul();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class ol : public element {
          public:
            ol() { element::m_type = ol_t; m_newline_after_tag = true; m_newline_after_element = true; }

            virtual ~ol() { ; }
            virtual element* make_copy()const override {
                ol* ptr = new html::ol();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class li : public element {
          public:
            li() { element::m_type = li_t; }
            li(const std::string& _s) {
                element::m_type = li_t;
                m_newline_after_element = true;
                add(text(_s));
            }
            li(element& _e) {
                element::m_type = li_t;
                m_newline_after_element = true;
                add(_e);
            }
            li(element&& _e) {
                element::m_type = li_t;
                m_newline_after_element = true;
                add(std::move(_e));
            }
            virtual ~li() { ; }
            virtual element* make_copy()const override {
                li* ptr = new html::li();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class textarea : public element {
          public:
            textarea() { element::m_type = textarea_t; }
            textarea(const std::string& _s) {
                element::m_type = textarea_t;
                add(text(_s));
            }
            virtual ~textarea() { ; }
            virtual element* make_copy()const override {
                textarea* ptr = new html::textarea();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class br : public element {
          public:
            br() {
                element::m_type = br_t;
                element::m_has_closing_tag = false;
                element::m_is_container = false;
            }
            virtual ~br() { ; }
            virtual void write_html(std::ostream& _s)override {
                _s << "<br>";
            }
            virtual element* make_copy()const override {
                br* ptr = new br();
                ptr->copy(*this);
                return ptr;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////

        class hr : public element {
          public:
            hr() {
                element::m_type = hr_t;
                element::m_has_closing_tag = false;
                element::m_is_container = false;
            }
            virtual ~hr() { ; }
            virtual void write_html(std::ostream& _s)override {
                _s << "<hr>";
            }
            virtual element* make_copy()const override {
                hr* ptr = new hr();
                ptr->copy(*this);
                return ptr;
            }
        };


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
            virtual ~tr() { ; }

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
            virtual ~th() { ; }

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
            virtual ~tbody() { ; }

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
            virtual ~thead() { ; }

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
            virtual ~tfoot() { ; }

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
            virtual ~caption() { ; }

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
            virtual ~table() { ; }
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

        ////////////////////////////////////////////////////////////////////////////////////

        class script : public element {
          public:
            script() {
                element::m_type = script_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            script(const web::html::attr& _a) {
                element::m_type = script_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add(_a);
            }

            script(const web::html::attr& _a, const web::html::attr& _b) {
                element::m_type = script_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add(_a);
                add(_b);
            }

            script(const std::string& _s) {
                element::m_type = script_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add(text(_s));
            }
            virtual ~script() { ; }
          public:
            virtual element* make_copy()const override {
                script* ptr = new script();
                ptr->copy(*this);
                return ptr;
            }
        };

        ////////////////////////////////////////////////////////////////////////////////////

        class img : public element {
          public:
            img() {
                element::m_type = img_t;
                element::m_has_closing_tag = false;
                m_newline_after_element = true;
            }
            img(const std::string& _src, const std::string& _width = "") {
                element::m_type = img_t;
                element::m_has_closing_tag = false;
                m_newline_after_element = true;
                src(_src);
                if(!_width.empty())
                { width(_width); }
            }
            virtual ~img() { ; }
          public:
            virtual element* make_copy()const override {
                img* ptr = new img();
                ptr->copy(*this);
                return ptr;
            }
        };

        ////////////////////////////////////////////////////////////////////////////////////

        class link : public element {
          public:
            link() {
                m_type = link_t;
                element::m_is_container = false;
                element::m_has_closing_tag = false;
                element::m_newline_after_element = true;
            }
            virtual ~link() { ; }
          public:
            virtual element* make_copy()const override {
                link* ptr = new link();
                ptr->copy(*this);
                return ptr;
            }
        };

        ////////////////////////////////////////////////////////////////////////////////////

        class head_link : public link {
          public:
            head_link() { m_newline_after_element = true; }
            head_link(const html::attr& _a) {
                m_newline_after_element = true;
                add_attr(_a.name, _a.value);
            }
            head_link(const html::attr& _a, const html::attr& _b) {
                m_newline_after_element = true;
                add_attr(_a.name, _a.value);
                add_attr(_b.name, _b.value);
            }
            head_link(const html::attr& _a, const html::attr& _b, const html::attr& _c) {
                m_newline_after_element = true;
                add_attr(_a.name, _a.value);
                add_attr(_b.name, _b.value);
                add_attr(_c.name, _c.value);
            }

            virtual ~head_link() { ; }

            virtual element* make_copy()const override {
                head_link* ptr = new head_link();
                ptr->copy(*this);
                return ptr;
            }

        };

        ////////////////////////////////////////////////////////////////////////////////////

        class meta : public element {
          public:
            meta() {
                element::m_is_container = false;
                element::m_newline_after_element = true;
                element::m_type = meta_t;
                element::m_has_closing_tag = false;
            }
            meta(const html::attr& _a, const html::attr& _b) {
                element::m_is_container = false;
                element::m_newline_after_element = true;
                element::m_type = meta_t;
                element::m_has_closing_tag = false;
                add(_a);
                add(_b);
            }
            meta(const html::attr& _a, const html::attr& _b, const html::attr& _c) {
                element::m_is_container = false;
                element::m_newline_after_element = true;
                element::m_type = meta_t;
                element::m_has_closing_tag = false;
                add(_a);
                add(_b);
                add(_c);
            }

            virtual ~meta() { ; }

            virtual element* make_copy()const override {
                meta* ptr = new meta();
                ptr->copy(*this);
                return ptr;
            }

        };

        ////////////////////////////////////////////////////////////////////////////////////

        class anchor : public element {
          public:
            anchor() { element::m_type = a_t; }
            anchor(const std::string& _href) {
                element::m_type = a_t;
                href(_href);
            }

            anchor(const std::string& _href, const element& _e) {
                element::m_type = a_t;
                href(_href);
                add(_e);
            }
            anchor(const std::string& _href, const std::string& _text) {
                element::m_type = a_t;
                href(_href);
                add(text(_text));
            }
            virtual ~anchor() { ; }
          public:
            virtual element* make_copy()const override {
                anchor* ptr = new anchor();
                ptr->copy(*this);
                return ptr;
            }
        };

        ////////////////////////////////////////////////////////////////////////////////////

        class style : public element {
          public:
            style() {
                element::m_type = style_t;
                m_newline_after_element = true;
            }
            style(const std::string& _s) {
                element::m_type = style_t;
                m_newline_after_element = true;
                element::add(text(_s));
            }
            virtual ~style() { ; }
          public:
            virtual element* make_copy()const override {
                style* ptr = new style();
                ptr->copy(*this);
                return ptr;
            }
            virtual element& add(const std::string& _s) override {
                text t(_s);
                t.m_newline_after_element = true;
                element::add(t);
                return *this;
            }
        };

        ////////////////////////////////////////////////////////////////////////////////////
        // Form Elements
        ////////////////////////////////////////////////////////////////////////////////////

        class form : public element {
          public:
            form() {
                element::m_type = form_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            form& action(const std::string& _a) { add_attr("action", _a); return *this; }
            form& method(const std::string& _m) { add_attr("method", _m); return *this; }
            virtual ~form() { ; }
            virtual element* make_copy()const override {
                form* ptr = new form();
                ptr->copy(*this);
                return ptr;
            }
        };

        class input : public element {
          public:
            input() {
                element::m_type = input_t;
                element::m_has_closing_tag = false;
                element::m_is_container = false;
            }
            input& name(const std::string& _n) { add_attr("name", _n); return *this; }
            input& value(const std::string& _v) { add_attr("value", _v); return *this; }
            input& placeholder(const std::string& _p) { add_attr("placeholder", _p); return *this; }
            input& disabled() { add_attr("disabled", "disabled"); return *this; }
            input& readonly() { add_attr("readonly", "readonly"); return *this; }
            input& required() { add_attr("required", "required"); return *this; }
            input& checked() { add_attr("checked", "checked"); return *this; }
            virtual ~input() { ; }
            virtual element* make_copy()const override {
                input* ptr = new input();
                ptr->copy(*this);
                return ptr;
            }
        };

        class button : public element {
          public:
            button() { element::m_type = button_t; }
            button(const std::string& _text) {
                element::m_type = button_t;
                add(text(_text));
            }
            button& name(const std::string& _n) { add_attr("name", _n); return *this; }
            button& value(const std::string& _v) { add_attr("value", _v); return *this; }
            button& disabled() { add_attr("disabled", "disabled"); return *this; }
            virtual ~button() { ; }
            virtual element* make_copy()const override {
                button* ptr = new button();
                ptr->copy(*this);
                return ptr;
            }
        };

        class select : public element {
          public:
            select() {
                element::m_type = select_t;
                m_newline_after_tag = true;
            }
            select& name(const std::string& _n) { add_attr("name", _n); return *this; }
            select& multiple() { add_attr("multiple", "multiple"); return *this; }
            select& disabled() { add_attr("disabled", "disabled"); return *this; }
            select& required() { add_attr("required", "required"); return *this; }
            virtual ~select() { ; }
            virtual element* make_copy()const override {
                html::select* ptr = new html::select();
                ptr->copy(*this);
                return ptr;
            }
        };

        class option : public element {
          public:
            option() { element::m_type = option_t; }
            option(const std::string& _text) {
                element::m_type = option_t;
                add(text(_text));
            }
            option(const std::string& _value, const std::string& _text) {
                element::m_type = option_t;
                add_attr("value", _value);
                add(text(_text));
            }
            option& selected() { add_attr("selected", "selected"); return *this; }
            option& disabled() { add_attr("disabled", "disabled"); return *this; }
            virtual ~option() { ; }
            virtual element* make_copy()const override {
                option* ptr = new option();
                ptr->copy(*this);
                return ptr;
            }
        };

        class label : public element {
          public:
            label() { element::m_type = label_t; }
            label(const std::string& _text) {
                element::m_type = label_t;
                add(text(_text));
            }
            label& for_id(const std::string& _id) { add_attr("for", _id); return *this; }
            virtual ~label() { ; }
            virtual element* make_copy()const override {
                label* ptr = new label();
                ptr->copy(*this);
                return ptr;
            }
        };

        class fieldset : public element {
          public:
            fieldset() {
                element::m_type = fieldset_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            fieldset& disabled() { add_attr("disabled", "disabled"); return *this; }
            virtual ~fieldset() { ; }
            virtual element* make_copy()const override {
                fieldset* ptr = new fieldset();
                ptr->copy(*this);
                return ptr;
            }
        };

        class legend : public element {
          public:
            legend() { element::m_type = legend_t; }
            legend(const std::string& _text) {
                element::m_type = legend_t;
                add(text(_text));
            }
            virtual ~legend() { ; }
            virtual element* make_copy()const override {
                legend* ptr = new legend();
                ptr->copy(*this);
                return ptr;
            }
        };

        ////////////////////////////////////////////////////////////////////////////////////
        // Semantic HTML5 Elements
        ////////////////////////////////////////////////////////////////////////////////////

        class header : public element {
          public:
            header() {
                element::m_type = header_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            virtual ~header() { ; }
            virtual element* make_copy()const override {
                header* ptr = new header();
                ptr->copy(*this);
                return ptr;
            }
        };

        class footer : public element {
          public:
            footer() {
                element::m_type = footer_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            virtual ~footer() { ; }
            virtual element* make_copy()const override {
                footer* ptr = new footer();
                ptr->copy(*this);
                return ptr;
            }
        };

        class section : public element {
          public:
            section() {
                element::m_type = section_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            virtual ~section() { ; }
            virtual element* make_copy()const override {
                section* ptr = new section();
                ptr->copy(*this);
                return ptr;
            }
        };

        class article : public element {
          public:
            article() {
                element::m_type = article_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            virtual ~article() { ; }
            virtual element* make_copy()const override {
                article* ptr = new article();
                ptr->copy(*this);
                return ptr;
            }
        };

        class aside : public element {
          public:
            aside() {
                element::m_type = aside_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            virtual ~aside() { ; }
            virtual element* make_copy()const override {
                aside* ptr = new aside();
                ptr->copy(*this);
                return ptr;
            }
        };

        class main : public element {
          public:
            main() {
                element::m_type = main_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            virtual ~main() { ; }
            virtual element* make_copy()const override {
                html::main* ptr = new html::main();
                ptr->copy(*this);
                return ptr;
            }
        };

        ////////////////////////////////////////////////////////////////////////////////////
        // Media Elements
        ////////////////////////////////////////////////////////////////////////////////////

        class video : public element {
          public:
            video() {
                element::m_type = video_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            video& controls() { add_attr("controls", "controls"); return *this; }
            video& autoplay() { add_attr("autoplay", "autoplay"); return *this; }
            video& loop() { add_attr("loop", "loop"); return *this; }
            video& muted() { add_attr("muted", "muted"); return *this; }
            video& poster(const std::string& _p) { add_attr("poster", _p); return *this; }
            virtual ~video() { ; }
            virtual element* make_copy()const override {
                video* ptr = new video();
                ptr->copy(*this);
                return ptr;
            }
        };

        class audio : public element {
          public:
            audio() {
                element::m_type = audio_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            audio& controls() { add_attr("controls", "controls"); return *this; }
            audio& autoplay() { add_attr("autoplay", "autoplay"); return *this; }
            audio& loop() { add_attr("loop", "loop"); return *this; }
            audio& muted() { add_attr("muted", "muted"); return *this; }
            virtual ~audio() { ; }
            virtual element* make_copy()const override {
                audio* ptr = new audio();
                ptr->copy(*this);
                return ptr;
            }
        };

        class source : public element {
          public:
            source() {
                element::m_type = source_t;
                element::m_has_closing_tag = false;
                element::m_is_container = false;
            }
            source(const std::string& _src, const std::string& _type) {
                element::m_type = source_t;
                element::m_has_closing_tag = false;
                element::m_is_container = false;
                src(_src);
                type(_type);
            }
            virtual ~source() { ; }
            virtual element* make_copy()const override {
                source* ptr = new source();
                ptr->copy(*this);
                return ptr;
            }
        };

    }//html

}//web


#endif
