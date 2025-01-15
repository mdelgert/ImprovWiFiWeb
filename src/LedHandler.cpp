#ifdef ENABLE_LED_HANDLER

#include "LedHandler.h"

// Define static members
CRGB LedHandler::leds[NUM_LEDS];
uint8_t LedHandler::defaultBrightness = 100; // Default brightness

std::string toLower(const std::string &str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}

// Define the color map
const std::unordered_map<std::string, CRGB> LedHandler::colorMap = {
    {"red", CRGB::Red},
    {"green", CRGB::Green},
    {"blue", CRGB::Blue},
    {"yellow", CRGB::Yellow},
    {"white", CRGB::White},
    {"black", CRGB::Black},
    {"orange", CRGB::Orange},
    {"purple", CRGB::Purple},
    {"pink", CRGB::Pink},
    {"cyan", CRGB::Cyan},
    {"magenta", CRGB::Magenta},
    {"brown", CRGB::Brown},
    {"lime", CRGB::Lime},
    {"turquoise", CRGB::Turquoise},
    {"violet", CRGB::Violet},
    {"gold", CRGB::Gold},
    {"silver", CRGB::Silver},
    {"teal", CRGB::Teal},
    {"navy", CRGB::Navy},
    {"maroon", CRGB::Maroon},
    {"olive", CRGB::Olive},
    {"skyblue", CRGB::SkyBlue},
    {"hotpink", CRGB::HotPink},
    {"chartreuse", CRGB::Chartreuse},
    {"aquamarine", CRGB::Aquamarine},
    {"khaki", CRGB::Khaki},
    {"lavender", CRGB::Lavender},
    {"beige", CRGB::Beige}
};

void LedHandler::init() {
    FastLED.addLeds<LED_TYPE, LED_DI_PIN, LED_CI_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    clear(); // Turn off all LEDs initially
    CommandHandler::registerCommand("led", runCommand);
    debugI("LEDHandler initialized with %d LED(s)", NUM_LEDS);
}

void LedHandler::setColor(const CRGB &color, uint8_t brightness) {
    FastLED.setBrightness(brightness);
    leds[0] = color;
    FastLED.show();
    debugD("LED color set to R:%d G:%d B:%d with brightness %d", color.r, color.g, color.b, brightness);
}

/*
void LedHandler::setColorByName(const std::string &colorName, uint8_t brightness) {
    auto it = colorMap.find(colorName);
    if (it != colorMap.end()) {
        setColor(it->second, brightness);
    } else {
        debugW("Unknown color: %s", colorName.c_str());
    }
}
*/

void LedHandler::setColorByName(const std::string &colorName, uint8_t brightness) {
    std::string lowerColorName = toLower(colorName); // Convert colorName to lowercase
    auto it = colorMap.find(lowerColorName);
    if (it != colorMap.end()) {
        setColor(it->second, brightness);
    } else {
        debugW("Unknown color: %s", colorName.c_str());
    }
}

void LedHandler::clear() {
    FastLED.clear();
    FastLED.show();
    debugI("LEDs cleared");
}

void LedHandler::setDefaultBrightness(uint8_t brightness) {
    defaultBrightness = brightness;
    FastLED.setBrightness(defaultBrightness);
    FastLED.show();
    debugI("Default brightness set to %d", brightness);
}

void LedHandler::runCommand(const String &command) {
    String cmd = command;
    String args = "";

    int spaceIndex = command.indexOf(' ');
    if (spaceIndex > 0) {
        cmd = command.substring(0, spaceIndex);
        args = command.substring(spaceIndex + 1);
    }

    if (cmd == "color") {
        setColorByName(args.c_str(), defaultBrightness);
    } else if (cmd == "clear") {
        clear();
    } else if (cmd == "brightness") {
        setDefaultBrightness(args.toInt());
    } else {
        debugW("Unknown command: %s", cmd.c_str());
    }
}

#endif // ENABLE_LED_HANDLER