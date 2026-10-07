#ifndef UTILS_HPP
#define UTILS_HPP

#include <chrono>
#include <cstdint>
#include <string>
#include <tuple>
#include <utility>

namespace Utils
{
namespace Family
{
enum class Kindship : uint8_t {
    GRAND_MOTHER = 1 << 0,
    FATHER = 1 << 1,
    MOTHER = 1 << 2,
    SON = 1 << 3,
    DAUGHTER = 1 << 4,
    UNKNOWN = 1 << 5
};

constexpr Kindship operator|(Kindship lhs, Kindship rhs)
{
    return static_cast<Utils::Family::Kindship>(std::to_underlying(lhs) |
                                                std::to_underlying(rhs));
}

constexpr bool operator&(Kindship lhs, Kindship rhs)
{
    return (std::to_underlying(lhs) & std::to_underlying(rhs)) != 0;
}

std::string toString(Kindship kindship);
Kindship fromString(std::string kindship);
} // namespace Family

namespace Input
{
std::tuple<std::string, std::chrono::year_month_day, Utils::Family::Kindship>
person(const std::string &message =
           "Por favor, introduce el nombre de la persona") noexcept;
} // namespace Input
} // namespace Utils

#endif // UTILS_HPP
