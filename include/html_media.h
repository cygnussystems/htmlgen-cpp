/*  ===================================================================
*                      HTML Generator Library
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#ifndef HTML_MEDIA__INCLUDED
#define HTML_MEDIA__INCLUDED

#include "html_core.h"

namespace html {

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

        ////////////////////////////////////////////////////////////////////////////////////
        // Additional Media & Embedded Elements
        ////////////////////////////////////////////////////////////////////////////////////

        class picture : public element {
          public:
            picture() {
                element::m_type = picture_t;
                m_newline_after_tag = true;
                m_newline_after_element = true;
            }
            virtual ~picture() { ; }
            virtual element* make_copy()const override {
                picture* ptr = new picture();
                ptr->copy(*this);
                return ptr;
            }
        };

        class track : public element {
          public:
            track() {
                element::m_type = track_t;
                element::m_has_closing_tag = false;
                element::m_is_container = false;
            }
            track& kind(const std::string& k) { add_attr("kind", k); return *this; }
            track& srclang(const std::string& l) { add_attr("srclang", l); return *this; }
            track& label(const std::string& l) { add_attr("label", l); return *this; }
            track& default_() { add_attr("default", "default"); return *this; }
            virtual ~track() { ; }
            virtual element* make_copy()const override {
                track* ptr = new track();
                ptr->copy(*this);
                return ptr;
            }
        };

        class iframe : public element {
          public:
            iframe() {
                element::m_type = iframe_t;
                m_newline_after_element = true;
            }
            iframe& sandbox(const std::string& s) { add_attr("sandbox", s); return *this; }
            iframe& allow(const std::string& a) { add_attr("allow", a); return *this; }
            iframe& loading(const std::string& l) { add_attr("loading", l); return *this; }
            iframe& name(const std::string& n) { add_attr("name", n); return *this; }
            iframe& srcdoc(const std::string& s) { add_attr("srcdoc", s); return *this; }
            virtual ~iframe() { ; }
            virtual element* make_copy()const override {
                iframe* ptr = new iframe();
                ptr->copy(*this);
                return ptr;
            }
        };

        class canvas : public element {
          public:
            canvas() {
                element::m_type = canvas_t;
                m_newline_after_element = true;
            }
            virtual ~canvas() { ; }
            virtual element* make_copy()const override {
                canvas* ptr = new canvas();
                ptr->copy(*this);
                return ptr;
            }
        };

}//html

#endif
