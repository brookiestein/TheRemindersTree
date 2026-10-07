#include "person.hpp"

#include <utility>

Person::Person(std::string name, std::chrono::year_month_day birthDate,
               Utils::Family::Kindship kindship)
    : m_name(std::move(name))
    , m_birthDate(birthDate)
    , m_kindship(kindship)
{
}

std::string_view Person::name() const noexcept
{
    return m_name;
}

std::chrono::year_month_day Person::birthDate() const noexcept
{
    return m_birthDate;
}

Utils::Family::Kindship Person::kindship() const noexcept
{
    return m_kindship;
}

bool Person::operator==(const Person &rhs) const noexcept
{
    return (m_name == rhs.m_name && m_birthDate == rhs.m_birthDate);
}
