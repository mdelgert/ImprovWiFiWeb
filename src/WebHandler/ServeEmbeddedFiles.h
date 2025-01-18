#pragma once

#ifdef ENABLE_WEB_HANDLER

#include <Arduino.h>

// Declarations for embedded files

// extern const uint8_t codemirror_css_start[] asm("_binary_web_codemirror_codemirror_min_css_start");
// extern const uint8_t codemirror_css_end[] asm("_binary_web_codemirror_codemirror_min_css_end");

extern const uint8_t actions_html_start[] asm("_binary_web_actions_html_start");
extern const uint8_t actions_html_end[] asm("_binary_web_actions_html_end");
extern const uint8_t actions_js_start[] asm("_binary_web_actions_js_start");
extern const uint8_t actions_js_end[] asm("_binary_web_actions_js_end");

extern const uint8_t advanced_html_start[] asm("_binary_web_advanced_html_start");
extern const uint8_t advanced_html_end[] asm("_binary_web_advanced_html_end");
extern const uint8_t advanced_js_start[] asm("_binary_web_advanced_js_start");
extern const uint8_t advanced_js_end[] asm("_binary_web_advanced_js_end");

extern const uint8_t blueserial_html_start[] asm("_binary_web_blueserial_html_start");
extern const uint8_t blueserial_html_end[] asm("_binary_web_blueserial_html_end");
extern const uint8_t blueserial_js_start[] asm("_binary_web_blueserial_js_start");
extern const uint8_t blueserial_js_end[] asm("_binary_web_blueserial_js_end");

extern const uint8_t editor_css_start[] asm("_binary_web_editor_css_start");
extern const uint8_t editor_css_end[] asm("_binary_web_editor_css_end");
extern const uint8_t editor_html_start[] asm("_binary_web_editor_html_start");
extern const uint8_t editor_html_end[] asm("_binary_web_editor_html_end");
extern const uint8_t editor_js_start[] asm("_binary_web_editor_js_start");
extern const uint8_t editor_js_end[] asm("_binary_web_editor_js_end");

extern const uint8_t error_html_start[] asm("_binary_web_error_html_start");
extern const uint8_t error_html_end[] asm("_binary_web_error_html_end");

extern const uint8_t favicon_ico_start[] asm("_binary_web_favicon_ico_start");
extern const uint8_t favicon_ico_end[]   asm("_binary_web_favicon_ico_end");

extern const uint8_t footer_html_start[] asm("_binary_web_footer_html_start");
extern const uint8_t footer_html_end[] asm("_binary_web_footer_html_end");

extern const uint8_t global_js_start[] asm("_binary_web_global_js_start");
extern const uint8_t global_js_end[] asm("_binary_web_global_js_end");

extern const uint8_t index_html_start[] asm("_binary_web_index_html_start");
extern const uint8_t index_html_end[] asm("_binary_web_index_html_end");
extern const uint8_t index_js_start[] asm("_binary_web_index_js_start");
extern const uint8_t index_js_end[] asm("_binary_web_index_js_end");

extern const uint8_t navbar_html_start[] asm("_binary_web_navbar_html_start");
extern const uint8_t navbar_html_end[] asm("_binary_web_navbar_html_end");

extern const uint8_t settings_html_start[] asm("_binary_web_settings_html_start");
extern const uint8_t settings_html_end[] asm("_binary_web_settings_html_end");
extern const uint8_t settings_js_start[] asm("_binary_web_settings_js_start");
extern const uint8_t settings_js_end[] asm("_binary_web_settings_js_end");

extern const uint8_t styles_css_start[] asm("_binary_web_styles_css_start");
extern const uint8_t styles_css_end[] asm("_binary_web_styles_css_end");

extern const uint8_t terminal_css_start[] asm("_binary_web_terminal_css_start");
extern const uint8_t terminal_css_end[] asm("_binary_web_terminal_css_end");
extern const uint8_t terminal_html_start[] asm("_binary_web_terminal_html_start");
extern const uint8_t terminal_html_end[] asm("_binary_web_terminal_html_end");
extern const uint8_t terminal_js_start[] asm("_binary_web_terminal_js_start");
extern const uint8_t terminal_js_end[] asm("_binary_web_terminal_js_end");

extern const uint8_t timezones_json_start[] asm("_binary_web_timezones_json_start");
extern const uint8_t timezones_json_end[] asm("_binary_web_timezones_json_end");

#endif // ENABLE_WEB_HANDLER
