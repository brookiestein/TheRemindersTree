#ifndef INPUT_HPP
#define INPUT_HPP

#include <boost/convert.hpp>
#include <boost/convert/strtol.hpp>
#include <functional>
#include <print>
#include <string>
#include <type_traits>

struct boost::cnv::by_default : boost::cnv::strtol {};

class Input
{
public:
    Input() = delete;

    static std::string text(const std::string &message) noexcept;

    template <typename T>
        requires std::is_arithmetic_v<T>
    static T number(
        const std::string &message,
        std::function<bool(const T &)> &&isValid =
            [](const T &) {
                return true;
            },
        const std::string &errorMessage = "El valor introducido no cumple los "
                                          "criterios establecidos.") noexcept
    {
        T num {};

        while (true) {
            auto input = text(message);

            try {
                num = boost::convert<T>(input).value();
                if (isValid(num))
                    break;
            } catch (...) {
                std::println(
                    stderr,
                    "Lo que introdujiste, {}, no parece ser un número válido.",
                    input);
                continue;
            }

            std::println(stderr, "{}", errorMessage);
        }

        return num;
    }
};

#endif // INPUT_HPP
