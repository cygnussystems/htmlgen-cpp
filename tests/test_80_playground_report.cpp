/*  ===================================================================
*                      HTML Generator Library - Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#include <catch2/catch_all.hpp>
#include <fstream>
#include <filesystem>
#include "../include/html_gen.h"

using namespace html;

namespace {

// Helper to get output directory
std::filesystem::path get_output_dir() {
    return std::filesystem::path(__FILE__).parent_path() / "output";
}

// Helper to save page to file
void save_page(const std::string& filename, page& pg) {
    auto output_dir = get_output_dir();
    std::filesystem::create_directories(output_dir);
    std::ofstream file(output_dir / filename);
    file << pg.html();
}

//=============================================================================
// TILE HELPER FUNCTIONS
//=============================================================================

// Blue bordered tile with title and value
element tile_blue_large(const std::string& title_text, const std::string& value_id) {
    span tile;
    tile.cl("tile-blue-large");
    tile << span(title_text).cl("title");
    tile << br();
    tile << span().cl("value").id(value_id);
    return tile;
}

// Cameleon (red/green) tile with title and value
element tile_cameleon_large(const std::string& title_text, const std::string& value_id, bool show_sign = false) {
    span tile;
    tile.cl("tile-cameleon-large");
    tile << span(title_text).cl("title");
    tile << br();
    auto value_span = span().cl(show_sign ? "value-with-sign" : "value").id(value_id);
    if (show_sign) {
        value_span.add_attr("data-show-sign", "");
    }
    tile << value_span;
    if (show_sign) {
        tile << text("%");
    }
    return tile;
}

// Quality metric tile (gray background)
element tile_quality_metric(const std::string& title_text, const std::string& value_id) {
    span tile;
    tile.cl("tile-quality-metric");
    tile << span(title_text).cl("tile-title");
    tile << br();
    tile << span().cl("tile-value").id(value_id);
    return tile;
}

// Black background tile
element tile_black_large(const std::string& title_text, const std::string& value_id) {
    span tile;
    tile.cl("tile-black-large");
    tile << span(title_text).cl("tile-title");
    tile << br();
    tile << span().cl("tile-value").id(value_id);
    return tile;
}

// Basic tile with title and content
element basic_tile(const std::string& title_text, const std::string& content_id, const std::string& width = "") {
    html::div tile;
    tile.cl("basic-tile");
    tile << span(title_text).cl("title");
    tile << br();
    tile << span().cl("content").id(content_id);
    if (!width.empty()) {
        tile.style("width: " + width);
    }
    return tile;
}

// Section title with toggle
element section_title(const std::string& title_text, const std::string& target_class) {
    html::div title_div;
    title_div.cl("section-title");
    title_div << text(title_text);
    html::div toggle;
    toggle.cl("toggle-img").add_attr("data-target", target_class);
    title_div << toggle;
    return title_div;
}

// Flex row container
element row_flex(const std::string& extra_class = "") {
    auto row = html::div().cl("row-100-flex");
    if (!extra_class.empty()) {
        row.add_cl(extra_class);
    }
    return row;
}

// Spacer div with percentage width
element spacer(const std::string& width) {
    return html::div().style("width: " + width);
}

// Left column (25% width, right-aligned)
element left_column() {
    return html::div().style("width: 25%; text-align: right;");
}

//=============================================================================
// CSS STYLESHEET
//=============================================================================

const char* playground_css = R"(
/********************************/
/********* REPORT TITLE *********/
/********************************/

.section-report-title {
    text-align: center !important;
    padding: 20px !important;
    background-color: black !important;
    color: white !important;
    width: 100% !important;
    position: relative;
}

.section-report-title .content-wrapper {
    max-width: 1200px !important;
    margin: 0 auto !important;
}

.section-report-title h1 {
    font-size: 3.5em;
    font-weight: 700;
    margin: 0;
    letter-spacing: 0.02em;
    font-family: 'Segoe UI', 'Arial', sans-serif;
}

.section-report-title .subtitle {
    color: #ccc;
    margin-top: 0.3em;
}

.section-report-title .powered-by {
    font-size: 0.85em;
    color: #ccc;
}

.section-report-title .company-name {
    font-size: 1.1em;
    color: #4d9fff;
    text-decoration: underline;
}

.section-report-title .company-name:hover {
    color: #3385ff;
}

.section-report-title .generated-date {
    position: absolute;
    bottom: 10px;
    right: 20px;
    font-size: 0.8em;
    color: #ccc;
    z-index: 1;
}

.mb-10 {
    margin-bottom: 10px;
}

.toggle-img {
    height: 18px;
    width: 14px;
    cursor: pointer;
    margin-left: 10px;
    background-image: url('./toggle1.png');
    background-size: contain;
    background-repeat: no-repeat;
}

.toggle-img:hover {
    border: 1px solid;
}

.row-100-flex {
    width: 100%;
    display: flex;
}

/********* PAGE-CONTENT *********/

.page-content {
    margin: 10px auto 0px auto;
    padding: 10px;
    max-width: 800px;
    min-width: 685px;
    font-family: 'Lato', sans-serif;
    font-weight: 400;
    font-family: Calibri, 'Trebuchet MS', sans-serif;
}

