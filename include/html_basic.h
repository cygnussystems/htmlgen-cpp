/*  ===================================================================
*                         HtmlGen++
*            Copyright (c) 2015-2024 Peter Ritter
*                  Licensed under MIT License
*  ====================================================================
*/

#ifndef HTML_BASIC__INCLUDED
#define HTML_BASIC__INCLUDED

#include "html_core.h"

namespace html {

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
            // Variadic constructor for multiple children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 1)>>
            div(Args&&... args) {
                element::m_type = div_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~div() { ; }
            HTML_FLUENT_METHODS(div)
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
            // Variadic constructor for multiple children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 1)>>
            nav(Args&&... args) {
                m_newline_after_tag = true;
                m_newline_after_element = true;
                element::m_type = nav_t;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~nav() { ; }
            HTML_FLUENT_METHODS(nav)
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
            HTML_FLUENT_METHODS(h1)
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
            HTML_FLUENT_METHODS(h2)
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
            HTML_FLUENT_METHODS(h3)
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
            HTML_FLUENT_METHODS(h4)
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
            HTML_FLUENT_METHODS(h5)
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
            HTML_FLUENT_METHODS(h6)
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
            // Variadic constructor for multiple children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 1)>>
            p(Args&&... args) {
                element::m_type = p_t;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~p() { ; }
            HTML_FLUENT_METHODS(p)
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
            HTML_FLUENT_METHODS(em)
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
            HTML_FLUENT_METHODS(strong)
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
            HTML_FLUENT_METHODS(b)
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
            HTML_FLUENT_METHODS(small_)
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
            HTML_FLUENT_METHODS(span)
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
            // Variadic constructor for multiple children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            ul(Args&&... args) {
                element::m_type = ul_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }

            virtual ~ul() { ; }
            HTML_FLUENT_METHODS(ul)
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
            // Variadic constructor for multiple children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            ol(Args&&... args) {
                element::m_type = ol_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }

            virtual ~ol() { ; }
            HTML_FLUENT_METHODS(ol)
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
            // Variadic constructor for multiple children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 1)>>
            li(Args&&... args) {
                element::m_type = li_t;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~li() { ; }
            HTML_FLUENT_METHODS(li)
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
            HTML_FLUENT_METHODS(textarea)
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

}//html

#endif
