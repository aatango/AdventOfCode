#include "MullItOver.hh"

#include <regex>

namespace MullItOver {

auto parseInput(std::string const& input) noexcept -> Multiplications
{
    auto const pattern = std::regex { R"(mul\((\d{1,3}),(\d{1,3})\))" };

    auto const inputBegin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto const inputEnd = std::sregex_iterator();

    auto multiplications = Multiplications {};
    multiplications.reserve(2 * std::distance(inputBegin, inputEnd));

    for (std::regex_iterator i = inputBegin; i != inputEnd; ++i) {
        auto const multiplicand = std::stoull((*i)[1].str());
        auto const multiplier = std::stoull((*i)[2].str());

        multiplications.emplace_back(multiplicand, multiplier);
    }

    return multiplications;
}

} // namespace MullItOver
