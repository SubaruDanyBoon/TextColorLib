#ifndef COLOR_LIB_H
#define COLOR_LIB_H

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <optional>

namespace graphics
{
    // object that holds a 8bit R, 8bit G, and 8bit B int values that represents a 24bit color
    // Can also be used as a sticky iomanipulator just like GCode
    class Color
    {
    public:
        uint8_t r, g, b;

        // Used to create a color object, with optional 8bit r, b, g values
        Color(const uint8_t& _r = 0, const uint8_t& _b = 0, const uint8_t& _g = 0);
        // Used to add another Color object to a Color object's self
        friend void operator+=(Color& c1, const Color& c2);
        // Used to get the result of adding two Color objects together
        friend Color operator+(const Color& c1, const Color& c2);
        // Used to subtract another Color object to a Color object's self
        friend void operator-=(Color& c1, const Color& c2);
        // Used to get the result of subtracting two Color objects together
        friend Color operator-(const Color& c1, const Color& c2);
        // Used to multiply a scalar 8bit value to a Color object's self
        friend void operator*=(Color& c, const uint8_t& s);
        // Used to get the result of multiplying a Color object and a 8bit scalar
        friend Color operator*(const Color& c, const uint8_t& s);
        // Used to compare if two Color objects are equal
        friend bool operator==(const Color& c1, const Color& c2);
        // Used to compare if two Color objects are NOT equal
        friend bool operator!=(const Color& c1, const Color& c2);
        // Returns the stringified version of a color
        std::string to_string() const;
        // Returns the stringified version of a color
        static std::string to_string(const Color& c);

        // Minimum value of a uint8_t
        static const uint8_t MIN_VALUE{ 0 };
        // Maximum value of a uint8_t
        static const uint8_t MAX_VALUE{ 255 };

    private:
        // Clamps a integer inbetween two uint8_t values
        static uint8_t clamp(const int& num, const uint8_t& lowerBound, const uint8_t& upperBound);

    public:
        // A Color object that is set to the color BLACK
        static const Color BLACK;
        // A Color object that is set to the color RED
        static const Color RED;
        // A Color object that is set to the color LIME
        static const Color LIME;
        // A Color object that is set to the color YELLOW
        static const Color YELLOW;
        // A Color object that is set to the color BLUE
        static const Color BLUE;
        // A Color object that is set to the color MAGENTA
        static const Color MAGENTA;
        // A Color object that is set to the color CYAN
        static const Color CYAN;
        // A Color object that is set to the color WHITE
        static const Color WHITE;
        // A Color object that is set to the color SILVER
        static const Color SILVER;
        // A Color object that is set to the color GRAY
        static const Color GRAY;
        // A Color object that is set to the color MAROON
        static const Color MAROON;
        // A Color object that is set to the color OLIVE
        static const Color OLIVE;
        // A Color object that is set to the color GREEN
        static const Color GREEN;
        // A Color object that is set to the color PURPLE
        static const Color PURPLE;
        // A Color object that is set to the color TEAL
        static const Color TEAL;
        // A Color object that is set to the color NAVY
        static const Color NAVY;
        // A Color object that is set to the color ORANGE
        static const Color ORANGE;
        // A Color object that is set to the color ORANGERED
        static const Color ORANGERED;
        // A Color object that is set to the color GOLD
        static const Color GOLD;
        // A Color object that is set to the color INDIGO
        static const Color INDIGO;
        // A Color object that is set to the color VIOLET
        static const Color VIOLET;
    };
    
    /*
        Graphics Code for SGRs or Select Graphic Rendition attributes. They are used just like iomanipulators.
        Using the << operator before text it will change texts graphically to different colors or effects.
        WARNING: these are sticky manipulators so be sure to use graphics::reset on the output stream after use.
        Can also be used in accordance w/ print_graphic_text({GCode}) or print_line_graphic_text({GCode})
        as parameters, but are not required
    */
    class GCode
    {
    private:
        Color fgColor;
        std::optional<Color> bgColor;
        bool isBolded;
        bool isFaint;
        bool isItalicized;
        bool isUnderlined;
        bool isBlinking;

    public:
        GCode(const Color& _fgColor = Color::BLACK, const std::optional<Color>& _bgColor = std::nullopt, const bool& _isBolded = false, const bool& _isFaint = false, const bool& _isItalicized = false, const bool& _isUnderlined = false, const bool& _isBlinking = false);
        // Sets the foreground's or text's color using a Color object
        void set_foreground(const Color& color = Color::BLACK);
        // Sets the foreground's or text's color using 8bit RGB values
        void set_foreground(const uint8_t& r = Color::MAX_VALUE, const uint8_t& g = Color::MAX_VALUE, const uint8_t& b = Color::MAX_VALUE);
        // Sets the background's color using a color object
        void set_background(const Color& color = Color::BLACK);
        // Sets the background's color using 8bit RGB values
        void set_background(const uint8_t& r = Color::MAX_VALUE, const uint8_t& g = Color::MAX_VALUE, const uint8_t& b = Color::MAX_VALUE);
        // toggles text being bolded
        void toggle_bold();
        // toggles text beign underlined
        void toggle_underline();
        // toggles text being italicized
        void toggle_italic();
        // toggles text to blink/flash
        void toggle_blink();
        // To set a output stream to a sticky manipulator known as a GCode
        friend std::ostream& operator<<(std::ostream& os, const GCode& gc);
        // To add a GCode and std::string together
        friend std::string operator+(const GCode& gc, const std::string& str);
        // To add a GCode and std::string together
        friend std::string operator+(const std::string& str, const GCode& gc);

        // Gets size of GCode
        int size() const;

        // Returns a debug message to stdout stream, showing all the data members of a GCode for debugging purposes
        static std::string get_debug_string(const GCode& gc);

    private:
        // Combines all attributes into a single std::string
        std::string get_code() const;

    public:
        // A way of resetting GCode/Color iomanipulators
        static const std::string RESET;
    };

    // Used to send a Color code out to a output stream
    std::ostream& operator<<(std::ostream& os, const Color& c);
    
    // Prints a string using a GCode to the std::cout with a added std::endl
    void print_line_graphic_text(const std::string& str, const GCode& gc);
    // Prints a string using a Color to the std::cout with a added std::endl
    void print_line_graphic_text(const std::string& str, const Color& c);
    // Prints a string using a GCode to the std::cout
    void print_graphic_text(const std::string& str, const GCode& gc);
    // Prints a string using a Color to the std::cout
    void print_graphic_text(const std::string& str, const Color& c);

    // Returns a char with a color of the rainbow
    std::string rainbowify_char(const char& c);
    // Returns a std::string that each character is another color from the rainbow
    std::string rainbowify_string(const std::string& str);
    // Returns a char with a color of the rainbow using all static consts color predefined
    std::string rainbowify_alternative_char(const char& c);
    // Returns a std::string that each character is another color from the rainbow using all static consts color predefined
    std::string rainbowify_alternative_string(const std::string& str);
    // Returns a string preformatted with a GCode and auto resets the GCode at the end of the std::string
    std::string get_graphic_text(const std::string& str, const GCode& gc);
    // Returns a string preformatted with a Color and auto resets the GCode at the end of the std::string
    std::string get_graphic_text(const std::string& str, const Color& c);
};

#endif
