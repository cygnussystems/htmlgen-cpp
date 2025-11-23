/*  ===================================================================
*                      HTML Generator Library - Tests
*               Copyright 1999 - 2024 by Peter Ritter
*                A L L   R I G H T S   R E S E R V E D
*  ====================================================================
*/

#include <catch2/catch_all.hpp>
#include "../include/html_tags.h"

using namespace html;

TEST_CASE("25000: Video element", "[elements][media]") {
    video v;
    v.src("video.mp4");
    v.controls().autoplay();
    std::string html = v.html_string();
    CHECK(html.find("<video") != std::string::npos);
    CHECK(html.find("src=\"video.mp4\"") != std::string::npos);
    CHECK(html.find("controls=\"controls\"") != std::string::npos);
    CHECK(html.find("autoplay=\"autoplay\"") != std::string::npos);
}

TEST_CASE("25010: Audio element", "[elements][media]") {
    audio a;
    a.src("audio.mp3");
    a.controls().loop();
    std::string html = a.html_string();
    CHECK(html.find("<audio") != std::string::npos);
    CHECK(html.find("controls=\"controls\"") != std::string::npos);
    CHECK(html.find("loop=\"loop\"") != std::string::npos);
}

TEST_CASE("25020: Source element", "[elements][media]") {
    source s("video.mp4", "video/mp4");
    std::string html = s.html_string();
    CHECK(html.find("<source") != std::string::npos);
    CHECK(html.find("src=\"video.mp4\"") != std::string::npos);
    CHECK(html.find("type=\"video/mp4\"") != std::string::npos);
}

TEST_CASE("25030: Picture element", "[elements][media]") {
    picture pic;
    pic << source("large.jpg", "image/jpeg") << img("fallback.jpg");
    std::string html = pic.html_string();
    CHECK(html.find("<picture>") != std::string::npos);
    CHECK(html.find("</picture>") != std::string::npos);
}

TEST_CASE("25040: Track element", "[elements][media]") {
    track t;
    t.src("subtitles.vtt");
    t.kind("subtitles").srclang("en").label("English");
    std::string html = t.html_string();
    CHECK(html.find("<track") != std::string::npos);
    CHECK(html.find("kind=\"subtitles\"") != std::string::npos);
    CHECK(html.find("srclang=\"en\"") != std::string::npos);
}

TEST_CASE("25050: Iframe element", "[elements][media]") {
    iframe ifr;
    ifr.src("https://example.com").width("600").height("400");
    ifr.sandbox("allow-scripts").loading("lazy");
    std::string html = ifr.html_string();
    CHECK(html.find("<iframe") != std::string::npos);
    CHECK(html.find("sandbox=\"allow-scripts\"") != std::string::npos);
    CHECK(html.find("loading=\"lazy\"") != std::string::npos);
}

TEST_CASE("25060: Canvas element", "[elements][media]") {
    canvas c;
    c.id("myCanvas").width("300").height("150");
    std::string html = c.html_string();
    CHECK(html.find("<canvas") != std::string::npos);
    CHECK(html.find("id=\"myCanvas\"") != std::string::npos);
    CHECK(html.find("</canvas>") != std::string::npos);
}
