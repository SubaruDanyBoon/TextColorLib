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
    return gc.get_code() + str + graphics::RESET;
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

void graphics::print_graphic_text(const std::string& str, const GCode& gc)
{
    std::cout << (gc + str + graphics::RESET);
}

void graphics::print_graphic_text(const std::string& str, const Color& c)
{
    std::cout << (GCode{ c } + str + graphics::RESET);
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
    static uint8_t currColor = 0;
    std::ostringstream oss;
    switch (currColor++)
    {
    case 0:
        oss << RED;
        break;
    case 1:
        oss << ORANGE;
        break;
    case 2:
        oss << YELLOW;
        break;
    case 3:
        oss << GREEN;
        break;
    case 4:
        oss << BLUE;
        break;
    case 5:
        oss << INDIGO;
        break;
    case 6:
        oss << VIOLET;
        break;
    default:
        currColor = 0;
        oss << RED;
    }
    oss << c;
    return oss.str();
}

std::string graphics::rainbowify_string(const std::string& str)
{
    std::ostringstream oss;
    for (int i = 0; i < str.size(); ++i)
        oss << rainbowify_char(str[i]);
    oss << RESET;
    return oss.str();
}

std::string graphics::rainbowify_alternative_char(const char& c)
{
    static uint8_t currColor = 0;
    std::ostringstream oss;
    switch (currColor++)
    {
    case 0:
        oss << RED;
        break;
    case 1:
        oss << LIME;
        break;
    case 2:
        oss << YELLOW;
        break;
    case 3:
        oss << BLUE;
        break;
    case 4:
        oss << MAGENTA;
        break;
    case 5:
        oss << CYAN;
        break;
    case 6:
        oss << WHITE;
        break;
    case 7:
        oss << SILVER;
        break;
    case 8:
        oss << GRAY;
        break;
    case 9:
        oss << MAROON;
        break;
    case 10:
        oss << OLIVE;
        break;
    case 11:
        oss << GREEN;
        break;
    case 12:
        oss << PURPLE;
        break;
    case 13:
        oss << TEAL;
        break;
    case 14:
        oss << NAVY;
        break;
    case 15:
        oss << ORANGE;
        break;
    case 16:
        oss << ORANGERED;
        break;
    case 17:
        oss << GOLD;
        break;
    case 18:
        oss << INDIGO;
        break;
    case 19:
        oss << VIOLET;
        break;
    default:
        currColor = 0;
        oss << RED;
    }
    oss << c;
    return oss.str();
}

std::string graphics::rainbowify_alternative_string(const std::string& str)
{
    std::ostringstream oss;
    for (int i = 0; i < str.size(); ++i)
        oss << rainbowify_alternative_char(str[i]);
    oss << RESET;
    return oss.str();
}