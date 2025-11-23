/*  ===================================================================
*                      HTML Generator Library
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#ifndef HTML_FORM__INCLUDED
#define HTML_FORM__INCLUDED

#include "html_core.h"

namespace html {

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
        // Form Enhancement Elements
        ////////////////////////////////////////////////////////////////////////////////////

        class datalist : public element {
          public:
            datalist() {
                element::m_type = datalist_t;
                m_newline_after_tag = true;
            }
            virtual ~datalist() { ; }
            virtual element* make_copy()const override {
                datalist* ptr = new datalist();
                ptr->copy(*this);
                return ptr;
            }
        };

        class output : public element {
          public:
            output() { element::m_type = output_t; }
            output& for_id(const std::string& ids) { add_attr("for", ids); return *this; }
            output& name(const std::string& n) { add_attr("name", n); return *this; }
            output& form(const std::string& f) { add_attr("form", f); return *this; }
            virtual ~output() { ; }
            virtual element* make_copy()const override {
                output* ptr = new output();
                ptr->copy(*this);
                return ptr;
            }
        };

        class optgroup : public element {
          public:
            optgroup() {
                element::m_type = optgroup_t;
                m_newline_after_tag = true;
            }
            optgroup& label(const std::string& l) { add_attr("label", l); return *this; }
            optgroup& disabled() { add_attr("disabled", "disabled"); return *this; }
            virtual ~optgroup() { ; }
            virtual element* make_copy()const override {
                optgroup* ptr = new optgroup();
                ptr->copy(*this);
                return ptr;
            }
        };

        class progress : public element {
          public:
            progress() { element::m_type = progress_t; }
            progress& value(double v) { add_attr("value", std::to_string(v)); return *this; }
            progress& max(double m) { add_attr("max", std::to_string(m)); return *this; }
            virtual ~progress() { ; }
            virtual element* make_copy()const override {
                progress* ptr = new progress();
                ptr->copy(*this);
                return ptr;
            }
        };

        class meter : public element {
          public:
            meter() { element::m_type = meter_t; }
            meter& value(double v) { add_attr("value", std::to_string(v)); return *this; }
            meter& min(double m) { add_attr("min", std::to_string(m)); return *this; }
            meter& max(double m) { add_attr("max", std::to_string(m)); return *this; }
            meter& low(double l) { add_attr("low", std::to_string(l)); return *this; }
            meter& high(double h) { add_attr("high", std::to_string(h)); return *this; }
            meter& optimum(double o) { add_attr("optimum", std::to_string(o)); return *this; }
            virtual ~meter() { ; }
            virtual element* make_copy()const override {
                meter* ptr = new meter();
                ptr->copy(*this);
                return ptr;
            }
        };

}//html

#endif
