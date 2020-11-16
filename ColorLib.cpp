#include "ColorLib.h"

graphics::Color::Color(const uint8_t& _r, const uint8_t& _g, const uint8_t& _b)
    : r{ _r }, g{ _g }, b{ _b } {}

uint8_t graphics::Color::clamp(const int& num, const uint8_t& lowerBound, const uint8_t& upperBound)
{
    if (num > upperBound)
        return upperBound;
    if (num < lowerBound)
        return lowerBound;
    return num;
}

void graphics::operator+=(Color& c1, const Color& c2)
{
    c1.r = graphics::Color::clamp(c1.r + c2.r, graphics::Color::MIN_VALUE, graphics::Color::MAX_VALUE);
    c1.g = graphics::Color::clamp(c1.g + c2.g, graphics::Color::MIN_VALUE, graphics::Color::MAX_VALUE);
    c1.b = graphics::Color::clamp(c1.b + c2.b, graphics::Color::MIN_VALUE, graphics::Color::MAX_VALUE);
}

graphics::Color graphics::operator+(const Color& c1, const Color& c2)
{
    return Color{ Color::clamp(c1.r + c2.r, Color::MIN_VALUE, Color::MAX_VALUE), Color::clamp(c1.g + c2.g, Color::MIN_VALUE, Color::MAX_VALUE), Color::clamp(c1.b + c1.b, Color::MIN_VALUE, Color::MAX_VALUE) };
}

void graphics::operator-=(Color& c1, const Color& c2)
{
    c1.r = Color::clamp(c1.r - c2.r, Color::MIN_VALUE, Color::MAX_VALUE);
    c1.g = Color::clamp(c1.g - c2.g, Color::MIN_VALUE, Color::MAX_VALUE);
    c1.b = Color::clamp(c1.b - c2.b, Color::MIN_VALUE, Color::MAX_VALUE);
}

graphics::Color graphics::operator-(const Color& c1, const Color& c2)
{
    return Color{ Color::clamp(c1.r - c2.r, Color::MIN_VALUE, Color::MAX_VALUE), Color::clamp(c1.g - c2.g, Color::MIN_VALUE, Color::MAX_VALUE), Color::clamp(c1.b - c1.b, Color::MIN_VALUE, Color::MAX_VALUE) };
}

void graphics::operator*=(graphics::Color& c, const uint8_t& s)
{
    c.r = graphics::Color::clamp(c.r * s, graphics::Color::MIN_VALUE, graphics::Color::MAX_VALUE);
    c.g = graphics::Color::clamp(c.g * s, graphics::Color::MIN_VALUE, graphics::Color::MAX_VALUE);
    c.b = graphics::Color::clamp(c.b * s, graphics::Color::MIN_VALUE, graphics::Color::MAX_VALUE);
}

graphics::Color graphics::operator*(const Color& c, const uint8_t& s)
{
    return Color{ Color::clamp(c.r * s, Color::MIN_VALUE, Color::MAX_VALUE), Color::clamp(c.g * s, Color::MIN_VALUE, Color::MAX_VALUE), Color::clamp(c.b * s, Color::MIN_VALUE, Color::MAX_VALUE) };
}

bool graphics::operator==(const Color& c1, const Color& c2)
{
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}

bool graphics::operator!=(const Color& c1, const Color& c2)
{
    return !(c1 == c2);
}

std::ostream& graphics::operator<<(std::ostream& os, const graphics::Color& c)
{
    os << GCode{ c };
    return os;
}

std::string graphics::Color::to_string() const
{
    std::ostringstream oss;
    oss << "{ " << (int)r << ", " << (int)g << ", " << (int)b << " }";
    return oss.str();
}

std::string graphics::Color::to_string(const Color& c)
{
    return c.to_string();
}

const graphics::Color graphics::Color::BLACK{ 0, 0, 0 };
const graphics::Color graphics::Color::RED{ 255, 0, 0 };
const graphics::Color graphics::Color::LIME{ 0, 255, 0 };
const graphics::Color graphics::Color::YELLOW{ 255, 255, 0 };
const graphics::Color graphics::Color::BLUE{ 0, 0, 255 };
const graphics::Color graphics::Color::MAGENTA{ 255, 0, 255 };
const graphics::Color graphics::Color::CYAN{ 0, 255, 255 };
const graphics::Color graphics::Color::WHITE{ 255, 255, 255 };
const graphics::Color graphics::Color::SILVER{ 192, 192, 192 };
const graphics::Color graphics::Color::GRAY{ 128, 128, 128 };
const graphics::Color graphics::Color::MAROON{ 128, 0, 0 };
const graphics::Color graphics::Color::OLIVE{ 128, 128, 0 };
const graphics::Color graphics::Color::GREEN{ 0, 128, 0 };
const graphics::Color graphics::Color::PURPLE{ 128, 0, 128 };
const graphics::Color graphics::Color::TEAL{ 0, 128, 128 };
const graphics::Color graphics::Color::NAVY{ 0, 0, 128 };
const graphics::Color graphics::Color::ORANGE{ 255, 165, 0 };
const graphics::Color graphics::Color::ORANGERED{ 255, 69, 0 };
const graphics::Color graphics::Color::GOLD{ 255, 215, 0 };
const graphics::Color graphics::Color::INDIGO{ 75, 0, 130 };
const graphics::Color graphics::Color::VIOLET{ 238, 130, 238 };

graphics::GCode::GCode(const Color& _fgColor, const std::optional<Color>& _bgColor, const bool& _isBolded, const bool& _isFaint, const bool& _isItalicized, const bool& _isUnderlined, const bool& _isBlinking)
    : fgColor{ _fgColor }, bgColor{ _bgColor }, isBolded{ _isBolded }, isFaint{ _isFaint }, isItalicized{ _isItalicized }, isUnderlined{ _isUnderlined }, isBlinking{ _isBlinking } {}

