/*  ===================================================================
*                         HtmlGen++
*            Copyright (c) 2015-2024 Peter Ritter
*                  Licensed under MIT License
*  ====================================================================
*/

#ifndef HTML_CORE__INCLUDED
#define HTML_CORE__INCLUDED

#include "html_forward.h"

namespace html {

        // HTML escape utility - escapes <, >, &, ", '
        [[nodiscard]] std::string html_escape(std::string_view input);

        // Raw HTML wrapper - content will not be escaped
        struct raw_html {
            std::string content;
            explicit raw_html(std::string_view s) : content(s) {}
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
            element& operator=(const element&) = delete;
          public:
            element();
            element(const element&);
            element(element&&) noexcept;
            element& operator=(element&&) noexcept;
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

            // Data attributes
            element& data(const std::string& name, const std::string& value);

            // ARIA accessibility attributes
            element& aria_label(const std::string&);
            element& aria_labelledby(const std::string&);
            element& aria_describedby(const std::string&);
            element& aria_hidden(bool = true);
            element& aria_expanded(bool);
            element& aria_controls(const std::string&);
            element& aria_current(const std::string&);
            element& aria_live(const std::string&);

            // Global boolean attributes
            element& hidden(bool = true);
            element& contenteditable(bool = true);
            element& draggable(bool = true);
            element& spellcheck(bool);
            element& tabindex(int);
            element& title(const std::string&);
            element& lang(const std::string&);
            element& dir(const std::string&);

          public:
            element& add_attr(const html::attr&);

          public:
            element& add(const html::attr&);
            virtual element& add(const std::string&);
            virtual element& add(const element&);
            virtual element& add(element&& e);
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
            // Variadic constructor helpers
            template<typename T>
            void add_child_item(T&& item) {
                if constexpr (std::is_convertible_v<std::decay_t<T>, std::string_view>) {
                    add(text(std::string(std::forward<T>(item))));
                } else {
                    add(std::forward<T>(item));
                }
            }

            template<typename... Args>
            void add_children(Args&&... args) {
                (add_child_item(std::forward<Args>(args)), ...);
            }

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

        std::ostream& operator<<(std::ostream&, html::element&);

        //=============================================================================
        // Fluent Method Override Macro
        // Use this in derived classes to enable full method chaining.
        // Example: input().type("email").name("foo").id("bar").required()
        //=============================================================================
        #define HTML_FLUENT_METHODS(DerivedClass) \
            DerivedClass& id(const std::string& s) { element::id(s); return *this; } \
            DerivedClass& cl(const std::string& s) { element::cl(s); return *this; } \
            DerivedClass& add_cl(const std::string& s) { element::add_cl(s); return *this; } \
            DerivedClass& style(const std::string& s) { element::style(s); return *this; } \
            DerivedClass& type(const std::string& s) { element::type(s); return *this; } \
            DerivedClass& data_id(const std::string& s) { element::data_id(s); return *this; } \
            DerivedClass& role(const std::string& s) { element::role(s); return *this; } \
            DerivedClass& hidden(bool b = true) { element::hidden(b); return *this; } \
            DerivedClass& tabindex(int i) { element::tabindex(i); return *this; } \
            DerivedClass& title(const std::string& s) { element::title(s); return *this; } \
            DerivedClass& aria_label(const std::string& s) { element::aria_label(s); return *this; } \
            DerivedClass& data(const std::string& n, const std::string& v) { element::data(n, v); return *this; }

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

          private:
            // Dependency management
            std::set<dependency> m_dependencies;
            std::vector<std::string> m_head_scripts;
            std::vector<std::string> m_body_scripts;
            std::vector<std::string> m_init_scripts;
            std::set<std::string> m_init_script_keys;  // For deduplication
            std::vector<std::string> m_styles;         // Embedded CSS
            dependency_mode m_dependency_mode;

          public:
            page();
            virtual ~page();

          public:
            // Dependency registration methods
            void require(dependency dep);
            void add_head_script(const std::string& js);
            void add_body_script(const std::string& js);
            void add_on_ready(const std::string& js, const std::string& key = "");
            void add_style(const std::string& css);

            // Dependency mode
            void set_dependency_mode(dependency_mode mode);
            dependency_mode get_dependency_mode() const;

            // Check if dependency is registered
            bool has_dependency(dependency dep) const;

          public:
            virtual element* make_copy()const override;
            virtual void write_html(std::ostream&) override;

          private:
            void write_dependency_css(std::ostream& _s);
            void write_dependency_js(std::ostream& _s);
            void write_init_scripts(std::ostream& _s);
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
            element_group();
            element_group(element_group&& _g) noexcept;
            element_group(const element_group& _g);
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

}//html

#endif
