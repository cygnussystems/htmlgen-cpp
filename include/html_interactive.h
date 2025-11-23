/*  ===================================================================
*                      HTML Generator Library
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
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
            virtual ~template_() { ; }
            virtual element* make_copy()const override {
                template_* ptr = new template_();
                ptr->copy(*this);
                return ptr;
            }
        };

}//html

#endif