/*********************************/
/********* SECTION TITLE *********/
/*********************************/

.section-title {
    display: flex;
    align-items: center;
    gap: 8px;
    font-size: 18px;
    font-weight: 700;
    cursor: pointer;
    margin: 5px 0 5px 0;
}

.section-title .toggle-img {
    margin: 0;
    width: 16px;
    height: 16px;
    background-image: url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' fill='%232c3e50'%3E%3Cpath d='M19 9l-7 7-7-7'/%3E%3C/svg%3E");
    background-size: contain;
    background-repeat: no-repeat;
    transition: transform 0.3s ease;
}

.section-title.collapsed .toggle-img {
    transform: rotate(-90deg);
}

/*********************************/
/********* SECTION  **************/
/*********************************/

.standard_section {
    background: rgb(247, 248, 249);
    border: 1px solid rgb(229, 229, 229);
    padding: 10px;
    border-radius: 6px;
    opacity: 1;
    transition: opacity 1s;
}

/********* SECTION::ATRIBS_1  **************/

.section__attributes_1 {
    padding: 15px 0;
    margin: 0px 0 0px 0;
}

.section__attributes_1 .strategy-row {
    margin-bottom: 8px;
}

.section__attributes_1 .strategy-label {
    font-size: 18px;
    font-weight: 700;
    border-radius: 6px;
    margin-right: 10px;
}

.section__attributes_1 .strategy-name {
    font-size: 1.2em;
    background: rgb(225,237,255);
    border: 1px solid #ddd;
    color: rgb(16, 113, 255);
    padding: 2px 10px;
    border-radius: 15px;
}

/********* SECTION::ATRIBS_2__NET_PROFIT  **************/

.section__attributes_2__net_profit {
    background: rgb(225, 243, 240);
    border: 1px solid rgb(31, 141, 119);
    padding: 10px;
    border-radius: 6px;
    display: flex;
    flex-direction: column;
    min-height: 150px;
}

.section__attributes_2__net_profit .section-title {
    font-size: 20px;
    font-weight: 500;
    color: rgb(31, 141, 119);
    text-align: left;
    margin-bottom: 10px;
}

.section__attributes_2__net_profit .section-value {
    flex: 1;
    display: flex;
    justify-content: center;
    align-items: center;
    color: rgb(31, 141, 119);
    margin-top: -15px;
}

.section__attributes_2__net_profit .section-value .value-main {
    font-size: 35px;
}

.section__attributes_2__net_profit .section-value .value-decimal {
    font-size: 23px;
}

.section__attributes_2__net_profit .section-currency {
    text-align: center;
    color: rgb(31, 141, 119);
    font-size: 13px;
    font-weight: 400;
    border: 1px solid rgb(31, 141, 119);
    border-radius: 4px;
    padding: 0px 3px;
    width: fit-content;
    margin: 0 auto;
}

/********* SECTION::ATRIBS_2__RIGHT  **************/

.section__attributes_2_right .date {
    margin: 0px;
    font-weight: 700;
    font-size: 23px;
}

.section__attributes_2_right .time {
    margin: 0px;
    font-weight: 500;
    font-size: 17px;
}

/**************************/
/********* TILES **********/
/**************************/

/********* BASIC TILE *********/

.basic-tile {
    display: inline-block;
    text-align: left;
}

.basic-tile .title {
    color: rgb(0, 32, 96);
    margin: 0px;
    font-size: 17px;
    font-weight: 400;
}

.basic-tile .content {
    height: 30px;
    border: 1px solid rgb(217, 217, 217);
    background: white;
    color: rgb(0, 32, 100);
    display: flex;
    width: min-content;
    min-width: 120px;
    align-items: center;
    justify-content: center;
    font-family: 'Roboto Mono', monospace;
    font-size: 17px;
    border-radius: 3px;
}

.basic-tile .extra-content {
    height: 30px;
    position: absolute;
    bottom: 0px;
    padding: 4px 10px;
    margin-left: 4px;
    background: rgb(161, 180, 199);
    color: white;
    font-family: 'Roboto Mono', monospace;
    border-radius: 3px;
}

/********* TILE::BLUE-LARGE *********/

.tile-blue-large {
    display: inline-block;
    color: rgb(0, 32, 96);
    border-radius: 5px;
    text-align: center;
    padding: 2px 10px 2px;
    min-width: 120px;
    background: rgb(241, 245, 249);
    border: 1px solid rgb(57, 129, 246);
}

.tile-blue-large .title {
    font-size: 18px;
    font-weight: 400;
}

.tile-blue-large .value {
    margin: 0px;
    color: #24292f;
    font-weight: 700;
    align-items: center;
    font-family: 'Roboto Mono', monospace;
    font-size: 19px;
}

/********* TILE::CAMELEON-LARGE *********/

.tile-cameleon-large {
    display: inline-block;
    color: rgb(206, 49, 49);
    border-radius: 5px;
    text-align: center;
    padding: 2px 10px 2px;
    min-width: 120px;
    background: rgb(255, 237, 237);
    border: 1px solid rgb(206, 49, 49);
}

