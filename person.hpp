#ifndef PERSON_HPP
#define PERSON_HPP

#include <chrono>
#include <string>
#include <string_view>

#include "utils.hpp"

class Person
{
public:
    Person(std::string name, std::chrono::year_month_day birthDate,
           Utils::Family::Kindship kindship);

    [[nodiscard]] std::string_view name() const noexcept;
    [[nodiscard]] std::chrono::year_month_day birthDate() const noexcept;
    [[nodiscard]] Utils::Family::Kindship kindship() const noexcept;
    [[nodiscard]] bool operator==(const Person &rhs) const noexcept;

private:
    const std::string m_name;
    const std::chrono::year_month_day m_birthDate;
    Utils::Family::Kindship m_kindship;
};

#endif // PERSON_HPP
