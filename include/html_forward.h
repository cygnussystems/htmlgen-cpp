/*  ===================================================================
*                      HTML Generator Library
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#ifndef HTML_FORWARD__INCLUDED
#define HTML_FORWARD__INCLUDED

#include <vector>
#include <string>
#include <string_view>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <cassert>

namespace html {

        enum element_t {
            undefined_t = 0,
            body_t,
            head_t,
            title_t,
            meta_t,
            element_group_t,

            div_t,

            text_t,
            script_t,
            img_t,
            a_t,
            link_t,
            style_t,
            nav_t,
            span_t,

            h1_t,
            h2_t,
            h3_t,
            h4_t,
            h5_t,
            h6_t,

            p_t,
            small_t,
            em_t,
            strong_t,
            b_t,
            textarea_t,

            br_t,
            hr_t,

            table_t,
            tr_t,
            td_t,
            tbody_t,
            thead_t,
            tfoot_t,
            th_t,
            caption_t,

            ul_t,
            ol_t,
            li_t,

            // Form elements
            form_t,
            input_t,
            button_t,
            select_t,
            option_t,
            label_t,
            fieldset_t,
            legend_t,

            // Semantic HTML5 elements
            header_t,
            footer_t,
            section_t,
            article_t,
            aside_t,
            main_t,

            // Media elements
            video_t,
            audio_t,
            source_t,

            // Table structure
            colgroup_t,
            col_t,

            // Interactive elements
            details_t,
            summary_t,
            dialog_t,
            template_t,

            // Semantic text elements
            figure_t,
            figcaption_t,
            time_t,
            mark_t,
            code_t,
            pre_t,
            kbd_t,
            samp_t,
            var_t,
            blockquote_t,
            q_t,
            abbr_t,
            cite_t,
            dfn_t,
            address_t,
            sub_t,
            sup_t,
            ins_t,
            del_t,
            s_t,
            u_t,

            // Form enhancements
            datalist_t,
            output_t,
            optgroup_t,
            progress_t,
            meter_t,

            // Media & embedded
            picture_t,
            track_t,
            iframe_t,
            canvas_t
        };

        // Forward declarations
        class page;
        class element_group;
        class element;

}//html

#endif