.tile-cameleon-large .title {
    font-size: 18px;
    font-weight: 400;
}

.tile-cameleon-large .value {
    margin: 0px;
    color: rgb(206, 49, 49);
    font-weight: 700;
    align-items: center;
    font-family: 'Roboto Mono', monospace;
    font-size: 19px;
}

.tile-cameleon-large .value-with-sign {
    margin: 0px;
    color: rgb(216, 59, 59);
    font-weight: 700;
    align-items: center;
    font-family: 'Roboto Mono', monospace;
    font-size: 19px;
}

/********* TILE::QUALITY-METRIC *********/

.tile-quality-metric {
    display: inline-block;
    color: rgb(0, 32, 96);
    border-radius: 5px;
    text-align: center;
    padding: 2px 10px 2px;
    min-width: 120px;
    background: rgb(245, 246, 247);
    border: 1px solid rgb(200, 200, 200);
}

.tile-quality-metric .tile-title {
    color: rgb(0, 32, 96);
    font-size: 17px;
    font-weight: 400;
}

.tile-quality-metric .tile-value {
    margin: 0px;
    color: #24292f;
    font-weight: 700;
    align-items: center;
    font-family: 'Roboto Mono', monospace;
    font-size: 19px;
}

/********* TILE::BLACK-LARGE *********/

.tile-black-large {
    display: inline-block;
    color: rgb(0, 32, 96);
    border-radius: 5px;
    text-align: center;
    padding: 2px 10px 2px;
    min-width: 120px;
    background: rgb(20, 20, 20);
    border: 1px solid rgb(200, 200, 200);
}

.tile-black-large .tile-title {
    color: rgb(255, 255, 255);
}

.tile-black-large .tile-value {
    margin: 0px;
    color: rgb(255, 255, 255);
    font-weight: 700;
    align-items: center;
    font-family: 'Roboto Mono', monospace;
    font-size: 19px;
}

/**************************/
/********* FOOTER *********/
/**************************/

.footer {
    background-color: black !important;
    color: #ccc !important;
    padding: 15px 20px !important;
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-top: 2rem;
}

.footer .powered-by {
    font-size: 0.85em;
    color: #ccc;
}

.footer .company-name {
    font-size: 1.1em;
    color: #4d9fff;
    text-decoration: underline;
}

.footer .website {
    color: #4d9fff;
    text-decoration: underline;
}
)";

//=============================================================================
// JAVASCRIPT FOR TOGGLE
//=============================================================================

const char* toggle_script = R"(
document.querySelectorAll('.section-title').forEach(title => {
    title.addEventListener('click', () => {
        title.classList.toggle('collapsed');
        const sectionId = title.querySelector('.toggle-img').getAttribute('data-target');
        const section = document.querySelector('.' + sectionId);
        if (section) {
            section.style.display = section.style.display === 'none' ? 'block' : 'none';
        }
    });
});
)";

} // anonymous namespace

//=============================================================================
// TEST CASE
//=============================================================================

