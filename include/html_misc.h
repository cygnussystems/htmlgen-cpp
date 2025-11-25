/*  ===================================================================
*                         HtmlGen++
*            Copyright (c) 2015-2024 Peter Ritter
*                  Licensed under MIT License
*  ====================================================================
*/

#ifndef HTML_MISC__INCLUDED
#define HTML_MISC__INCLUDED

#include "html_core.h"

namespace html {

        ////////////////////////////////////////////////////////////////////////////////////

        class script : public element {
          public:
            script() {
                element::m_type = script_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            script(const html::attr& _a) {
                element::m_type = script_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add(_a);
            }

            script(const html::attr& _a, const html::attr& _b) {
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
            HTML_FLUENT_METHODS(img)
            img& loading(const std::string& l) { add_attr("loading", l); return *this; }
            img& decoding(const std::string& d) { add_attr("decoding", d); return *this; }
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
            HTML_FLUENT_METHODS(anchor)
            anchor& target(const std::string& t) { add_attr("target", t); return *this; }
            anchor& download(const std::string& d = "") {
                if (d.empty()) add_attr("download", "download");
                else add_attr("download", d);
                return *this;
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

}//html

#endif
