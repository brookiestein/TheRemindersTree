#include "utils.hpp"
#include "input.hpp"

#include <chrono>
#include <cctype>
#include <format>
#include <print>
#include <ranges>
#include <string>
#include <utility>

std::string Utils::Family::toString(Utils::Family::Kindship kindship)
{
    switch (kindship) {
    case Family::Kindship::GRAND_MOTHER:
        return "Abuela";
    case Family::Kindship::FATHER:
        return "Padre";
    case Family::Kindship::MOTHER:
        return "Madre";
    case Family::Kindship::SON:
        return "Hijo";
    case Family::Kindship::DAUGHTER:
        return "Hija";
    case Family::Kindship::UNKNOWN:
        return "No establecido";
    }

    std::unreachable();
}

Utils::Family::Kindship Utils::Family::fromString(std::string kindship)
{
    std::ranges::transform(kindship, kindship.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });

    if (kindship == "abuela")
        return Family::Kindship::GRAND_MOTHER;
    if (kindship == "padre")
        return Family::Kindship::FATHER;
    if (kindship == "madre")
        return Family::Kindship::MOTHER;
    if (kindship == "hijo")
        return Family::Kindship::SON;
    if (kindship == "hija")
        return Family::Kindship::DAUGHTER;

    return Family::Kindship::UNKNOWN;
}

std::tuple<std::string, std::chrono::year_month_day, Utils::Family::Kindship>
Utils::Input::person(const std::string &message) noexcept
{
    std::println("{}", message);

    auto name = ::Input::text("Primero, su nombre");

    const auto today = std::chrono::floor<std::chrono::days>(
        std::chrono::system_clock::now());
    const std::chrono::year_month_day currentDate {today};
    const auto currentYear = static_cast<int>(currentDate.year());

    std::chrono::year_month_day birthDate;

    while (true) {
        auto day = ::Input::number<int>(
            "Continuemos con su día de nacimiento [1-31]", [](int day) {
                return (day > 0 && day < 32);
            });

        auto month = ::Input::number<int>(
            "Ahora su mes de nacimiento [1-12]", [](int month) {
                return (month > 0 && month < 13);
            });

        auto year = ::Input::number<int>(
            "Ya casi terminamos, vamos con su año de nacimiento",
            [currentYear](int year) {
                return (year >= 1920 && year <= currentYear);
            });

        birthDate = std::chrono::year_month_day(
            std::chrono::year(year),
            std::chrono::month(static_cast<unsigned>(month)),
            std::chrono::day(static_cast<unsigned>(day)));

        if (birthDate.ok())
            break;

        std::println(stderr,
                     "La fecha introducida no existe. Inténtalo nuevamente.");
    }

    std::println(
        "Por último, pero no menos importante, su parentesco en esta familia");

    Family::Kindship kindship = Family::Kindship::UNKNOWN;
    while (true) {
        std::println("[Abuela, padre, madre, hijo o hija]");

        auto kindshipStr = ::Input::text(std::format(
            "Por favor, introduce el parentesco de {} en esta familia", name));

        kindship = Family::fromString(kindshipStr);
        if (kindship != Family::Kindship::UNKNOWN)
            break;

        std::println(stderr, "Debes introducir uno de los valores indicados.");
    }

    return {name, birthDate, kindship};
}