void graphics::GCode::set_foreground(const Color& color)
{
    fgColor = color;
}

void graphics::GCode::set_foreground(const uint8_t& r, const uint8_t& g, const uint8_t& b)
{
    fgColor = Color{ r, g, b };
}

void graphics::GCode::set_background(const Color& color)
{
    fgColor = color;
}

void graphics::GCode::set_background(const uint8_t& r, const uint8_t& g, const uint8_t& b)
{
    fgColor = Color{ r, g, b };
}

void graphics::GCode::toggle_bold()
{
    isBolded = !isBolded;
}

void graphics::GCode::toggle_underline()
{
    isUnderlined = !isUnderlined;
}

void graphics::GCode::toggle_italic()
{
    isItalicized = !isItalicized;
}

void graphics::GCode::toggle_blink()
{
    isBlinking = !isBlinking;
}

std::string graphics::GCode::get_code() const
{
    std::ostringstream oss;
    oss << "\033[";
    oss << "38;2;" << (int)fgColor.r << ';' << (int)fgColor.g << ';' << (int)fgColor.b;
    if (bgColor.has_value())
        oss << ';' << "48;2;" << (int)bgColor.value().r << ';' << (int)bgColor.value().g << ';' << (int)bgColor.value().b;
    if (isBolded)
        oss << ";1";
    if (isUnderlined)
        oss << ";4";
    if (isItalicized)
        oss << ";3";
    if (isBlinking)
        oss << ";5;6";
    oss << 'm';
    return oss.str();
}

std::ostream& graphics::operator<<(std::ostream& os, const GCode& gc)
{
    os << gc.get_code();
    return os;
}

std::string graphics::operator+(const GCode& gc, const std::string& str)
{
    return gc.get_code() + str + graphics::GCode::RESET;
}

std::string graphics::operator+(const std::string& str, const GCode& gc)
{
    return gc + str;
}

int graphics::GCode::size() const
{
    return get_code().size();
}

std::string graphics::GCode::get_debug_string(const GCode& gc)
{
    std::ostringstream oss;
    oss << "Foreground Color: " << gc.fgColor << "\n";
    if (gc.bgColor.has_value())
        oss << "Background Color: " << gc.bgColor.value() << "\n";
    else
        oss << "NULL" << "\n";
    oss << std::boolalpha;
    oss << "isBolded: " << gc.isBolded << "\n"
        << "isUnderlined: " << gc.isUnderlined << "\n"
        << "isIntalicized: " << gc.isItalicized << "\n"
        << "isBlinking: " << gc.isBlinking << std::endl;
    return oss.str();
}

const std::string graphics::GCode::RESET{"\033[0m"};

void graphics::print_graphic_text(const std::string& str, const GCode& gc)
{
    std::cout << (gc + str + graphics::GCode::RESET);
}

void graphics::print_graphic_text(const std::string& str, const Color& c)
{
    std::cout << (GCode{ c } + str + graphics::GCode::RESET);
}

void graphics::print_line_graphic_text(const std::string& str, const GCode& gc)
{
    print_graphic_text(str, gc);
    std::cout << std::endl;
}

void graphics::print_line_graphic_text(const std::string& str, const Color& c)
{
    print_graphic_text(str, c);
    std::cout << std::endl;
}

std::string graphics::rainbowify_char(const char& c)
{
    static const unsigned int SIZE{ 7 };
    static const Color* colors[SIZE]{ &Color::RED, &Color::ORANGE, &Color::YELLOW, &Color::GREEN, &Color::BLUE, &Color::INDIGO, &Color::VIOLET };
    static uint8_t currColor = 0;
    if (currColor == SIZE)
        currColor = 0;
    std::ostringstream oss;
    oss << *colors[currColor++];
    oss << c;
    return oss.str();
}

std::string graphics::rainbowify_string(const std::string& str)
{
    std::ostringstream oss;
    for (int i = 0; i < str.size(); ++i)
        oss << rainbowify_char(str[i]);
    oss << GCode::RESET;
    return oss.str();
}

std::string graphics::rainbowify_alternative_char(const char& c)
{
    static const unsigned int SIZE{ 20 };
    static const Color* colors[SIZE]{ &Color::RED, &Color::LIME, &Color::YELLOW, &Color::BLUE, &Color::MAGENTA, &Color::CYAN, &Color::WHITE, &Color::SILVER, &Color::GRAY, &Color::MAROON, &Color::OLIVE, &Color::GREEN, &Color::PURPLE, &Color::TEAL, &Color::NAVY, &Color::ORANGE, &Color::ORANGERED, &Color::GOLD, &Color::INDIGO, &Color::VIOLET };
    static uint8_t currColor = 0;
    if (currColor == SIZE)
        currColor = 0;
    std::ostringstream oss;
    oss << *colors[currColor++];
    oss << c;
    return oss.str();
}

std::string graphics::rainbowify_alternative_string(const std::string& str)
{
    std::ostringstream oss;
    for (int i = 0; i < str.size(); ++i)
        oss << rainbowify_alternative_char(str[i]);
    oss << GCode::RESET;
    return oss.str();
}

std::string graphics::get_graphic_text(const std::string& str, const GCode& gc)
{
    std::ostringstream oss;
    oss << gc << str << GCode::RESET;
    return oss.str();
}

std::string graphics::get_graphic_text(const std::string& str, const Color& c)
{
    return get_graphic_text(str, GCode{c});
}