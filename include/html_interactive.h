/*  ===================================================================
*                         HtmlGen++
*            Copyright (c) 2015-2024 Peter Ritter
*                  Licensed under MIT License
*  ====================================================================
*/

#ifndef HTML_INTERACTIVE__INCLUDED
#define HTML_INTERACTIVE__INCLUDED

#include "html_core.h"

namespace html {

        ////////////////////////////////////////////////////////////////////////////////////
        // Interactive Elements
        ////////////////////////////////////////////////////////////////////////////////////

        class details : public element {
          public:
            details() {
                element::m_type = details_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            // Variadic constructor for nested children (summary + content)
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            details(Args&&... args) {
                element::m_type = details_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            HTML_FLUENT_METHODS(details)
            details& open() { add_attr("open", "open"); return *this; }
            virtual ~details() { ; }
            virtual element* make_copy()const override {
                details* ptr = new details();
                ptr->copy(*this);
                return ptr;
            }
        };

        class summary : public element {
          public:
            summary() { element::m_type = summary_t; }
            summary(const std::string& _s) {
                element::m_type = summary_t;
                add(text(_s));
            }
            HTML_FLUENT_METHODS(summary)
            virtual ~summary() { ; }
            virtual element* make_copy()const override {
                summary* ptr = new summary();
                ptr->copy(*this);
                return ptr;
            }
        };

        class dialog : public element {
          public:
            dialog() {
                element::m_type = dialog_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            // Variadic constructor for nested children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            dialog(Args&&... args) {
                element::m_type = dialog_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            HTML_FLUENT_METHODS(dialog)
            dialog& open() { add_attr("open", "open"); return *this; }
            virtual ~dialog() { ; }
            virtual element* make_copy()const override {
                dialog* ptr = new dialog();
                ptr->copy(*this);
                return ptr;
            }
        };

        class template_ : public element {
          public:
            template_() {
                element::m_type = template_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            HTML_FLUENT_METHODS(template_)
            virtual ~template_() { ; }
            virtual element* make_copy()const override {
                template_* ptr = new template_();
                ptr->copy(*this);
                return ptr;
            }
        };

}//html

#endif
