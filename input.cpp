#include "input.hpp"

#include <iostream>
#include <print>

std::string Input::text(const std::string &message) noexcept
{
    std::string input {};

    while (true) {
        std::print("{}: ", message);
        std::getline(std::cin, input);

        if (input.empty()) {
            std::println("No introdujiste nada.");
            continue;
        }

        break;
    }

    return input;
}
