#ifndef SERVE_EMBEDDED_FILES_H
#define SERVE_EMBEDDED_FILES_H

#include <Arduino.h>

// Declarations for embedded files

extern const uint8_t actions_html_start[] asm("_binary_web_actions_html_start");
extern const uint8_t actions_html_end[] asm("_binary_web_actions_html_end");
extern const uint8_t actions_js_start[] asm("_binary_web_actions_js_start");
extern const uint8_t actions_js_end[] asm("_binary_web_actions_js_end");

extern const uint8_t advanced_html_start[] asm("_binary_web_advanced_html_start");
extern const uint8_t advanced_html_end[] asm("_binary_web_advanced_html_end");
extern const uint8_t advanced_js_start[] asm("_binary_web_advanced_js_start");
extern const uint8_t advanced_js_end[] asm("_binary_web_advanced_js_end");

extern const uint8_t error_html_start[] asm("_binary_web_error_html_start");
extern const uint8_t error_html_end[] asm("_binary_web_error_html_end");

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

#endif // EMBEDDED_FILES_H
