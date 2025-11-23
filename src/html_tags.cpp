/*  ===================================================================
*                      HTML Generator Library
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#include "../include/html_tags.h"

namespace web {

    namespace html {

        /////////////////////////////////////////////////////////////
        // HTML escape utility implementation
        std::string html_escape(std::string_view input) {
            std::string result;
            result.reserve(input.size() * 1.1); // Pre-allocate slightly larger
            for (char c : input) {
                switch (c) {
                    case '&':  result += "&amp;";  break;
                    case '<':  result += "&lt;";   break;
                    case '>':  result += "&gt;";   break;
                    case '"':  result += "&quot;"; break;
                    case '\'': result += "&#39;";  break;
                    default:   result += c;        break;
                }
            }
            return result;
        }

        /////////////////////////////////////////////////////////////
        std::vector<std::string> init_static_tag_names() {
            std::vector<std::string> v;
            v.resize(120); // Increased for new elements
            v[body_t] = "body";
            v[head_t] = "head";
            v[title_t] = "title";
            v[meta_t] = "meta";
            v[div_t] = "div";
            v[nav_t] = "nav";
            v[span_t] = "span";
            v[element_group_t] = ""; //no tag
            v[a_t] = "a";
            v[link_t] = "link";
            v[p_t] = "p";
            v[text_t] = ""; //no tag
            v[script_t] = "script";
            v[img_t] = "img";
            v[style_t] = "style";
            v[h1_t] = "h1";
            v[h2_t] = "h2";
            v[h3_t] = "h3";
            v[h4_t] = "h4";
            v[h5_t] = "h5";
            v[h6_t] = "h6";
            v[table_t] = "table";
            v[td_t] = "td";
            v[tr_t] = "tr";
            v[thead_t] = "thead";
            v[tfoot_t] = "tfoot";
            v[tbody_t] = "tbody";
            v[th_t] = "th";
            v[caption_t] = "caption";
            v[br_t] = "br";
            v[hr_t] = "hr";
            v[em_t] = "em";
            v[strong_t] = "strong";
            v[small_t] = "small";
            v[b_t] = "b";
            v[ol_t] = "ol";
            v[ul_t] = "ul";
            v[li_t] = "li";
            v[textarea_t] = "textarea";
            // Form elements
            v[form_t] = "form";
            v[input_t] = "input";
            v[button_t] = "button";
            v[select_t] = "select";
            v[option_t] = "option";
            v[label_t] = "label";
            v[fieldset_t] = "fieldset";
            v[legend_t] = "legend";
            // Semantic HTML5 elements
            v[header_t] = "header";
            v[footer_t] = "footer";
            v[section_t] = "section";
            v[article_t] = "article";
            v[aside_t] = "aside";
            v[main_t] = "main";
            // Media elements
            v[video_t] = "video";
            v[audio_t] = "audio";
            v[source_t] = "source";
            // Table structure
            v[colgroup_t] = "colgroup";
            v[col_t] = "col";
            // Interactive elements
            v[details_t] = "details";
            v[summary_t] = "summary";
            v[dialog_t] = "dialog";
            v[template_t] = "template";
            // Semantic text elements
            v[figure_t] = "figure";
            v[figcaption_t] = "figcaption";
            v[time_t] = "time";
            v[mark_t] = "mark";
            v[code_t] = "code";
            v[pre_t] = "pre";
            v[kbd_t] = "kbd";
            v[samp_t] = "samp";
            v[var_t] = "var";
            v[blockquote_t] = "blockquote";
            v[q_t] = "q";
            v[abbr_t] = "abbr";
            v[cite_t] = "cite";
            v[dfn_t] = "dfn";
            v[address_t] = "address";
            v[sub_t] = "sub";
            v[sup_t] = "sup";
            v[ins_t] = "ins";
            v[del_t] = "del";
            v[s_t] = "s";
            v[u_t] = "u";
            // Form enhancements
            v[datalist_t] = "datalist";
            v[output_t] = "output";
            v[optgroup_t] = "optgroup";
            v[progress_t] = "progress";
            v[meter_t] = "meter";
            // Media & embedded
            v[picture_t] = "picture";
            v[track_t] = "track";
            v[iframe_t] = "iframe";
            v[canvas_t] = "canvas";
            return v;
        }

        std::vector<std::string> element::s_static_tag_names = init_static_tag_names();

        element::element()
            :
            m_page_ptr(nullptr),
            m_parent_ptr(nullptr),
            m_is_container(true),
            m_has_closing_tag(true),
            m_type(undefined_t),
            m_is_head_element(false),
            m_newline_after_tag(false),
            m_newline_after_element(false) {
            ;
        }

        element::~element() { m_elements.clear(); }

        element::element(const element& _e)
            :
            m_page_ptr(nullptr),
            m_parent_ptr(nullptr),
            m_is_container(true),
            m_has_closing_tag(true),
            m_type(undefined_t),
            m_is_head_element(false),
            m_newline_after_tag(false),
            m_newline_after_element(false) {
            this->copy(_e);
        }

        element::element(element&& _e) noexcept
            :
            m_page_ptr(_e.m_page_ptr),
            m_parent_ptr(_e.m_parent_ptr),
            m_type(_e.m_type),
            m_is_container(_e.m_is_container),
            m_has_closing_tag(_e.m_has_closing_tag),
            m_is_head_element(_e.m_is_head_element),
            m_newline_after_tag(_e.m_newline_after_tag),
            m_newline_after_element(_e.m_newline_after_element),
            m_class_attr(std::move(_e.m_class_attr)),
            m_id_attr(std::move(_e.m_id_attr)),
            m_data_id_attr(std::move(_e.m_data_id_attr)),
            m_type_attr(std::move(_e.m_type_attr)),
            m_role_attr(std::move(_e.m_role_attr)),
            m_style_attr(std::move(_e.m_style_attr)),
            m_src_attr(std::move(_e.m_src_attr)),
            m_alt_attr(std::move(_e.m_alt_attr)),
            m_width_attr(std::move(_e.m_width_attr)),
            m_height_attr(std::move(_e.m_height_attr)),
            m_href_attr(std::move(_e.m_href_attr)),
            m_rel_attr(std::move(_e.m_rel_attr)),
            m_other_attr(std::move(_e.m_other_attr)),
            m_elements(std::move(_e.m_elements)) {
            // Reset moved-from object
            _e.m_page_ptr = nullptr;
            _e.m_parent_ptr = nullptr;
            _e.m_type = undefined_t;
        }

        element& element::operator=(element&& _e) noexcept {
            if (this != &_e) {
                m_page_ptr = _e.m_page_ptr;
                m_parent_ptr = _e.m_parent_ptr;
                m_type = _e.m_type;
                m_is_container = _e.m_is_container;
                m_has_closing_tag = _e.m_has_closing_tag;
                m_is_head_element = _e.m_is_head_element;
                m_newline_after_tag = _e.m_newline_after_tag;
                m_newline_after_element = _e.m_newline_after_element;
                m_class_attr = std::move(_e.m_class_attr);
                m_id_attr = std::move(_e.m_id_attr);
                m_data_id_attr = std::move(_e.m_data_id_attr);
                m_type_attr = std::move(_e.m_type_attr);
                m_role_attr = std::move(_e.m_role_attr);
                m_style_attr = std::move(_e.m_style_attr);
                m_src_attr = std::move(_e.m_src_attr);
                m_alt_attr = std::move(_e.m_alt_attr);
                m_width_attr = std::move(_e.m_width_attr);
                m_height_attr = std::move(_e.m_height_attr);
                m_href_attr = std::move(_e.m_href_attr);
                m_rel_attr = std::move(_e.m_rel_attr);
                m_other_attr = std::move(_e.m_other_attr);
                m_elements = std::move(_e.m_elements);
                // Reset moved-from object
                _e.m_page_ptr = nullptr;
                _e.m_parent_ptr = nullptr;
                _e.m_type = undefined_t;
            }
            return *this;
        }

        void element::copy(const element& _other) {
            m_type = _other.m_type;
            m_class_attr = _other.m_class_attr;
            m_id_attr = _other.m_id_attr;
            m_data_id_attr = _other.m_data_id_attr;
            m_style_attr = _other.m_style_attr;
            m_src_attr = _other.m_src_attr;
            m_alt_attr = _other.m_alt_attr;
            m_type_attr = _other.m_type_attr;
            m_role_attr = _other.m_role_attr;
            m_other_attr = _other.m_other_attr;
            m_width_attr = _other.m_width_attr;
            m_height_attr = _other.m_height_attr;
            m_href_attr = _other.m_href_attr;
            m_rel_attr = _other.m_rel_attr;
            m_is_container = _other.m_is_container;
            m_has_closing_tag = _other.m_has_closing_tag;
            m_is_head_element = _other.m_is_head_element;
            m_newline_after_tag = _other.m_newline_after_tag;
            m_newline_after_element = _other.m_newline_after_element;
            m_elements.clear();
            for(auto& e : _other.m_elements) {
                m_elements.push_back(
                    std::unique_ptr<element>(e->make_copy()));
            }
        }

        const std::string& element::tag()const {
            assert(m_type != 0);
            assert(s_static_tag_names.size() > (size_t)m_type);
            return s_static_tag_names[m_type];
        }


        element& element::id(const std::string& _a) { m_id_attr = _a; return *this; }
        const std::string& element::id()const { return m_id_attr; }

        element& element::data_id(const std::string& _a) { m_data_id_attr = _a; return *this; }
        const std::string& element::data_id()const { return m_data_id_attr; }

        element& element::cl(const std::string& _a) { m_class_attr = _a; return *this; }
        element& element::add_cl(const std::string& _c) { m_class_attr += (" " + _c); return *this; }
        const std::string& element::cl()const { return m_class_attr; }

        element& element::type(const std::string& _a) { m_type_attr = _a; return *this; }
        const std::string& element::type()const { return m_type_attr; }

        element& element::role(const std::string& _a) { m_role_attr = _a; return *this; }
        const std::string& element::role()const { return m_role_attr; }

        element& element::rel(const std::string& _a) { m_rel_attr = _a; return *this; }
        const std::string& element::rel()const { return m_rel_attr; }

        element& element::src(const std::string& _a) { m_src_attr = _a; return *this; }
        const std::string& element::src()const { return m_src_attr; }

        element& element::height(const std::string& _a) { m_height_attr = _a; return *this; }
        const std::string& element::height()const { return m_height_attr; }

        element& element::width(const std::string& _a) { m_width_attr = _a; return *this; }
        const std::string& element::width()const { return m_width_attr; }

        element& element::alt(const std::string& _a) { m_alt_attr = _a; return *this; }
        const std::string& element::alt()const { return m_alt_attr; }

        element& element::style(const std::string& _a) { m_style_attr = _a; return *this; }
        const std::string& element::style()const { return m_style_attr; }

        element& element::href(const std::string& _a) { m_href_attr = _a; return *this; }
        const std::string& element::href()const { return m_href_attr; }

        // Data attributes
        element& element::data(const std::string& name, const std::string& value) {
            add_attr("data-" + name, value);
            return *this;
        }

        // ARIA accessibility attributes
        element& element::aria_label(const std::string& s) { add_attr("aria-label", s); return *this; }
        element& element::aria_labelledby(const std::string& s) { add_attr("aria-labelledby", s); return *this; }
        element& element::aria_describedby(const std::string& s) { add_attr("aria-describedby", s); return *this; }
        element& element::aria_hidden(bool b) { add_attr("aria-hidden", b ? "true" : "false"); return *this; }
        element& element::aria_expanded(bool b) { add_attr("aria-expanded", b ? "true" : "false"); return *this; }
        element& element::aria_controls(const std::string& s) { add_attr("aria-controls", s); return *this; }
        element& element::aria_current(const std::string& s) { add_attr("aria-current", s); return *this; }
        element& element::aria_live(const std::string& s) { add_attr("aria-live", s); return *this; }

        // Global boolean attributes
        element& element::hidden(bool b) { if (b) add_attr("hidden", "hidden"); return *this; }
        element& element::contenteditable(bool b) { add_attr("contenteditable", b ? "true" : "false"); return *this; }
        element& element::draggable(bool b) { add_attr("draggable", b ? "true" : "false"); return *this; }
        element& element::spellcheck(bool b) { add_attr("spellcheck", b ? "true" : "false"); return *this; }
        element& element::tabindex(int n) { add_attr("tabindex", std::to_string(n)); return *this; }
        element& element::title(const std::string& s) { add_attr("title", s); return *this; }
        element& element::lang(const std::string& s) { add_attr("lang", s); return *this; }
        element& element::dir(const std::string& s) { add_attr("dir", s); return *this; }

        element& element::add_attr(const html::attr& _atr) {
            return add(_atr);
        }

        element& element::add(const html::attr& _atr) {
            if(_atr.name == "class") {
                cl(_atr.value);
            } else if(_atr.name == "id") {
                id(_atr.value);
            } else if(_atr.name == "data-id") {
                data_id(_atr.value);
            } else if(_atr.name == "type") {
                type(_atr.value);
            } else if(_atr.name == "role") {
                role(_atr.value);
            } else if(_atr.name == "style") {
                style(_atr.value);
            } else if(_atr.name == "src") {
                src(_atr.value);
            } else if(_atr.name == "alt") {
                alt(_atr.value);
            } else if(_atr.name == "width") {
                width(_atr.value);
            } else if(_atr.name == "height") {
                height(_atr.value);
            } else if(_atr.name == "href") {
                href(_atr.value);
            } else if(_atr.name == "rel") {
                rel(_atr.value);
            } else {
                add_attr(_atr.name, _atr.value);
            }
            return *this;
        }

        bool element::empty()const {
            return m_elements.empty();
        }

        void element::clear() { m_elements.clear(); }

        void element::clear_all() {
            m_class_attr.clear();
            m_id_attr.clear();
            m_data_id_attr.clear();
            m_type_attr.clear();
            m_style_attr.clear();
            m_src_attr.clear();
            m_alt_attr.clear();
            m_width_attr.clear();
            m_height_attr.clear();
            m_other_attr.clear();
            m_href_attr.clear();
            m_rel_attr.clear();
            m_role_attr.clear();
            m_elements.clear();
        }

        size_t element::size()const { return m_elements.size(); }


        element& element::get_child(const std::string& _id) {
            element* ele_ptr = find_child(_id);
            if(!ele_ptr) {
                throw std::runtime_error("no child element with given id exists: " + _id);
            }
            return *ele_ptr;
        }

        element& element::get(const std::string& _id) {
            element* ele_ptr = find(_id);
            if(!ele_ptr) {
                throw std::runtime_error("no child element with given id exists: " + _id);
            }
            return *ele_ptr;
        }

        bool element::exists(const std::string& _id) {
            return find(_id) != nullptr;
        }

        element& element::at(size_t _sz) {
            return *m_elements[_sz];
        }

        element* element::find(const std::string& _id) {
            for(auto& e : m_elements) {
                if(e->id() == _id) {
                    return e.get();
                }
                //search recursively
                if(!e->empty()) {
                    element* ele_ptr = e->find(_id);
                    if(ele_ptr) {
                        assert(ele_ptr->id() == _id);
                        return ele_ptr;
                    }
                }
            }
            return nullptr;
        }

        element* element::find_child(const std::string& _id) {
            for(auto& e : m_elements) {
                if(e->id() == _id) {
                    return e.get();
                }
            }
            return nullptr;
        }

        element& element::operator<<(const std::string& _s) {
            add(text(_s));
            return *this;
        }

        element& element::operator<<(const element& _e) {
            add(_e);
            return *this;
        }

        element& element::operator<<(element_group& _e) {
            add(_e);
            return *this;
        }

        //////////////////////////////////////////////////////////////

        element& element::operator<<=(const std::string& _s) {
            clear();
            add(text(_s));
            return *this;
        }

        element& element::operator<<=(const element& _e) {
            clear();
            add(_e);
            return *this;
        }

        element& element::operator<<=(element_group& _e) {
            clear();
            add(_e);
            return *this;
        }

        //////////////////////////////////////////////////////////////

        element& element::operator<<(html::attr& _a) {
            add(_a);
            return *this;
        }

        element& element::add(const std::string& _s) {
            return add(html::text(_s));
        }

        html::element& element::add(const html::element& _e) {
            if(!m_is_container) {
                throw std::runtime_error("cannot add element - this element is not a container!");
            }
            element* ele_ptr = _e.make_copy();
            ele_ptr->m_parent_ptr = this;
            m_elements.push_back(std::unique_ptr<element>(ele_ptr));
            return *ele_ptr;
        }

        html::element& element::add(html::element&& _e) {
            if(!m_is_container) {
                throw std::runtime_error("cannot add element - this element is not a container!");
            }
            // Create a copy via make_copy which handles polymorphic types correctly
            // then move from the original to preserve any data
            element* ele_ptr = _e.make_copy();
            ele_ptr->m_parent_ptr = this;
            m_elements.push_back(std::unique_ptr<element>(ele_ptr));
            return *ele_ptr;
        }

        html::element& element::add(html::element_group& _e) {
            if(!m_is_container) {
                throw std::runtime_error("cannot add element - this element is not a container!");
            }
            assert(_e.m_type == element_group_t);
            if(_e.empty()) {
                throw std::runtime_error("cannot add empty element_group");
            }
            for(size_t c = 0; c < _e.m_elements.size(); c++) {
                m_elements.push_back(std::move(_e.m_elements[c]));
            }
            _e.m_elements.clear();
            return *m_elements.back();
        }

        ///////////////////////////////////////////////////////////////////////////////////

        element& element::operator[](const std::string& _id) {
            return get(_id);
        }

        element& element::operator[](size_t _idx) {
            if(_idx >= m_elements.size()) {
                throw std::runtime_error(std::string("bounds error at pos: ") + std::to_string(_idx));
            }
            return *m_elements[_idx];
        }

        //////////////////////////////////////////////////////////////////////////////////

        element& element::content(const std::string& _s) {
            m_elements.clear();
            add(text(_s));
            return *this;
        }



        html::element& element::content(html::element& _e) {
            m_elements.clear();
            element* ele_ptr = _e.make_copy();
            m_elements.push_back(std::unique_ptr<element>(ele_ptr));
            return *ele_ptr;
        }

        std::string element::html_content_string() {
            if(m_type == text_t) {
                assert(m_elements.empty());
                std::string s = html_string();
                return s;
            }
            std::ostringstream ss;
            for(auto& ele_ptr : m_elements) {
                ele_ptr->write_html(ss);
            }
            std::string s = ss.str();
            return s;
        }

        void element::write_elements(std::ostream& _s) {
            for(size_t c = 0; c < m_elements.size(); c++) {
                m_elements[c]->page(page());
                m_elements[c]->write_html(_s);
            }
        }

        void element::write_open_tag(std::ostream& _s)const {
            _s << "<" << tag();
            element::write_attributes(_s);
            _s << ">";
            if(m_newline_after_tag) {
                _s << std::endl;
            }
        }
        void element::write_close_tag(std::ostream& _s)const {
            if(m_has_closing_tag) {
                _s << "</" << tag() << ">";
            }
            if(m_newline_after_element) {
                _s << std::endl;
            }
        }

        void element::write_html(std::ostream& _s) {
            write_open_tag(_s);
            write_elements(_s);
            write_close_tag(_s);
        }


        std::string element::html() {
            std::string s;
            {
                std::ostringstream ss;
                write_html(ss);
                s = ss.str();
            }
            return s;
        }


        std::string element::html_string() {
            return html();
        }


        void element::write_attributes(std::ostream& _s)const {
            if(!m_id_attr.empty()) {
                _s << " ";
                _s << "id=\"" << m_id_attr << "\"";
            }
            if(!m_data_id_attr.empty()) {
                _s << " ";
                _s << "data-id=\"" << m_data_id_attr << "\"";
            }
            if(!m_class_attr.empty()) {
                _s << " ";
                _s << "class=\"" << m_class_attr << "\"";
            }
            if(!m_type_attr.empty()) {
                _s << " ";
                _s << "type=\"" << m_type_attr << "\"";
            }
            if(!m_role_attr.empty()) {
                _s << " ";
                _s << "role=\"" << m_role_attr << "\"";
            }
            if(!m_style_attr.empty()) {
                _s << " ";
                _s << "style=\"" << m_style_attr << "\"";
            }
            if(!m_src_attr.empty()) {
                _s << " ";
                _s << "src=\"" << m_src_attr << "\"";
            }
            if(!m_alt_attr.empty()) {
                _s << " ";
                _s << "alt=\"" << m_alt_attr << "\"";
            }
            if(!m_width_attr.empty()) {
                _s << " ";
                _s << "width=\"" << m_width_attr << "\"";
            }
            if(!m_height_attr.empty()) {
                _s << " ";
                _s << "height=\"" << m_height_attr << "\"";
            }
            if(!m_href_attr.empty()) {
                _s << " ";
                _s << "href=\"" << m_href_attr << "\"";
            }
            if(!m_rel_attr.empty()) {
                _s << " ";
                _s << "rel=\"" << m_rel_attr << "\"";
            }
            if(!m_other_attr.empty()) {
                _s << " ";
                _s << m_other_attr;
            }
        }

        //////////////////////////////////////////////////////////////////////////////

        std::string nbsp(size_t repeat) {
            std::string s;
            for(size_t c = 0; c < repeat; c++) {
                s += "&nbsp;";
            }
            return s;
        }


        //////////////////////////////////////////////////////////////////////////////

        element* element::make_copy()const {
            element* ele_ptr = new element();
            ele_ptr->copy(*this);
            return ele_ptr;
        }


        void element::add_attr(const std::string& _name, const std::string& _value) {
            m_other_attr += " " + _name + "=\"" + _value + "\"";
        }

        const std::string& element::attr()const {
            return m_other_attr;
        }

        ///////////////////////////////////////////////////////////////////////

        std::ostream& operator<<(std::ostream& _s, web::html::element& _e) {
            _e.write_html(_s);
            return _s;
        }

        //////////////////////////////////////////////////////////////////////

        page::page() {
            preamble = "<!DOCTYPE html>";
            m_bWriteNewlineAfterTag = true;
        }

        page::~page() {
            m_bWriteNewlineAfterTag = true;
        }

        element* page::make_copy()const {
            assert(false);
            return (element*)nullptr;
        }

        void page::write_html(std::ostream& _s) {
            _s << preamble << std::endl;
            _s << "<html>" << std::endl;
            head.page(this);
            head.write_html(_s);
            _s << "<body>" << std::endl;
            for(size_t c = 0; c < m_elements.size(); c++) {
                m_elements[c]->page(this);
                m_elements[c]->write_html(_s);
                _s << std::endl;
            }
            _s << "</body>" << std::endl;
            _s << "</html>" << std::endl;
        }

        std::ostream& operator<<(std::ostream& _s, page& _p) {
            _p.write_html(_s);
            return _s;
        }

        //////////////////////////////////////////////////////////

        element_group operator+(element& _a, element& _b) {
            element_group g;
            g.add(_a);
            g.add(_b);
            return g;
        }

        element_group operator+(element_group& _a, element& _b) {
            _a.add(_b);
            return std::move(_a);
        }

        element_group operator+(element_group& _a, element_group& _b) {
            // Move elements from _b into _a
            for(auto& e : _b.m_elements) {
                _a.m_elements.push_back(std::move(e));
            }
            _b.m_elements.clear();
            return std::move(_a);
        }

        // C++20 rvalue overloads - implementations
        element_group operator+(element&& lhs, element&& rhs) {
            return operator+(lhs, rhs);
        }

        element_group operator+(element& lhs, element&& rhs) {
            return operator+(lhs, rhs);
        }

        element_group operator+(element&& lhs, element& rhs) {
            return operator+(lhs, rhs);
        }

        //////////////////////////////////////////////////////////

        element_group::element_group() {
            element::m_type = element_group_t;
        }

        element_group::element_group(element_group&& _g) noexcept
            : element(std::move(_g)) {
            element::m_type = element_group_t;
            // Elements already moved via base class move constructor
        }

        element_group::element_group(const element_group& _g)
            : element(_g) {
            element::m_type = element_group_t;
            // Elements already copied via base class copy constructor
        }

        element* element_group::make_copy() const {
            // Properly copy the element_group
            element_group* ele_ptr = new element_group(*this);
            return ele_ptr;
        }

    }
}
