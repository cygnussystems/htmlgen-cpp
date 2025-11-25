/*  ===================================================================
*                         HtmlGen++
*            Copyright (c) 2015-2024 Peter Ritter
*                  Licensed under MIT License
*  ====================================================================
*/

#ifndef HTML_SEMANTIC__INCLUDED
#define HTML_SEMANTIC__INCLUDED

#include "html_core.h"

namespace html {

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
            // Variadic constructor for multiple children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            header(Args&&... args) {
                element::m_type = header_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~header() { ; }
            HTML_FLUENT_METHODS(header)
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
            // Variadic constructor for multiple children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            footer(Args&&... args) {
                element::m_type = footer_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~footer() { ; }
            HTML_FLUENT_METHODS(footer)
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
            // Variadic constructor for multiple children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            section(Args&&... args) {
                element::m_type = section_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~section() { ; }
            HTML_FLUENT_METHODS(section)
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
            // Variadic constructor for multiple children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            article(Args&&... args) {
                element::m_type = article_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~article() { ; }
            HTML_FLUENT_METHODS(article)
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
            // Variadic constructor for multiple children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            aside(Args&&... args) {
                element::m_type = aside_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~aside() { ; }
            HTML_FLUENT_METHODS(aside)
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
            // Variadic constructor for multiple children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            main(Args&&... args) {
                element::m_type = main_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~main() { ; }
            HTML_FLUENT_METHODS(main)
            virtual element* make_copy()const override {
                html::main* ptr = new html::main();
                ptr->copy(*this);
                return ptr;
            }
        };

        ////////////////////////////////////////////////////////////////////////////////////
        // Semantic Text Elements
        ////////////////////////////////////////////////////////////////////////////////////

        class figure : public element {
          public:
            figure() {
                element::m_type = figure_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            // Variadic constructor for multiple children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            figure(Args&&... args) {
                element::m_type = figure_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            virtual ~figure() { ; }
            HTML_FLUENT_METHODS(figure)
            virtual element* make_copy()const override {
                figure* ptr = new figure();
                ptr->copy(*this);
                return ptr;
            }
        };

        class figcaption : public element {
          public:
            figcaption() { element::m_type = figcaption_t; }
            figcaption(const std::string& _s) {
                element::m_type = figcaption_t;
                add(text(_s));
            }
            HTML_FLUENT_METHODS(figcaption)
            virtual ~figcaption() { ; }
            virtual element* make_copy()const override {
                figcaption* ptr = new figcaption();
                ptr->copy(*this);
                return ptr;
            }
        };

        class time_ : public element {
          public:
            time_() { element::m_type = time_t; }
            time_(const std::string& _s) {
                element::m_type = time_t;
                add(text(_s));
            }
            HTML_FLUENT_METHODS(time_)
            time_& datetime(const std::string& dt) { add_attr("datetime", dt); return *this; }
            virtual ~time_() { ; }
            virtual element* make_copy()const override {
                time_* ptr = new time_();
                ptr->copy(*this);
                return ptr;
            }
        };

        class mark : public element {
          public:
            mark() { element::m_type = mark_t; }
            mark(const std::string& _s) {
                element::m_type = mark_t;
                add(text(_s));
            }
            virtual ~mark() { ; }
            virtual element* make_copy()const override {
                mark* ptr = new mark();
                ptr->copy(*this);
                return ptr;
            }
        };

        class code : public element {
          public:
            code() { element::m_type = code_t; }
            code(const std::string& _s) {
                element::m_type = code_t;
                add(text(_s));
            }
            virtual ~code() { ; }
            virtual element* make_copy()const override {
                code* ptr = new code();
                ptr->copy(*this);
                return ptr;
            }
        };

        class pre : public element {
          public:
            pre() {
                element::m_type = pre_t;
                m_newline_after_element = true;
            }
            pre(const std::string& _s) {
                element::m_type = pre_t;
                m_newline_after_element = true;
                add(text(_s));
            }
            virtual ~pre() { ; }
            virtual element* make_copy()const override {
                pre* ptr = new pre();
                ptr->copy(*this);
                return ptr;
            }
        };

        class kbd : public element {
          public:
            kbd() { element::m_type = kbd_t; }
            kbd(const std::string& _s) {
                element::m_type = kbd_t;
                add(text(_s));
            }
            virtual ~kbd() { ; }
            virtual element* make_copy()const override {
                kbd* ptr = new kbd();
                ptr->copy(*this);
                return ptr;
            }
        };

        class samp : public element {
          public:
            samp() { element::m_type = samp_t; }
            samp(const std::string& _s) {
                element::m_type = samp_t;
                add(text(_s));
            }
            virtual ~samp() { ; }
            virtual element* make_copy()const override {
                samp* ptr = new samp();
                ptr->copy(*this);
                return ptr;
            }
        };

        class var : public element {
          public:
            var() { element::m_type = var_t; }
            var(const std::string& _s) {
                element::m_type = var_t;
                add(text(_s));
            }
            virtual ~var() { ; }
            virtual element* make_copy()const override {
                var* ptr = new var();
                ptr->copy(*this);
                return ptr;
            }
        };

        class blockquote : public element {
          public:
            blockquote() {
                element::m_type = blockquote_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            blockquote(const std::string& _s) {
                element::m_type = blockquote_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add(text(_s));
            }
            // Variadic constructor for nested children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 1)>>
            blockquote(Args&&... args) {
                element::m_type = blockquote_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            HTML_FLUENT_METHODS(blockquote)
            blockquote& cite(const std::string& url) { add_attr("cite", url); return *this; }
            virtual ~blockquote() { ; }
            virtual element* make_copy()const override {
                blockquote* ptr = new blockquote();
                ptr->copy(*this);
                return ptr;
            }
        };

        class q : public element {
          public:
            q() { element::m_type = q_t; }
            q(const std::string& _s) {
                element::m_type = q_t;
                add(text(_s));
            }
            q& cite(const std::string& url) { add_attr("cite", url); return *this; }
            virtual ~q() { ; }
            virtual element* make_copy()const override {
                q* ptr = new q();
                ptr->copy(*this);
                return ptr;
            }
        };

        class abbr : public element {
          public:
            abbr() { element::m_type = abbr_t; }
            abbr(const std::string& _s) {
                element::m_type = abbr_t;
                add(text(_s));
            }
            virtual ~abbr() { ; }
            virtual element* make_copy()const override {
                abbr* ptr = new abbr();
                ptr->copy(*this);
                return ptr;
            }
        };

        class cite_ : public element {
          public:
            cite_() { element::m_type = cite_t; }
            cite_(const std::string& _s) {
                element::m_type = cite_t;
                add(text(_s));
            }
            virtual ~cite_() { ; }
            virtual element* make_copy()const override {
                cite_* ptr = new cite_();
                ptr->copy(*this);
                return ptr;
            }
        };

        class dfn : public element {
          public:
            dfn() { element::m_type = dfn_t; }
            dfn(const std::string& _s) {
                element::m_type = dfn_t;
                add(text(_s));
            }
            virtual ~dfn() { ; }
            virtual element* make_copy()const override {
                dfn* ptr = new dfn();
                ptr->copy(*this);
                return ptr;
            }
        };

        class address : public element {
          public:
            address() {
                element::m_type = address_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            // Variadic constructor for nested children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            address(Args&&... args) {
                element::m_type = address_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            HTML_FLUENT_METHODS(address)
            virtual ~address() { ; }
            virtual element* make_copy()const override {
                address* ptr = new address();
                ptr->copy(*this);
                return ptr;
            }
        };

        class sub : public element {
          public:
            sub() { element::m_type = sub_t; }
            sub(const std::string& _s) {
                element::m_type = sub_t;
                add(text(_s));
            }
            virtual ~sub() { ; }
            virtual element* make_copy()const override {
                sub* ptr = new sub();
                ptr->copy(*this);
                return ptr;
            }
        };

        class sup : public element {
          public:
            sup() { element::m_type = sup_t; }
            sup(const std::string& _s) {
                element::m_type = sup_t;
                add(text(_s));
            }
            virtual ~sup() { ; }
            virtual element* make_copy()const override {
                sup* ptr = new sup();
                ptr->copy(*this);
                return ptr;
            }
        };

        class ins : public element {
          public:
            ins() { element::m_type = ins_t; }
            ins(const std::string& _s) {
                element::m_type = ins_t;
                add(text(_s));
            }
            ins& cite(const std::string& url) { add_attr("cite", url); return *this; }
            ins& datetime(const std::string& dt) { add_attr("datetime", dt); return *this; }
            virtual ~ins() { ; }
            virtual element* make_copy()const override {
                ins* ptr = new ins();
                ptr->copy(*this);
                return ptr;
            }
        };

        class del : public element {
          public:
            del() { element::m_type = del_t; }
            del(const std::string& _s) {
                element::m_type = del_t;
                add(text(_s));
            }
            del& cite(const std::string& url) { add_attr("cite", url); return *this; }
            del& datetime(const std::string& dt) { add_attr("datetime", dt); return *this; }
            virtual ~del() { ; }
            virtual element* make_copy()const override {
                del* ptr = new del();
                ptr->copy(*this);
                return ptr;
            }
        };

        class s : public element {
          public:
            s() { element::m_type = s_t; }
            s(const std::string& _s) {
                element::m_type = s_t;
                add(text(_s));
            }
            virtual ~s() { ; }
            virtual element* make_copy()const override {
                html::s* ptr = new html::s();
                ptr->copy(*this);
                return ptr;
            }
        };

        class u : public element {
          public:
            u() { element::m_type = u_t; }
            u(const std::string& _s) {
                element::m_type = u_t;
                add(text(_s));
            }
            virtual ~u() { ; }
            virtual element* make_copy()const override {
                u* ptr = new u();
                ptr->copy(*this);
                return ptr;
            }
        };

}//html

#endif
