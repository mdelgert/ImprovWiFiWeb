#ifndef LED_HANDLER_H
#define LED_HANDLER_H

#include "Globals.h"
#include <FastLED.h>
#include <unordered_map>
#include <string>

// LED configuration
#define NUM_LEDS 1
#define LED_TYPE APA102
#define COLOR_ORDER BGR

class LedHandler {
public:
    // Initialize the LED handler
    static void init();

    // Set LED color by name (e.g., "Red", "Blue")
    static void setColorByName(const std::string &colorName, uint8_t brightness = defaultBrightness);

    // Turn off all LEDs
    static void clear();

    // Set default brightness
    static void setDefaultBrightness(uint8_t brightness);

private:
    static CRGB leds[NUM_LEDS];       // Static array for LED data
    static uint8_t defaultBrightness; // Default brightness level

    // Map of color names to CRGB values
    static const std::unordered_map<std::string, CRGB> colorMap;

    // Set LED color directly (internal use only)
    static void setColor(const CRGB &color, uint8_t brightness);
};

#endif // LED_HANDLER_H