TEST_CASE("80000: Playground report generation", "[output][report]") {
    page pg;
    pg.head << title("Performance");
    pg.head << head_link(attr("href", "res/bootstrap/css/bootstrap.min.css"), attr("rel", "stylesheet"));
    pg.head << style(playground_css);

    // ============== REPORT TITLE SECTION ==============
    html::div report_title;
    report_title.cl("section-report-title");

    html::div content_wrapper;
    content_wrapper.cl("content-wrapper");
    content_wrapper << h1("Trading Systems Report");

    html::div subtitle;
    subtitle.cl("subtitle");
    subtitle << span("Powered by").cl("powered-by");
    subtitle << anchor("http://www.TradingSystemAPI.com", "Trading System API").cl("company-name");
    content_wrapper << subtitle;

    html::div gen_date;
    gen_date.cl("generated-date");
    gen_date << text("Generated on: ");
    gen_date << span("2024-10-12 14:33:15.4").id("generated_datetime");
    content_wrapper << gen_date;

    report_title << content_wrapper;
    pg << report_title;

    // ============== PAGE CONTENT ==============
    html::div page_content;
    page_content.cl("page-content");

    // ============== STRATEGY ATTRIBUTES 1 ==============
    html::div attribs1;
    attribs1.cl("section__attributes_1");

    html::div strat_row;
    strat_row.cl("strategy-row");
    strat_row << span("Strategy Name:").cl("strategy-label");
    strat_row << span("My-greate-strategy").cl("strategy-name").id("5000_A");
    strat_row << span("Instruments:").cl("strategy-label").style("margin-left: 30px;");
    strat_row << span("ES:CME").cl("strategy-name").style("background: #FFF2E1; color: #9B631A;");
    attribs1 << strat_row;

    page_content << attribs1;

    // ============== NET PROFIT AND ATTRIBUTES 2 ==============
    html::div section_container;
    section_container.style("display: flex; gap: 20px; align-items: stretch;");

    // Left: Net Profit
    html::div net_profit;
    net_profit.cl("section__attributes_2__net_profit").style("flex: 1;");

    html::div np_title;
    np_title.cl("section-title");
    np_title << text("Net Profit");
    net_profit << np_title;

    html::div np_value;
    np_value.cl("section-value");
    np_value << span().cl("value-sign");
    np_value << span().cl("value-main").id("1020_A_1");
    np_value << text(".");
    np_value << span().cl("value-decimal").id("1020_A_2");
    net_profit << np_value;

    html::div np_currency;
    np_currency.cl("section-currency");
    np_currency << text("USD");
    net_profit << np_currency;

    section_container << net_profit;

    // Right: Other Attributes
    html::div attribs2_right;
    attribs2_right.cl("standard_section section__attributes_2_right").style("flex: 2;");

    table attribs_table;
    attribs_table.style("width: 100%; border-spacing: 0; border-collapse: separate;");

    // Date range row
    tr date_row;
    td date_cell;
    date_cell.colspan(4).style("padding: 5px 5px;");
    html::div date_content;
    date_content.style("display: flex; align-items: center; justify-content: center; gap: 20px;");
    html::div start_date;
    start_date.style("text-align: center;");
    start_date << span().cl("date").id("5050_A");
    start_date << br();
    start_date << span().cl("time").id("5052_A");
    date_content << start_date;

    date_content << img("./arrow.png", "20").style("height: 20px;");

    html::div end_date;
    end_date.style("text-align: center;");
    end_date << span().cl("date").id("5051_A");
    end_date << br();
    end_date << span().cl("time").id("5053_A");
    date_content << end_date;
    date_content << tile_quality_metric("Period", "5024_A").style("min-width: 100px; margin-left: 20px; border: 2px solid black;");
    date_cell << date_content;
    date_row << date_cell;
    attribs_table << date_row;

    // Bar frequency row
    tr freq_row;
    freq_row.style("height: 50px;");
    td freq_cell1;
    freq_cell1.style("width: 25%; padding-left: 25px;");
    html::div freq_content1;
    freq_content1.style("display: flex; align-items: center; height: 100%;");
    freq_content1 << span("Bar Frequency:").style("color: rgb(0, 32, 96); font-size: 17px; font-weight: 400; margin-right: 10px;");
    freq_content1 << span().style("font-family: 'Roboto Mono', monospace; font-size: 17px; border: 1px solid #ddd; padding: 2px 8px; border-radius: 3px;").id("5047_A");
    freq_cell1 << freq_content1;
    freq_row << freq_cell1;

    td freq_cell2;
    freq_cell2.style("width: 25%; padding: 5px;");
    html::div freq_content2;
    freq_content2.style("display: flex; align-items: center; height: 100%;");
    freq_content2 << span("Num Bars:").style("color: rgb(0, 32, 96); font-size: 17px; font-weight: 400; margin-right: 10px;");
    freq_content2 << span().style("font-family: 'Roboto Mono', monospace; font-size: 17px; border: 1px solid #ddd; padding: 2px 8px; border-radius: 3px;").id("5030_A");
    freq_cell2 << freq_content2;
    freq_row << freq_cell2;
    attribs_table << freq_row;

    attribs2_right << attribs_table;
    section_container << attribs2_right;
    page_content << section_container;

    // ============== ACCOUNT SECTION ==============
    page_content << section_title("Account", "section__account");

    html::div account_section;
    account_section.cl("standard_section section__account");

    // Row 1: Return, Start/End Account
    auto row1 = row_flex("mb-10");
    auto left1 = left_column();
    left1 << tile_cameleon_large("Return", "6018_A", true);
    row1 << left1;
    row1 << spacer("10%");

    html::div accounts_container;
    accounts_container.style("display: flex; align-items: start; justify-content: center; gap: 20px; width: 65%;");
    accounts_container << html::div(tile_black_large("Start Account", "6000_A").style("width: 200px;"));
    accounts_container << img("./arrow.png", "20").style("height: 20px; align-self: center;");
    accounts_container << html::div(tile_black_large("End Account", "6006_A").style("width: 200px;"));
    row1 << accounts_container;
    account_section << row1;

    // Row 2: Annualized Return, Max Drawdown, Min Start Acct
    auto row2 = row_flex();
    auto left2 = left_column();
    left2 << basic_tile("Annualized Ret.", "6022_A");
    row2 << left2;
    row2 << spacer("10%");

    auto dd_tile = basic_tile("Max Drawdown", "6102_A", "35%");
    dd_tile.style("width: 35%; position: relative; margin-left: 60px;");
    html::div extra;
    extra.cl("extra-content");
    extra << span().id("6110_A");
    extra << text("%");
    // Note: extra-content would need to be added to the tile
    row2 << dd_tile;
    row2 << basic_tile("Min. Start Acct.", "xxx", "30%");
    account_section << row2;

    page_content << account_section;

    // ============== QUALITY SECTION ==============
    page_content << section_title("Quality", "section__quality");

    html::div quality_section;
    quality_section.cl("standard_section section__quality");

    // Row 1
    auto qrow1 = row_flex("mb-10");
    auto qleft1 = left_column();
    qleft1 << tile_blue_large("Sharpe Ratio", "7000_A");
    qrow1 << qleft1;
    qrow1 << spacer("10%");
    qrow1 << html::div(tile_quality_metric("S-Quality Score", "7018_A")).style("width: 20%;");
    qrow1 << html::div(tile_quality_metric("S-Quality Nbr.", "7016_A")).style("width: 20%;");
    qrow1 << html::div(tile_quality_metric("MAR Ratio", "7008_A")).style("width: 25%;");
    quality_section << qrow1;

    // Row 2
    auto qrow2 = row_flex();
    auto qleft2 = left_column();
    qleft2 << tile_blue_large("Sortino Ratio", "7002_A");
    qrow2 << qleft2;
    qrow2 << spacer("10%");
    qrow2 << html::div(tile_quality_metric("Expectancy", "7022_A")).style("width: 20%;");
    qrow2 << html::div(tile_quality_metric("Min. Start Acct.", "xxx")).style("width: 20%;");
    qrow2 << html::div(tile_quality_metric("Equity Slope", "7004_A")).style("width: 25%;");
    quality_section << qrow2;

    page_content << quality_section;

    // ============== TRADES SECTION ==============
    page_content << section_title("Trades", "section__trades");

    html::div trades_section;
    trades_section.cl("standard_section section__trades");

    // Row 1: Trades, Avg Trade, Stdev, Median
    auto trow1 = row_flex("mb-10");
    auto tleft1 = left_column();
    tleft1 << tile_blue_large("Trades", "1000_A");
    trow1 << tleft1;
    trow1 << spacer("10%");
    trow1 << html::div(tile_cameleon_large("Avg. Trade", "1011_A")).style("width: 20%;");
    trow1 << basic_tile("Stdev.", "1026_A", "20%");
    trow1 << basic_tile("Median Trade", "1017_A", "25%");
    trades_section << trow1;

    // Row 2: Win Ratio, Winners, Losers, Even
    auto trow2 = row_flex("mb-10");
    auto tleft2 = left_column();
    tleft2 << tile_blue_large("Win Ratio", "1010_A");
    trow2 << tleft2;
    trow2 << spacer("10%");
    trow2 << basic_tile("Num. Winners", "1002_A", "20%");
    trow2 << basic_tile("Num. Losers", "1001_A", "20%");
    trow2 << basic_tile("Num. Even", "1003_A", "25%");
    trades_section << trow2;

    // Row 3: Payout Ratio, Avg Winners, Avg Losers
    auto trow3 = row_flex("mb-10");
    auto tleft3 = left_column();
    tleft3 << tile_blue_large("Payout Ratio", "7024_A");
    trow3 << tleft3;
    trow3 << spacer("10%");
    trow3 << basic_tile("Avg. Winners", "1013_A", "20%");
    trow3 << basic_tile("Avg. Losers", "1014_A", "45%");
    trades_section << trow3;

    // Row 4: Profit Factor, Total Winnings, Total Losses
    auto trow4 = row_flex("mb-10");
    auto tleft4 = left_column();
    tleft4 << tile_blue_large("Profit Factor", "1023_A");
    trow4 << tleft4;
    trow4 << spacer("10%");
    trow4 << basic_tile("Total Winnings(Net)", "1024_A", "20%");
    trow4 << basic_tile("Total Loses(Net)", "1025_A", "45%");
    trades_section << trow4;

    // Row 5: Long-Short Ratio, Num Long, Num Short
    auto trow5 = row_flex("mb-10");
    auto tleft5 = left_column();
    tleft5 << tile_blue_large("Lng-Shrt Ratio", "xxx");
    trow5 << tleft5;
    trow5 << spacer("10%");
    trow5 << basic_tile("Num. Long", "1000_L", "20%");
    trow5 << basic_tile("Num. Short", "1000_S", "45%");
    trades_section << trow5;

    // Row 6: Symmetry, Avg Long Profit, Avg Short Profit
    auto trow6 = row_flex("mb-10");
    auto tleft6 = left_column();
    tleft6 << tile_blue_large("Symmetry", "1500_A");
    trow6 << tleft6;
    trow6 << spacer("10%");
    trow6 << basic_tile("Avg. Long Profit", "1013_L", "20%");
    trow6 << basic_tile("Avg. Short Profit", "1013_S", "45%");
    trades_section << trow6;

    page_content << trades_section;

    // ============== COSTS SECTION ==============
    page_content << section_title("Costs", "section__costs");

    html::div costs_section;
    costs_section.cl("standard_section section__costs");

    // Row 1
    auto crow1 = row_flex("mb-10");
    auto cleft1 = left_column();
    cleft1 << tile_blue_large("Total Costs", "1105_A");
    crow1 << cleft1;
    crow1 << spacer("10%");
    crow1 << basic_tile("Total Commission", "1103_A", "30%");
    crow1 << basic_tile("Total Slippage", "1104_A", "35%");
    costs_section << crow1;

    // Row 2
    auto crow2 = row_flex();
    auto cleft2 = left_column();
    cleft2 << basic_tile("Trade Cost (Avg.)", "1102_A");
    crow2 << cleft2;
    crow2 << spacer("10%");
    crow2 << basic_tile("Trade Commission (Avg.)", "1100_A", "30%");
    crow2 << basic_tile("Trade Slippage (Avg.)", "1101_A", "35%");
    costs_section << crow2;

    page_content << costs_section;

    // ============== UNITS SECTION ==============
    page_content << section_title("Units", "section__units");

    html::div units_section;
    units_section.cl("standard_section section__units");

    // Row 1
    auto urow1 = row_flex("mb-10");
    auto uleft1 = left_column();
    uleft1 << tile_blue_large("Units Traded", "2110_A");
    urow1 << uleft1;
    urow1 << spacer("10%");
    urow1 << basic_tile("Unit Net Profit (Avg.)", "2103_A", "30%");
    urow1 << basic_tile("Unit Gross Profit (Avg.)", "2104_A", "35%");
    units_section << urow1;

    // Row 2
    auto urow2 = row_flex("mb-10");
    auto uleft2 = left_column();
    uleft2 << tile_blue_large("Unit Costs (Avg.)", "2101_A");
    urow2 << uleft2;
    urow2 << spacer("10%");
    urow2 << basic_tile("Unit Commission", "4004_A", "35%");
    urow2 << basic_tile("Unit Slippage (Avg.)", "2100_A", "35%");
    units_section << urow2;

    page_content << units_section;

    // ============== TEST SECTION 1 ==============
    page_content << section_title("Test Section 1", "section__test_1");

    html::div test_section;
    test_section.cl("standard_section section__test_1");

    // Row 1
    auto tsrow1 = row_flex("mb-10");
    auto tsleft1 = left_column();
    tsleft1 << tile_blue_large("Total Units", "2110_A");
    tsrow1 << tsleft1;
    tsrow1 << spacer("10%");
    tsrow1 << basic_tile("Net Profit A", "1103_A", "30%");
    tsrow1 << basic_tile("Cost(Avg.)", "1104_A", "35%");
    test_section << tsrow1;

    // Row 2
    auto tsrow2 = row_flex("mb-10");
    auto tsleft2 = left_column();
    tsleft2 << basic_tile("Net Profit B", "1103_A");
    tsrow2 << tsleft2;
    tsrow2 << spacer("10%");
    tsrow2 << basic_tile("Net Profit C", "1103_A", "30%");
    tsrow2 << basic_tile("Cost(Avg.)B", "1104_A", "35%");
    test_section << tsrow2;

    // Row 3
    auto tsrow3 = row_flex();
    tsrow3 << spacer("35%");
    tsrow3 << basic_tile("Gross Profit(Avg.)", "2104_A", "30%");
    tsrow3 << basic_tile("Slippage(Avg.)", "2100_A", "35%");
    test_section << tsrow3;

    page_content << test_section;

    pg << page_content;

    // ============== FOOTER ==============
    html::div footer;
    footer.cl("footer");
    footer << html::div(
        span("powered by").cl("powered-by"),
        anchor("http://www.TradingSystemAPI.com", "Trading System API").cl("company-name")
    );
    footer << anchor("http://www.TradingSystemAPI.com", "www.TradingSystemAPI.com").cl("website");
    pg << footer;

    // ============== SCRIPTS ==============
    pg << script().src("./data.js");
    pg << script().src("./custom.js");
    pg << script(toggle_script);

    // Save the page
    save_page("playground_report.html", pg);

    CHECK(std::filesystem::exists(get_output_dir() / "playground_report.html"));
}

