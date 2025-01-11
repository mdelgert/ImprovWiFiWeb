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

extern const uint8_t terminal_css_start[] asm("_binary_web_terminal_css_start");
extern const uint8_t terminal_css_end[] asm("_binary_web_terminal_css_end");
extern const uint8_t terminal_html_start[] asm("_binary_web_terminal_html_start");
extern const uint8_t terminal_html_end[] asm("_binary_web_terminal_html_end");
extern const uint8_t terminal_js_start[] asm("_binary_web_terminal_js_start");
extern const uint8_t terminal_js_end[] asm("_binary_web_terminal_js_end");

#endif // EMBEDDED_FILES_H

//Embedding binary files not working with current toolchain
//Not working - https://stackoverflow.com/questions/68924676/how-to-upload-binary-data-html-favicon-to-esp32-using-esp-idf
//https://community.platformio.org/t/add-t-none-or-t-binary/441/17
//https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/build-system.html#embedding-binary-data
//https://community.platformio.org/t/how-to-embed-binary-files-into-esp32-firmware/3791/2
//https://community.platformio.org/t/how-to-embed-binary-files-into-esp32-firmware/3791/6
//https://docs.platformio.org/en/latest/platforms/espressif32.html#embedding-binary-data
//https://github.com/platformio/platform-espressif32/issues/245
//./xtensa-esp32s3-elf-nm /mnt/d1/home/mdelgert/source/ImprovWiFiWeb/.pio/build/esp32-s3-devkitc-1/firmware.elf | grep favicon

//extern const uint8_t favicon_ico_start[] asm("_binary_favicon_ico_start");
//extern const uint8_t favicon_ico_end[] asm("_binary_favicon_ico_end");
//serveEmbeddedFile(server, "/favicon.ico", favicon_ico_start, favicon_ico_end, "image/x-icon");