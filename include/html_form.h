/*  ===================================================================
*                         HtmlGen++
*            Copyright (c) 2015-2024 Peter Ritter
*                  Licensed under MIT License
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
            // Variadic constructor for nested children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            form(Args&&... args) {
                element::m_type = form_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            HTML_FLUENT_METHODS(form)
            form& action(const std::string& _a) { add_attr("action", _a); return *this; }
            form& method(const std::string& _m) { add_attr("method", _m); return *this; }
            form& enctype(const std::string& _e) { add_attr("enctype", _e); return *this; }
            form& target(const std::string& _t) { add_attr("target", _t); return *this; }
            form& novalidate() { add_attr("novalidate", "novalidate"); return *this; }
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
            HTML_FLUENT_METHODS(input)
            input& name(const std::string& _n) { add_attr("name", _n); return *this; }
            input& value(const std::string& _v) { add_attr("value", _v); return *this; }
            input& placeholder(const std::string& _p) { add_attr("placeholder", _p); return *this; }
            input& disabled() { add_attr("disabled", "disabled"); return *this; }
            input& readonly() { add_attr("readonly", "readonly"); return *this; }
            input& required() { add_attr("required", "required"); return *this; }
            input& checked() { add_attr("checked", "checked"); return *this; }
            input& min(const std::string& _m) { add_attr("min", _m); return *this; }
            input& max(const std::string& _m) { add_attr("max", _m); return *this; }
            input& step(const std::string& _s) { add_attr("step", _s); return *this; }
            input& pattern(const std::string& _p) { add_attr("pattern", _p); return *this; }
            input& autocomplete(const std::string& _a) { add_attr("autocomplete", _a); return *this; }
            input& autofocus() { add_attr("autofocus", "autofocus"); return *this; }
            input& list(const std::string& _l) { add_attr("list", _l); return *this; }
            input& minlength(int _m) { add_attr("minlength", std::to_string(_m)); return *this; }
            input& maxlength(int _m) { add_attr("maxlength", std::to_string(_m)); return *this; }
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
            HTML_FLUENT_METHODS(button)
            button& name(const std::string& _n) { add_attr("name", _n); return *this; }
            button& value(const std::string& _v) { add_attr("value", _v); return *this; }
            button& disabled() { add_attr("disabled", "disabled"); return *this; }
            button& formaction(const std::string& _a) { add_attr("formaction", _a); return *this; }
            button& formmethod(const std::string& _m) { add_attr("formmethod", _m); return *this; }
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
            // Variadic constructor for nested options
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            select(Args&&... args) {
                element::m_type = select_t;
                m_newline_after_tag = true;
                add_children(std::forward<Args>(args)...);
            }
            HTML_FLUENT_METHODS(select)
            select& name(const std::string& _n) { add_attr("name", _n); return *this; }
            select& multiple() { add_attr("multiple", "multiple"); return *this; }
            select& disabled() { add_attr("disabled", "disabled"); return *this; }
            select& required() { add_attr("required", "required"); return *this; }
            select& size(int _s) { add_attr("size", std::to_string(_s)); return *this; }
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
            HTML_FLUENT_METHODS(option)
            option& value(const std::string& _v) { add_attr("value", _v); return *this; }
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
            HTML_FLUENT_METHODS(label)
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
            // Variadic constructor for nested children
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            fieldset(Args&&... args) {
                element::m_type = fieldset_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
                add_children(std::forward<Args>(args)...);
            }
            HTML_FLUENT_METHODS(fieldset)
            fieldset& disabled() { add_attr("disabled", "disabled"); return *this; }
            fieldset& name(const std::string& _n) { add_attr("name", _n); return *this; }
            fieldset& form_attr(const std::string& _f) { add_attr("form", _f); return *this; }
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
            HTML_FLUENT_METHODS(legend)
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
            // Variadic constructor for nested options
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            datalist(Args&&... args) {
                element::m_type = datalist_t;
                m_newline_after_tag = true;
                add_children(std::forward<Args>(args)...);
            }
            HTML_FLUENT_METHODS(datalist)
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
            HTML_FLUENT_METHODS(output)
            output& for_id(const std::string& ids) { add_attr("for", ids); return *this; }
            output& name(const std::string& n) { add_attr("name", n); return *this; }
            output& form_attr(const std::string& f) { add_attr("form", f); return *this; }
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
            // Variadic constructor for nested options
            template<typename... Args, typename = std::enable_if_t<(sizeof...(Args) > 0)>>
            optgroup(Args&&... args) {
                element::m_type = optgroup_t;
                m_newline_after_tag = true;
                add_children(std::forward<Args>(args)...);
            }
            HTML_FLUENT_METHODS(optgroup)
            optgroup& label(const std::string& l) { add_attr("label", l); return *this; }
            optgroup& label_attr(const std::string& l) { add_attr("label", l); return *this; }
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
            HTML_FLUENT_METHODS(progress)
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
            HTML_FLUENT_METHODS(meter)
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