//=============================================================================
// TEST CASE 80010 - Concise version using variadic constructors
//=============================================================================

TEST_CASE("80010: Playground report - concise variadic style", "[output][report]") {
    page pg;
    pg.head << title("Performance");
    pg.head << head_link(attr("href", "res/bootstrap/css/bootstrap.min.css"), attr("rel", "stylesheet"));
    pg.head << style(playground_css);

    // ============== REPORT TITLE SECTION ==============
    pg << html::div(
        html::div(
            h1("Trading Systems Report"),
            html::div(
                span("Powered by").cl("powered-by"),
                anchor("http://www.TradingSystemAPI.com", "Trading System API").cl("company-name")
            ).cl("subtitle"),
            html::div(
                text("Generated on: "),
                span("2024-10-12 14:33:15.4").id("generated_datetime")
            ).cl("generated-date")
        ).cl("content-wrapper")
    ).cl("section-report-title");

    // ============== PAGE CONTENT ==============
    html::div page_content;
    page_content.cl("page-content");

    // ============== STRATEGY ATTRIBUTES 1 ==============
    page_content << html::div(
        html::div(
            span("Strategy Name:").cl("strategy-label"),
            span("My-greate-strategy").cl("strategy-name").id("5000_A"),
            span("Instruments:").cl("strategy-label").style("margin-left: 30px;"),
            span("ES:CME").cl("strategy-name").style("background: #FFF2E1; color: #9B631A;")
        ).cl("strategy-row")
    ).cl("section__attributes_1");

    // ============== NET PROFIT AND ATTRIBUTES 2 ==============
    page_content << html::div(
        // Left: Net Profit
        html::div(
            html::div(text("Net Profit")).cl("section-title"),
            html::div(
                span().cl("value-sign"),
                span().cl("value-main").id("1020_A_1"),
                text("."),
                span().cl("value-decimal").id("1020_A_2")
            ).cl("section-value"),
            html::div(text("USD")).cl("section-currency")
        ).cl("section__attributes_2__net_profit").style("flex: 1;"),
        // Right: Other Attributes
        html::div(
            table(
                // Date range row
                tr(td(
                    html::div(
                        html::div(
                            span().cl("date").id("5050_A"),
                            br(),
                            span().cl("time").id("5052_A")
                        ).style("text-align: center;"),
                        img("./arrow.png", "20").style("height: 20px;"),
                        html::div(
                            span().cl("date").id("5051_A"),
                            br(),
                            span().cl("time").id("5053_A")
                        ).style("text-align: center;"),
                        tile_quality_metric("Period", "5024_A").style("min-width: 100px; margin-left: 20px; border: 2px solid black;")
                    ).style("display: flex; align-items: center; justify-content: center; gap: 20px;")
                ).colspan(4).style("padding: 5px 5px;")),
                // Bar frequency row
                tr(
                    td(html::div(
                        span("Bar Frequency:").style("color: rgb(0, 32, 96); font-size: 17px; font-weight: 400; margin-right: 10px;"),
                        span().style("font-family: 'Roboto Mono', monospace; font-size: 17px; border: 1px solid #ddd; padding: 2px 8px; border-radius: 3px;").id("5047_A")
                    ).style("display: flex; align-items: center; height: 100%;")).style("width: 25%; padding-left: 25px;"),
                    td(html::div(
                        span("Num Bars:").style("color: rgb(0, 32, 96); font-size: 17px; font-weight: 400; margin-right: 10px;"),
                        span().style("font-family: 'Roboto Mono', monospace; font-size: 17px; border: 1px solid #ddd; padding: 2px 8px; border-radius: 3px;").id("5030_A")
                    ).style("display: flex; align-items: center; height: 100%;")).style("width: 25%; padding: 5px;")
                ).style("height: 50px;")
            ).style("width: 100%; border-spacing: 0; border-collapse: separate;")
        ).cl("standard_section section__attributes_2_right").style("flex: 2;")
    ).style("display: flex; gap: 20px; align-items: stretch;");

    // ============== ACCOUNT SECTION ==============
    page_content << section_title("Account", "section__account");
    page_content << html::div(
        // Row 1: Return, Start/End Account
        html::div(
            html::div(tile_cameleon_large("Return", "6018_A", true)).style("width: 25%; text-align: right;"),
            spacer("10%"),
            html::div(
                html::div(tile_black_large("Start Account", "6000_A").style("width: 200px;")),
                img("./arrow.png", "20").style("height: 20px; align-self: center;"),
                html::div(tile_black_large("End Account", "6006_A").style("width: 200px;"))
            ).style("display: flex; align-items: start; justify-content: center; gap: 20px; width: 65%;")
        ).cl("row-100-flex mb-10"),
        // Row 2: Annualized Return, Max Drawdown, Min Start Acct
        html::div(
            html::div(basic_tile("Annualized Ret.", "6022_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            basic_tile("Max Drawdown", "6102_A", "35%").style("width: 35%; position: relative; margin-left: 60px;"),
            basic_tile("Min. Start Acct.", "xxx", "30%")
        ).cl("row-100-flex")
    ).cl("standard_section section__account");

    // ============== QUALITY SECTION ==============
    page_content << section_title("Quality", "section__quality");
    page_content << html::div(
        // Row 1
        html::div(
            html::div(tile_blue_large("Sharpe Ratio", "7000_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            html::div(tile_quality_metric("S-Quality Score", "7018_A")).style("width: 20%;"),
            html::div(tile_quality_metric("S-Quality Nbr.", "7016_A")).style("width: 20%;"),
            html::div(tile_quality_metric("MAR Ratio", "7008_A")).style("width: 25%;")
        ).cl("row-100-flex mb-10"),
        // Row 2
        html::div(
            html::div(tile_blue_large("Sortino Ratio", "7002_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            html::div(tile_quality_metric("Expectancy", "7022_A")).style("width: 20%;"),
            html::div(tile_quality_metric("Min. Start Acct.", "xxx")).style("width: 20%;"),
            html::div(tile_quality_metric("Equity Slope", "7004_A")).style("width: 25%;")
        ).cl("row-100-flex")
    ).cl("standard_section section__quality");

    // ============== TRADES SECTION ==============
    page_content << section_title("Trades", "section__trades");
    page_content << html::div(
        // Row 1: Trades, Avg Trade, Stdev, Median
        html::div(
            html::div(tile_blue_large("Trades", "1000_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            html::div(tile_cameleon_large("Avg. Trade", "1011_A")).style("width: 20%;"),
            basic_tile("Stdev.", "1026_A", "20%"),
            basic_tile("Median Trade", "1017_A", "25%")
        ).cl("row-100-flex mb-10"),
        // Row 2: Win Ratio, Winners, Losers, Even
        html::div(
            html::div(tile_blue_large("Win Ratio", "1010_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            basic_tile("Num. Winners", "1002_A", "20%"),
            basic_tile("Num. Losers", "1001_A", "20%"),
            basic_tile("Num. Even", "1003_A", "25%")
        ).cl("row-100-flex mb-10"),
        // Row 3: Payout Ratio, Avg Winners, Avg Losers
        html::div(
            html::div(tile_blue_large("Payout Ratio", "7024_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            basic_tile("Avg. Winners", "1013_A", "20%"),
            basic_tile("Avg. Losers", "1014_A", "45%")
        ).cl("row-100-flex mb-10"),
        // Row 4: Profit Factor, Total Winnings, Total Losses
        html::div(
            html::div(tile_blue_large("Profit Factor", "1023_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            basic_tile("Total Winnings(Net)", "1024_A", "20%"),
            basic_tile("Total Loses(Net)", "1025_A", "45%")
        ).cl("row-100-flex mb-10"),
        // Row 5: Long-Short Ratio, Num Long, Num Short
        html::div(
            html::div(tile_blue_large("Lng-Shrt Ratio", "xxx")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            basic_tile("Num. Long", "1000_L", "20%"),
            basic_tile("Num. Short", "1000_S", "45%")
        ).cl("row-100-flex mb-10"),
        // Row 6: Symmetry, Avg Long Profit, Avg Short Profit
        html::div(
            html::div(tile_blue_large("Symmetry", "1500_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            basic_tile("Avg. Long Profit", "1013_L", "20%"),
            basic_tile("Avg. Short Profit", "1013_S", "45%")
        ).cl("row-100-flex mb-10")
    ).cl("standard_section section__trades");

    // ============== COSTS SECTION ==============
    page_content << section_title("Costs", "section__costs");
    page_content << html::div(
        // Row 1
        html::div(
            html::div(tile_blue_large("Total Costs", "1105_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            basic_tile("Total Commission", "1103_A", "30%"),
            basic_tile("Total Slippage", "1104_A", "35%")
        ).cl("row-100-flex mb-10"),
        // Row 2
        html::div(
            html::div(basic_tile("Trade Cost (Avg.)", "1102_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            basic_tile("Trade Commission (Avg.)", "1100_A", "30%"),
            basic_tile("Trade Slippage (Avg.)", "1101_A", "35%")
        ).cl("row-100-flex")
    ).cl("standard_section section__costs");

    // ============== UNITS SECTION ==============
    page_content << section_title("Units", "section__units");
    page_content << html::div(
        // Row 1
        html::div(
            html::div(tile_blue_large("Units Traded", "2110_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            basic_tile("Unit Net Profit (Avg.)", "2103_A", "30%"),
            basic_tile("Unit Gross Profit (Avg.)", "2104_A", "35%")
        ).cl("row-100-flex mb-10"),
        // Row 2
        html::div(
            html::div(tile_blue_large("Unit Costs (Avg.)", "2101_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            basic_tile("Unit Commission", "4004_A", "35%"),
            basic_tile("Unit Slippage (Avg.)", "2100_A", "35%")
        ).cl("row-100-flex mb-10")
    ).cl("standard_section section__units");

    // ============== TEST SECTION 1 ==============
    page_content << section_title("Test Section 1", "section__test_1");
    page_content << html::div(
        // Row 1
        html::div(
            html::div(tile_blue_large("Total Units", "2110_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            basic_tile("Net Profit A", "1103_A", "30%"),
            basic_tile("Cost(Avg.)", "1104_A", "35%")
        ).cl("row-100-flex mb-10"),
        // Row 2
        html::div(
            html::div(basic_tile("Net Profit B", "1103_A")).style("width: 25%; text-align: right;"),
            spacer("10%"),
            basic_tile("Net Profit C", "1103_A", "30%"),
            basic_tile("Cost(Avg.)B", "1104_A", "35%")
        ).cl("row-100-flex mb-10"),
        // Row 3
        html::div(
            spacer("35%"),
            basic_tile("Gross Profit(Avg.)", "2104_A", "30%"),
            basic_tile("Slippage(Avg.)", "2100_A", "35%")
        ).cl("row-100-flex")
    ).cl("standard_section section__test_1");

    pg << page_content;

    // ============== FOOTER ==============
    pg << html::div(
        html::div(
            span("powered by").cl("powered-by"),
            anchor("http://www.TradingSystemAPI.com", "Trading System API").cl("company-name")
        ),
        anchor("http://www.TradingSystemAPI.com", "www.TradingSystemAPI.com").cl("website")
    ).cl("footer");

    // ============== SCRIPTS ==============
    pg << script().src("./data.js");
    pg << script().src("./custom.js");
    pg << script(toggle_script);

    // Save the page
    save_page("playground_report_concise.html", pg);

    CHECK(std::filesystem::exists(get_output_dir() / "playground_report_concise.html"));
}
